#include "lexer/token_stream.h"

#include <algorithm>

Lexer::TokenStream::TokenStream(Lexer& lexer): lexer(lexer) {}

bool Lexer::TokenStream::tokenSaatIniAdalah(const std::string& tipe) {
  return this->tokenSaatIni.getTipe().getNama() == tipe;
}

bool Lexer::TokenStream::tokenSaatIniAdalah(const std::vector<std::string>& tipe
) {
  return std::ranges::any_of(tipe, [&](const auto& element) {
    return this->tokenSaatIniAdalah(element);
  });
}

const Lexer::Token& Lexer::TokenStream::tokenSelanjutNya(const bool& skip) {
  this->tokenSaatIni = this->lexer.get().tokenSelanjutNya();
  while(skip && this->tokenSaatIni.getTipe().isSkip()) {
    this->tokenSaatIni = this->lexer.get().tokenSelanjutNya();
  }
  return this->tokenSaatIni;
}

const Lexer::Token& Lexer::TokenStream::getTokenSaatIni() {
  return this->tokenSaatIni;
}
