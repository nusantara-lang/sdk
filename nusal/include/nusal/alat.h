#pragma once

#include "nusal/token.h"
#include "nusal/tipe_token_data.h"
#include <memory>
#include <vector>
#include <regex>

namespace nusal {

	template<typename T>
	std::unique_ptr<token<T>> buat_token(
    std::string& input, 
    size_t& baris,
    size_t& karakter,
    const std::string& sumber,
    const std::vector<tipe_token_data<T>>& datas
  ) 
	{
    if(input.empty()) {
      return nullptr;
    }
    token<T> tkn;
    tkn.sumber = sumber;
    tkn.baris = baris;
    size_t karakter_temp = karakter;
    tkn.karakter = karakter_temp;
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
            return std::make_unique<token<T>>(tkn);
        }
    }
    tkn.nilai = input[0];
    input.replace(0, tkn.nilai.length(), "");
    return std::make_unique<token<T>>(tkn);
	}

	std::string baca_file(const std::string& file_path);

}
