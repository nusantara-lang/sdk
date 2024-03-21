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

Nusap::Parser::Parser():
    lexer(Nusal::nusalDataTipeToken()), tokenSaatIni(nullptr) {}

void Nusap::Parser::input(const std::string& input) {
  this->lexer.input(input);
}

void Nusap::Parser::input(const std::string& sumber, const std::string& input) {
  this->lexer.input(sumber, input);
}

void Nusap::Parser::inputFilePath(const std::string& filePath) {
  this->lexer.inputFilePath(filePath);
}

const std::vector<Nusal::TipeToken>& Nusap::Parser::skipTipeToken() {
  static std::vector<Nusal::TipeToken> hasil = {
      Nusal::TipeToken::kembali_ke_awal_karakter,
      Nusal::TipeToken::baris_baru,
      Nusal::TipeToken::tab,
      Nusal::TipeToken::spasi,
      Nusal::TipeToken::komentar_satu_baris,
      Nusal::TipeToken::komentar_banyak_baris
  };
  return hasil;
}

void Nusap::Parser::tokenSelanjutNya() {
  this->tokenSaatIni = this->lexer.ambilToken();
}

bool Nusap::Parser::tokenSaatIniAdalah(const Nusal::TipeToken& tipe) {	
  return (this->tokenSaatIni != nullptr) && (this->tokenSaatIni->tipe == tipe);
}

bool Nusap::Parser::tokenSaatIniAdalah(const std::vector<Nusal::TipeToken>& tipe) {
  return std::ranges::any_of(tipe, [&](const auto& element) {
    return this->tokenSaatIniAdalah(element);
  });
}


bool Nusap::Parser::mengharapkanToken(
    const std::unique_ptr<Node>& aturan, const Nusal::TipeToken& tipe,
    const std::function<std::unique_ptr<Node>()>& callback
) {
  this->parseSkipToken();
  bool hasil = this->tokenSaatIniAdalah(tipe);
  if(hasil) {
		auto node = callback();
		if(node->tipe == TipeNode::token) {
			this->tokenSelanjutNya();
			this->parseSkipToken();
		}
    aturan->children.push_back(std::move(node));
  }
  return hasil;
}

bool Nusap::Parser::mengharapkanToken(
    const std::unique_ptr<Node>& aturan,
    const std::vector<Nusal::TipeToken>& tipe,
    const std::function<std::unique_ptr<Node>()>& callback
) {
  return std::ranges::any_of(tipe, [&](const auto& element) {
    return this->mengharapkanToken(aturan, element, callback);
  });
}

std::unique_ptr<Nusap::Node>
Nusap::Parser::buatNodeAturan(const Nusap::TipeNode& tipe) {
  return std::make_unique<Node>(tipe);
}

std::unique_ptr<Nusap::Node> Nusap::Parser::buatNodeToken() {
  return std::make_unique<Node>(
      TipeNode::token, std::make_unique<Nusal::Token>(*this->tokenSaatIni)
  );
}

void Nusap::Parser::parseSkipToken() {
  while(this->tokenSaatIniAdalah(this->skipTipeToken())) {
    this->tokenSelanjutNya();
  }
}

// PARSE AREA

std::unique_ptr<Nusap::Node> Nusap::Parser::parse() {
  std::unique_ptr<Nusap::Node> nusantara = buatNodeAturan(TipeNode::nusantara);
  this->tokenSelanjutNya();
  this->parseSkipToken();
  while(this->tokenSaatIni != nullptr) {
    if(this->tokenSaatIniAdalah(Nusal::TipeToken::tidak_diketahui)) {
      throw Nusap::KesalahanParse(
          this->tokenSaatIni,
          std::format(
              "Nusantara tidak dapat mengenali karakter '{}'.",
              this->tokenSaatIni->nilai
          )
      );
    }
		nusantara->children.push_back(this->parsePernyataan());
  }
  return nusantara;
}

std::unique_ptr<Nusap::Node> Nusap::Parser::parsePernyataan() {
  std::unique_ptr<Nusap::Node> pernyataan = buatNodeAturan(TipeNode::pernyataan);
	if(this->mengharapkanToken(pernyataan, Nusal::TipeToken::muat, [&](){return this->parseMuatFile();})) {
		if(!this->mengharapkanToken(pernyataan, Nusal::TipeToken::titik_koma, [&](){return this->buatNodeToken();})) {
			throw KesalahanParse(this->tokenSaatIni, "Jangan lupa titik koma.");
		}
  	return pernyataan;
	}
	throw KesalahanParse(this->tokenSaatIni, "Pernyataan tidak valid");
}

std::unique_ptr<Nusap::Node> Nusap::Parser::parseMuatFile() {
  std::unique_ptr<Nusap::Node> muatFile = buatNodeAturan(TipeNode::muat_file);
  if(!this->mengharapkanToken(muatFile, Nusal::TipeToken::muat, [&]() {return this->buatNodeToken();})) {
    throw KesalahanParse(this->tokenSaatIni, "Untuk memuat file harus di awali dengan kata kunci 'muat'.");
  }
  if(!this->mengharapkanToken(muatFile, Nusal::TipeToken::kutip_satu, [&]() {return this->parseNilaiTeks();})) {
    throw KesalahanParse(this->tokenSaatIni, "Lokasi file tidak valid.");
  }
  return muatFile;
}

std::unique_ptr<Nusap::Node> Nusap::Parser::parseNilaiTeks() {
  std::unique_ptr<Nusap::Node> nilaiTeks = buatNodeAturan(TipeNode::nilai_teks);
  if(!this->mengharapkanToken(nilaiTeks, Nusal::TipeToken::kutip_satu, [&]() {return this->buatNodeToken();})) {
    throw KesalahanParse(this->tokenSaatIni, "Teks harus di awali kutip 1.");
  }
  while(!tokenSaatIniAdalah(Nusal::TipeToken::kutip_satu)) {
    nilaiTeks->children.push_back(this->buatNodeToken());
		this->tokenSelanjutNya();
  }
  if(!this->mengharapkanToken(nilaiTeks, Nusal::TipeToken::kutip_satu, [&]() {return this->buatNodeToken();})) {
    throw KesalahanParse(this->tokenSaatIni, "Teks harus di akhiri kutip 1.");
  }
  return nilaiTeks;
}

std::unique_ptr<Nusap::Node> Nusap::Parser::parseNilaiBilangan() {
  std::unique_ptr<Nusap::Node> nilaiBilangan = buatNodeAturan(TipeNode::nilai_bilangan);
  this->mengharapkanToken(nilaiBilangan, Nusal::TipeToken::tanda_hubung, [&]() {return this->buatNodeToken();});
  while(tokenSaatIniAdalah(Nusal::TipeToken::angka)) {
    nilaiBilangan->children.push_back(this->buatNodeToken());
		this->tokenSelanjutNya();
  }
  if(this->tokenSaatIniAdalah(Nusal::TipeToken::titik)) {
    throw KesalahanParse(this->tokenSaatIni, "Di indonesia biasa nya bilangan desimal menggunakan koma.");
  }
  if(this->mengharapkanToken(nilaiBilangan, Nusal::TipeToken::koma, [&]() {return this->buatNodeToken();})) {
    size_t index = 0;
    while(tokenSaatIniAdalah(Nusal::TipeToken::angka)) {
      nilaiBilangan->children.push_back(this->buatNodeToken());
      this->tokenSelanjutNya();
      ++index;
    }
    if(index <= 0) {
      throw KesalahanParse(this->tokenSaatIni, "Setelah koma seharus nya ada angka lagi agar menjadi bilangan desimal.");
    }
  }
  return nilaiBilangan;
}

std::unique_ptr<Nusap::Node> Nusap::Parser::parseNilai() {
  std::unique_ptr<Nusap::Node> nilai = buatNodeAturan(TipeNode::nilai);
  if(this->tokenSaatIniAdalah({Nusal::TipeToken::tanda_hubung, Nusal::TipeToken::angka})) {
    nilai->children.push_back(this->parseNilaiBilangan());
    return nilai;
  }else if(this->tokenSaatIniAdalah(Nusal::TipeToken::kutip_satu)) {
    nilai->children.push_back(this->parseNilaiTeks());
    return nilai;
  }
  throw KesalahanParse(this->tokenSaatIni, "Nilai tidak valid.");
}

std::unique_ptr<Nusap::Node> Nusap::Parser::parseEkspresi() {
  std::unique_ptr<Nusap::Node> ekspresi = buatNodeAturan(TipeNode::ekspresi);
  if(this->mengharapkanToken(ekspresi, {Nusal::TipeToken::tanda_hubung, Nusal::TipeToken::angka, Nusal::TipeToken::kutip_satu}, [&](){return this->parseNilai();})) {
    return ekspresi;
  }
  throw KesalahanParse(this->tokenSaatIni, "Ekspresi tidak valid.");
}