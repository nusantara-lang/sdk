#include "nusal/lexer.h"

#include "nusal/alat.h"

nusal::lexer::lexer(const std::vector<nusal::tipe_token_data>& tipe_token_data):
    tipe_token_data(tipe_token_data) {}

void nusal::lexer::input(const std::string& input) {
  if(this->sumber_berserta_input.contains("tidak diketahui")) {
    this->sumber_berserta_input["tidak diketahui"] =
        this->sumber_berserta_input["tidak diketahui"] + input;
  } else {
    this->sumber_berserta_input["tidak diketahui"] = input;
  }
}

void nusal::lexer::input(const std::string& sumber, const std::string& input) {
  if(this->sumber_berserta_input.contains(sumber)) {
    this->sumber_berserta_input[sumber] =
        this->sumber_berserta_input[sumber] + input;
  } else {
    this->sumber_berserta_input[sumber] = input;
  }
}

void nusal::lexer::input_filepath(const std::string& file_path) {
  if(this->sumber_berserta_input.contains(file_path)) {
    this->sumber_berserta_input[file_path] =
        this->sumber_berserta_input[file_path] + baca_file(file_path);
  } else {
    this->sumber_berserta_input[file_path] = baca_file(file_path);
  }
}

std::unique_ptr<nusal::token> nusal::lexer::ambil_token() {
  for(auto& data : this->sumber_berserta_input) {
    const std::string& sumber = data.first;
    std::string& input = data.second;
    if(input.empty()) {
      this->sumber_berserta_input.erase(sumber);
      if(this->sumber_berserta_input.empty()) { break; }
      this->baris.nilai = 0;
      this->karakter.nilai = 0;
      continue;
    }
    return buat_token(
        input, this->baris, this->karakter, sumber, this->tipe_token_data
    );
  }
  return nullptr;
}