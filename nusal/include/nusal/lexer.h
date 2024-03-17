#pragma once

#include "nusal/alat.h"
#include "nusal/tipe_token_data.h"
#include "nusal/token.h"
#include <memory>
#include <map>
#include <vector>

namespace nusal {

		template<typename T>
		class lexer {
        public:
            lexer(const std::vector<tipe_token_data<T>>& tipe_token_data): tipe_token_data(tipe_token_data) {}

            void input(const std::string& input) {
						  if(this->sumber_berserta_input.contains(this->sumber_tidak_diketahui)) {
						    this->sumber_berserta_input[this->sumber_tidak_diketahui] = this->sumber_berserta_input[this->sumber_tidak_diketahui] + input;
						  }else{
						    this->sumber_berserta_input[this->sumber_tidak_diketahui] = input;
						  }
						}

            void input(const std::string& sumber, const std::string& input) {
						  if(this->sumber_berserta_input.contains(sumber)) {
						    this->sumber_berserta_input[sumber] = this->sumber_berserta_input[sumber] + input;
						  }else{
						    this->sumber_berserta_input[sumber] = input;
						  }
						}

            void input_filepath(const std::string& file_path) {
							if(this->sumber_berserta_input.contains(file_path)) {
						    this->sumber_berserta_input[file_path] = this->sumber_berserta_input[file_path] + baca_file(file_path);
						  }else{
						    this->sumber_berserta_input[file_path] = baca_file(file_path);
						  }
						}

            std::unique_ptr<token<T>> ambil_token() {
						  for(auto& data : this->sumber_berserta_input) {
							    const std::string& sumber = data.first;
							    std::string& input = data.second;
							    if(input.empty()) {
						      this->sumber_berserta_input.erase(sumber);
						      if(this->sumber_berserta_input.empty()) {
						        break;
						      }
					      	this->baris = 0;
					    	  this->karakter = 0;
					  	    continue;
						    }
						    return buat_token(
						      input, 
						      this->baris, 
						      this->karakter, 
						      sumber, 
						      this->tipe_token_data
						    );
						  }
					  	return nullptr;
						}

            constexpr static const std::string sumber_tidak_diketahui = "tidak diketahui";

        private:
						std::vector<tipe_token_data<T>> tipe_token_data;

            size_t baris = 0;

            size_t karakter = 0;

            std::map<std::string, std::string> sumber_berserta_input = {};
    };

}
