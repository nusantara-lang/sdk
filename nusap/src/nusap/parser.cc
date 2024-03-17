#include "nusap/parser.h"

#include "nusal/nusal.h"
#include "nusal/tipe_token.h"
#include "nusal/token.h"
#include "nusap/node.h"
#include "nusap/tipe_node.h"

#include <format>
#include <iostream>
#include <memory>
#include <stdexcept>

nusap::parser::parser():
    lexer(nusal::nusal_data_tipe_token()),
    token_saat_ini(this->lexer.ambil_token()) {}

void nusap::parser::input(const std::string& input) {
  this->lexer.input(input);
}

void nusap::parser::input(const std::string& sumber, const std::string& input) {
  this->lexer.input(sumber, input);
}

void nusap::parser::input_filepath(const std::string& file_path) {
  this->lexer.input_filepath(file_path);
}

void nusap::parser::token_selanjut_nya() {
    this->token_saat_ini = this->lexer.ambil_token();
    std::cout << nusal::ubah_ke_string(*this->token_saat_ini) << "\n";
}

bool nusap::parser::token_saat_ini_adalah(const nusal::tipe_token& tipe) {
  return (this->token_saat_ini != nullptr) &&
         (this->token_saat_ini->tipe == tipe);
}

bool nusap::parser::token_saat_ini_atau_adalah(
    const std::vector<nusal::tipe_token>& tipe
) {
  if(this->token_saat_ini != nullptr) {
    for(const auto& element : tipe) {
      if(this->token_saat_ini->tipe == element) { return true; }
    }
  }
  return false;
}

void nusap::parser::lewati_spasi_putih() {
  while(token_saat_ini_atau_adalah({
      nusal::tipe_token::KEMBALI_KE_AWAL_KARAKTER,
      nusal::tipe_token::BARIS_BARU,
      nusal::tipe_token::TAB,
      nusal::tipe_token::SPASI,
  })) {
    this->token_selanjut_nya();
  }
}

std::unique_ptr<nusap::node> nusap::parser::parse() {
  std::unique_ptr<node> nusantara = std::make_unique<node>(tipe_node::nusantara);
  while(auto token = this->lexer.ambil_token()) {
    this->lewati_spasi_putih();
    if(token->tipe == nusal::tipe_token::TIDAK_DIKETAHUI) {
      throw std::runtime_error(std::format(
          "Nusantara tidak dapat mengenali karakter '{}'.", token->nilai
      ));
    }
    if(this->token_saat_ini != nullptr) {
        nusantara->children.push_back(this->parse_pernyataan());
    }
    this->token_saat_ini = std::make_unique<nusal::token>(*token);
  }
  return nusantara;
}

std::unique_ptr<nusap::node> nusap::parser::parse_pernyataan() {
    std::unique_ptr<node> pernyataan = std::make_unique<node>(tipe_node::pernyataan);
    if(token_saat_ini_adalah(nusal::tipe_token::KATA_KUNCI)) {
        pernyataan->children.push_back(this->parse_membuat_kata_kunci());
    }else{
        throw std::runtime_error("Nusantara tidak dapat memparse pernyataan yang diberikan.");
    }
    return pernyataan;
}

std::unique_ptr<nusap::node> nusap::parser::parse_membuat_kata_kunci() {
    std::unique_ptr<node> membuat_kata_kunci = std::make_unique<node>(tipe_node::membuat_kata_kunci);
    membuat_kata_kunci->children.push_back(std::make_unique<node>(tipe_node::token, std::make_unique<nusal::token>(*this->token_saat_ini)));
    this->token_selanjut_nya();
    while(this->token_saat_ini_adalah(nusal::tipe_token::HURUF)) {
      membuat_kata_kunci->children.push_back(std::make_unique<node>(tipe_node::token, std::make_unique<nusal::token>(*this->token_saat_ini)));
      this->token_selanjut_nya();
    }
    if(this->token_saat_ini_adalah(nusal::tipe_token::TITIK_KOMA)) {
      membuat_kata_kunci->children.push_back(std::make_unique<node>(tipe_node::token, std::make_unique<nusal::token>(*this->token_saat_ini)));
      this->token_selanjut_nya();
    }else{
      throw std::runtime_error("Jangan lupa titik koma");
    }
    return membuat_kata_kunci;
}
