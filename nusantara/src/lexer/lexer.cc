#include "lexer/lexer.h"

#include "lexer/alat.h"
#include "lexer/tipe_token.h"
#include "lexer/token.h"

#include <filesystem>
#include <iostream>
#include <regex>
#include <string>

Lexer::Lexer::Lexer(
    std::vector<TipeToken>& tipeTokens,
    const size_t& indexTipeTokenTidakDiketahui,
    const size_t& indexTipeTokenAkhirDariFile
):
    tipeTokens(tipeTokens),
    baris(0), karakter(0),
    indexTipeTokenTidakDiketahui(indexTipeTokenTidakDiketahui),
    indexTipeTokenAkhirDariFile(indexTipeTokenAkhirDariFile) {}

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

Lexer::Token Lexer::Lexer::tokenSelanjutNya() {
  Token token(
      this->tipeTokens.get()[this->indexTipeTokenAkhirDariFile],
      "tidak diketahui", this->baris, this->karakter, "\0"
  );
  for(auto& data : this->sumberBersertaInput) {
    const std::string& sumber = data.first;
    std::string& input = data.second;
    if(input.empty()) {
      this->sumberBersertaInput.erase(sumber);
      token.setSumber(sumber);
      token.setBaris(this->baris.nilai);
      token.setKarakter(this->karakter.nilai);
      if(this->sumberBersertaInput.empty()) { break; }
      this->baris.nilai = 0;
      this->karakter.nilai = 0;
      continue;
    }
    if(const auto& tokenPtr = this->generateToken(input, sumber)) {
      token = *tokenPtr;
    }
    return token;
  }
  return this->sumberBersertaInput.empty() ? token : this->tokenSelanjutNya();
}

const std::vector<Lexer::TipeToken>& Lexer::Lexer::getTipeTokens() const {
  return this->tipeTokens;
}

std::unique_ptr<Lexer::Token>
Lexer::Lexer::generateToken(std::string& input, const std::string& sumber) {
  if(input.empty()) { return nullptr; }
  Token::Karakter karakterTemp = this->karakter;
  Token token(
      this->tipeTokens.get()[this->indexTipeTokenTidakDiketahui], sumber,
      this->baris, karakterTemp, ""
  );
  for(const auto& tipeToken : this->tipeTokens.get()) {
    if(tipeToken.getNama() ==
           this->tipeTokens.get()[this->indexTipeTokenTidakDiketahui].getNama(
           ) ||
       tipeToken.getNama() ==
           this->tipeTokens.get()[this->indexTipeTokenAkhirDariFile].getNama(
           )) {
      continue;
    }
    std::regex pola("^" + tipeToken.getPola());
    std::smatch matches;
    if(std::regex_search(
           input, matches, pola, std::regex_constants::match_continuous
       )) {
      token.setTipe(tipeToken);
      token.setNilai(matches.str());
      for(const char& character : token.getNilai()) {
        this->karakter.nilai++;
        if(character == '\n') {
          this->baris.nilai++;
          this->karakter.nilai = 0;
        }
      }
      input.replace(0, token.getNilai().length(), "");
      return std::make_unique<Token>(token);
    }
  }
  token.setNilai(input[0]);
  this->karakter.nilai++;
  input.replace(0, 1, "");
  return std::make_unique<Token>(token);
}
