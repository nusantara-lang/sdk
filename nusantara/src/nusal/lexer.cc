#include "nusal/lexer.h"

#include "nusal/alat.h"

#include <filesystem>
#include <string>

Nusal::Lexer::Lexer(const std::vector<Nusal::TipeTokenData>& tipeTokenData):
    tipeTokenData(tipeTokenData) {}

void Nusal::Lexer::input(const std::string& input) {
  if(this->sumberBersertaInput.contains("tidak diketahui")) {
    this->sumberBersertaInput["tidak diketahui"] =
        this->sumberBersertaInput["tidak diketahui"] + input;
  } else {
    this->sumberBersertaInput["tidak diketahui"] = input;
  }
}

void Nusal::Lexer::input(const std::string& sumber, const std::string& input) {
  if(this->sumberBersertaInput.contains(sumber)) {
    this->sumberBersertaInput[sumber] =
        this->sumberBersertaInput[sumber] + input;
  } else {
    this->sumberBersertaInput[sumber] = input;
  }
}

void Nusal::Lexer::inputFilePath(const std::string& filePath) {
  std::string filePathAbsolute =
      std::filesystem::absolute(filePath).string();
  if(this->sumberBersertaInput.contains(filePathAbsolute)) {
    this->sumberBersertaInput[filePathAbsolute] =
        this->sumberBersertaInput[filePathAbsolute] +
        bacaFile(filePathAbsolute);
  } else {
    this->sumberBersertaInput[filePathAbsolute] =
        bacaFile(filePathAbsolute);
  }
}

std::unique_ptr<Nusal::Token> Nusal::Lexer::ambilToken() {
  for(auto& data : this->sumberBersertaInput) {
    const std::string& sumber = data.first;
    std::string& input = data.second;
    if(input.empty()) {
      this->sumberBersertaInput.erase(sumber);
      if(this->sumberBersertaInput.empty()) { break; }
      this->baris.nilai = 0;
      this->karakter.nilai = 0;
      continue;
    }
    return buatToken(
        input, this->baris, this->karakter, sumber, this->tipeTokenData
    );
  }
  return nullptr;
}