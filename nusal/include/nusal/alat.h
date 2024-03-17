#pragma once

#include "nusal/tipe_token_data.h"
#include "nusal/token.h"

#include <memory>
#include <regex>
#include <vector>

namespace nusal {

  template<typename T>
  std::unique_ptr<token<T>> buat_token(
      std::string& input, baris& baris, karakter& karakter,
      const std::string& sumber, const std::vector<tipe_token_data<T>>& datas
  ) {
    if(input.empty()) { return nullptr; }
    token<T> tkn;
    tkn.sumber = sumber;
    tkn.baris = baris;
    size_t karakter_temp = karakter.nilai;
    tkn.karakter.nilai = karakter_temp;
    for(const auto& data : datas) {
      std::regex pola("^" + data.pola);
      std::smatch matches;
      if(std::regex_search(
             input, matches, pola, std::regex_constants::match_continuous
         )) {
        tkn.tipe = data.tipe;
        tkn.nama = data.nama;
        tkn.nilai = matches.str();
        for(const char& character : tkn.nilai) {
          karakter.nilai++;
          if(character == '\n') {
            baris.nilai++;
            karakter.nilai = 0;
          }
        }
        input.replace(0, tkn.nilai.length(), "");
        return std::make_unique<token<T>>(tkn);
      }
    }
    tkn.nilai = input[0];
    input.replace(0, tkn.nilai.length(), "");
    return std::make_unique<token<T>>(tkn);
  }

  std::string baca_file(const std::string& file_path);

} // namespace nusal
