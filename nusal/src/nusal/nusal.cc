#include "nusal/nusal.h"
#include <format>
#include <memory>
#include <regex>
#include <string>

std::string nusal::ubah_ke_string(const tipe_token& tipe_token) {
    switch (tipe_token) {
    case tipe_token::spasi:
      return "spasi";
    case tipe_token::baris_baru:
      return "baris_baru";
    case tipe_token::tab:
      return "tab";
    case tipe_token::angka:
      return "angka";
    case tipe_token::simbol:
      return "simbol";
    case tipe_token::huruf:
      return "huruf";
    case tipe_token::akhir:
      return "akhir";
    case tipe_token::tidak_diketahui:
      return "tidak_diketahui";
    }
}

nusal::token::token(
    const tipe_token& tipe,
    const std::string& nama,
    const std::string& sumber,
    const size_t& baris,
    const size_t& karakter,
    const std::string& nilai
):
    tipe(tipe),
    nama(nama),
    sumber(sumber),
    baris(baris),
    karakter(karakter),
    nilai(nilai)
{}

std::string nusal::ubah_ke_string(const token& token) {
  return std::format("{}:{}:{} {:<10} {}", token.sumber, token.baris, token.karakter, token.nama, token.nilai);
}

nusal::tipe_token_data::tipe_token_data(
    const tipe_token& tipe,
    const std::string& nama,
    const std::string& pola
):
    tipe(tipe),
    nama(nama),
    pola(pola)
{}

std::unique_ptr<nusal::token> nusal::buat_token(
    std::string& input,
    size_t& baris,
    size_t& karakter,
    const std::string& sumber,
    const std::vector<tipe_token_data>& datas,
    bool& akhir
) {
    if(input.empty() && akhir) {
      return nullptr;
    }
    token tkn;
    tkn.sumber = sumber;
    tkn.baris = baris;
    size_t karakter_temp = karakter;
    tkn.karakter = karakter_temp;
    if(input.empty() && !akhir) {
      tkn.tipe = tipe_token::akhir;
      tkn.nama = ubah_ke_string(tkn.tipe);
      tkn.nilai = "\0";
      akhir = true;
      return std::make_unique<token>(tkn);
    }
    for(const auto& data : datas) {
        std::regex pola("^" + data.pola);
        std::smatch matches;
        if(std::regex_search(input, matches, pola,std::regex_constants::match_continuous)) {
            tkn.tipe = data.tipe;
            tkn.nama = data.nama;
            tkn.nilai = matches.str();
            for(const char &character : tkn.nilai) {
                karakter++;
                if(character == '\n') {
                    baris++;
                    karakter = 0;
                }
            }
            input.replace(0, tkn.nilai.length(), "");
            return std::make_unique<token>(tkn);
        }
    }
    tkn.nilai = input[0];
    input.replace(0, tkn.nilai.length(), "");
    return std::make_unique<token>(tkn);
}

const std::string nusal::lexer::sumber_tidak_diketahui = "tidak diketahui";

void nusal::lexer::input(const std::string& input) {
  if(this->sumber_berserta_input.contains(this->sumber_tidak_diketahui)) {
    this->sumber_berserta_input[this->sumber_tidak_diketahui] = this->sumber_berserta_input[this->sumber_tidak_diketahui] + input;
  }else{
    this->sumber_berserta_input[this->sumber_tidak_diketahui] = input;
  }
}

void nusal::lexer::input(const std::string& sumber, const std::string& input) {
  if(this->sumber_berserta_input.contains(sumber)) {
    this->sumber_berserta_input[sumber] = this->sumber_berserta_input[sumber] + input;
  }else{
    this->sumber_berserta_input[sumber] = input;
  }
}

std::unique_ptr<nusal::token> nusal::lexer::ambil_token() {
  for(auto& data : this->sumber_berserta_input) {
    const std::string& sumber = data.first;
    std::string& input = data.second;
    if(input.empty() && this->akhir) {
      this->sumber_berserta_input.erase(sumber);
      if(this->sumber_berserta_input.empty()) {
        break;
      }
      this->baris = 0;
      this->karakter = 0;
      this->akhir = false;
      continue;
    }
    return buat_token(
      input, 
      this->baris, 
      this->karakter, 
      sumber, 
      nusa_data_tipe_token,
      this->akhir
    );
  }
  return nullptr;
}