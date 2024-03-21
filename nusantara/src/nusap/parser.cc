#include "nusap/parser.h"

#include "nusal/lexer.h"
#include "nusal/nusal.h"
#include "nusal/tipe_token.h"
#include "nusal/token.h"
#include "nusap/kesalahan_parse.h"
#include "nusap/node.h"
#include "nusap/tipe_node.h"

#include <algorithm>
#include <format>
#include <memory>

nusap::parser::parser():
    lexer(nusal::nusal_data_tipe_token()), token_saat_ini(nullptr) {}

void nusap::parser::input(const std::string& input) {
  this->lexer.input(input);
}

void nusap::parser::input(const std::string& sumber, const std::string& input) {
  this->lexer.input(sumber, input);
}

void nusap::parser::input_filepath(const std::string& file_path) {
  this->lexer.input_filepath(file_path);
}

const std::vector<nusal::tipe_token>& nusap::parser::skipTipeToken() {
  static std::vector<nusal::tipe_token> hasil = {
      nusal::tipe_token::KEMBALI_KE_AWAL_KARAKTER,
      nusal::tipe_token::BARIS_BARU,
      nusal::tipe_token::TAB,
      nusal::tipe_token::SPASI,
      nusal::tipe_token::KOMENTAR_SATU_BARIS,
      nusal::tipe_token::KOMENTAR_BANYAK_BARIS
  };
  return hasil;
}

void nusap::parser::tokenSelanjutNya() {
  this->token_saat_ini = this->lexer.ambil_token();
}

bool nusap::parser::tokenSaatIni(const nusal::tipe_token& tipe) {	
  return (this->token_saat_ini != nullptr) && (this->token_saat_ini->tipe == tipe);
}

bool nusap::parser::tokenSaatIni(const std::vector<nusal::tipe_token>& tipe) {
  return std::ranges::any_of(tipe, [&](const auto& element) {
    return this->tokenSaatIni(element);
  });
}


bool nusap::parser::mengharapkanToken(
    const std::unique_ptr<node>& aturan, const nusal::tipe_token& tipe,
    const std::function<std::unique_ptr<node>()>& callback
) {
  bool hasil = this->tokenSaatIni(tipe);
  if(hasil) {
		auto node = callback();
		if(node->tipe == tipe_node::token) {
			this->tokenSelanjutNya();
			this->parseSkipToken();
		}
    aturan->children.push_back(std::move(node));
  }
  return hasil;
}

bool nusap::parser::mengharapkanToken(
    const std::unique_ptr<node>& aturan,
    const std::vector<nusal::tipe_token>& tipe,
    const std::function<std::unique_ptr<node>()>& callback
) {
  return std::ranges::any_of(tipe, [&](const auto& element) {
    return this->mengharapkanToken(aturan, element, callback);
  });
}

std::unique_ptr<nusap::node>
nusap::parser::buatNodeAturan(const nusap::tipe_node& tipe) {
  return std::make_unique<node>(tipe);
}

std::unique_ptr<nusap::node> nusap::parser::buatNodeToken() {
  return std::make_unique<node>(
      tipe_node::token, std::make_unique<nusal::token>(*this->token_saat_ini)
  );
}

void nusap::parser::parseSkipToken() {
  while(this->tokenSaatIni(this->skipTipeToken())) {
    this->tokenSelanjutNya();
  }
}

std::unique_ptr<nusap::node> nusap::parser::parse() {
  std::unique_ptr<nusap::node> nusantara = buatNodeAturan(tipe_node::nusantara);
  this->tokenSelanjutNya();
  while(this->token_saat_ini != nullptr) {
    if(this->tokenSaatIni(nusal::tipe_token::TIDAK_DIKETAHUI)) {
      throw nusap::kesalahan_parser(
          *this->token_saat_ini,
          std::format(
              "Nusantara tidak dapat mengenali karakter '{}'.",
              this->token_saat_ini->nilai
          )
      );
    }
		nusantara->children.push_back(this->parse_pernyataan());
  }
  return nusantara;
}

std::unique_ptr<nusap::node> nusap::parser::parse_pernyataan() {
  std::unique_ptr<nusap::node> pernyataan = buatNodeAturan(tipe_node::pernyataan);
	if(this->mengharapkanToken(pernyataan, nusal::tipe_token::MUAT, [&](){return this->parse_muat_file();})) {
		if(!this->mengharapkanToken(pernyataan, nusal::tipe_token::TITIK_KOMA, [&](){return this->buatNodeToken();})) {
			throw kesalahan_parser(*this->token_saat_ini, "Jangan lupa titik koma.");
		}
  	return pernyataan;
	}
	throw kesalahan_parser(*this->token_saat_ini, "Pernyataan tidak valid");
}

std::unique_ptr<nusap::node> nusap::parser::parse_muat_file() {
  std::unique_ptr<nusap::node> muat_file = buatNodeAturan(tipe_node::muat_file);
  if(!this->mengharapkanToken(muat_file, nusal::tipe_token::MUAT, [&]() {return this->buatNodeToken();})) {
    throw kesalahan_parser(*this->token_saat_ini, "Untuk memuat file harus di awali dengan kata kunci 'muat'.");
  }
  if(!this->mengharapkanToken(muat_file, nusal::tipe_token::KUTIP_SATU, [&]() {return this->parse_nilai_teks();})) {
    throw kesalahan_parser(*this->token_saat_ini, "Lokasi file tidak valid.");
  }
  return muat_file;
}

std::unique_ptr<nusap::node> nusap::parser::parse_nilai_teks() {
  std::unique_ptr<nusap::node> nilai_teks = buatNodeAturan(tipe_node::nilai_teks);
  if(!this->mengharapkanToken(nilai_teks, nusal::tipe_token::KUTIP_SATU, [&]() {return this->buatNodeToken();})) {
    throw kesalahan_parser(*this->token_saat_ini, "Teks harus di awali kutip 1.");
  }
  while(!tokenSaatIni(nusal::tipe_token::KUTIP_SATU)) {
    nilai_teks->children.push_back(this->buatNodeToken());
		this->tokenSelanjutNya();
  }
  if(!this->mengharapkanToken(nilai_teks, nusal::tipe_token::KUTIP_SATU, [&]() {return this->buatNodeToken();})) {
    throw kesalahan_parser(*this->token_saat_ini, "Teks harus di akhiri kutip 1.");
  }
  return nilai_teks;
}
