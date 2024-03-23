#include "lexer/lexer.h"

#include "lexer/alat.h"
#include "lexer/tipe_token_data.h"
#include "lexer/token.h"

#include <filesystem>
#include <string>

const std::vector<Lexer::TipeTokenData>& Lexer::nusantaraDataTipeToken() {
  static std::vector<TipeTokenData> output = {
      {TipeToken::kembali_ke_awal_karakter, "[\r]"                  },
      {TipeToken::baris_baru,               "[\n]"                  },
      {TipeToken::tab,                      "[\t]"                  },
      {TipeToken::spasi,                    "[ ]"                   },
      {TipeToken::komentar_satu_baris,      "//[^\n]*"              },
      {TipeToken::komentar_banyak_baris,    "/\\*[^/*]*\\*/"        },
      {TipeToken::muat,                     "muat"                  },
      {TipeToken::luar,                     "luar"                  },
      {TipeToken::bilangan,                 "bilangan"              },
      {TipeToken::teks,                     "teks"                  },
      {TipeToken::dinamis,                  "dinamis"               },
      {TipeToken::identifikasi,             "[a-zA-Z_][a-zA-Z0-9_]*"},
      {TipeToken::angka,                    "[0-9]"                 },
      {TipeToken::tambah,                   "[+]"                   },
      {TipeToken::tanda_hubung,             "-"                     },
      {TipeToken::asteris,                  "[*]"                   },
      {TipeToken::garis_miring,             "/"                     },
      {TipeToken::persen,                   "[%]"                   },
      {TipeToken::sama_dengan,              "="                     },
      {TipeToken::seru,                     "!"                     },
      {TipeToken::dolar,                    "[$]"                   },
      {TipeToken::garis_bawah,              "_"                     },
      {TipeToken::koma,                     ","                     },
      {TipeToken::titik,                    "\\."                   },
      {TipeToken::titik_dua,                ":"                     },
      {TipeToken::titik_koma,               ";"                     },
      {TipeToken::kutip_satu,               "'"                     },
      {TipeToken::garis_vertikal,           R"(\|)"                 },
      {TipeToken::kurung_buka,              R"(\()"                 },
      {TipeToken::kurung_tutup,             R"(\))"                 },
      {TipeToken::kurung_siku_buka,         R"(\[)"                 },
      {TipeToken::kurung_siku_tutup,        R"(\])"                 },
      {TipeToken::kurung_kurawal_buka,      R"(\{)"                 },
      {TipeToken::kurung_kurawal_tutup,     R"(\})"                 },
      {TipeToken::garis_miring_terbalik,    R"(\\)"                 },
      {TipeToken::karakter,                 "."                     },
  };
  return output;
}

Lexer::Lexer::Lexer(const std::vector<TipeTokenData>& tipeTokenData):
    tipeTokenData(tipeTokenData) {}

void Lexer::Lexer::input(const std::string& input) {
  if(this->sumberBersertaInput.contains("tidak diketahui")) {
    this->sumberBersertaInput["tidak diketahui"] =
        this->sumberBersertaInput["tidak diketahui"] + input;
  } else {
    this->sumberBersertaInput["tidak diketahui"] = input;
  }
}

void Lexer::Lexer::input(const std::string& sumber, const std::string& input) {
  if(this->sumberBersertaInput.contains(sumber)) {
    this->sumberBersertaInput[sumber] =
        this->sumberBersertaInput[sumber] + input;
  } else {
    this->sumberBersertaInput[sumber] = input;
  }
}

void Lexer::Lexer::inputFilePath(const std::string& filePath) {
  std::string filePathAbsolute = std::filesystem::absolute(filePath).string();
  if(this->sumberBersertaInput.contains(filePathAbsolute)) {
    this->sumberBersertaInput[filePathAbsolute] =
        this->sumberBersertaInput[filePathAbsolute] +
        bacaFile(filePathAbsolute);
  } else {
    this->sumberBersertaInput[filePathAbsolute] = bacaFile(filePathAbsolute);
  }
}

Lexer::Token Lexer::Lexer::ambilToken() {
  Token token;
  token.tipe = TipeToken::akhir_dari_file;
  token.nilai = '\0';
  for(auto& data : this->sumberBersertaInput) {
    const std::string& sumber = data.first;
    std::string& input = data.second;
    if(input.empty()) {
      this->sumberBersertaInput.erase(sumber);
      token.sumber = sumber;
      token.baris = this->baris;
      token.karakter = this->karakter;
      if(this->sumberBersertaInput.empty()) { break; }
      this->baris.nilai = 0;
      this->karakter.nilai = 0;
      continue;
    }
    if(const auto& tokenPtr = buatToken(
           input, this->baris, this->karakter, sumber, this->tipeTokenData
       )) {
      token = *tokenPtr;
    }
    return token;
  }
  return this->sumberBersertaInput.empty() ? token : this->ambilToken();
}
