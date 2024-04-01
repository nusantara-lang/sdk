#include "lexer/token.h"

#include "lexer/tipe_token.h"

#include <format>
#include <string>

Lexer::Token::Baris::Baris(const size_t& nilai): nilai(nilai) {}

Lexer::Token::Karakter::Karakter(const size_t& nilai): nilai(nilai) {}

Lexer::Token::Token() = default;

Lexer::Token::Token(
    const TipeToken& tipe, std::string sumber, const Baris& baris,
    const Karakter& karakter, std::string nilai
):
    tipe(tipe),
    sumber(std::move(sumber)), baris(baris.nilai), karakter(karakter.nilai),
    nilai(std::move(nilai)) {}

std::string Lexer::Token::ubahKeString() const {
  return std::format(
      "{}:{}:{} {} {}", this->sumber, this->baris + 1, this->karakter + 1,
      this->tipe.ubahKeString(),
      (this->nilai == "\n")      ? "\\n"
      : (this->nilai == "\t")    ? "\\t"
      : (this->nilai == "\r")    ? "\\r"
      : (this->nilai[0] == '\0') ? "\\0"
                                 : this->nilai
  );
}

const Lexer::TipeToken& Lexer::Token::getTipe() const { return this->tipe; }

const std::string& Lexer::Token::getSumber() const { return this->sumber; }

const size_t& Lexer::Token::getBaris() const { return this->baris; }

const size_t& Lexer::Token::getKarakter() const { return this->karakter; }

const std::string& Lexer::Token::getNilai() const { return this->nilai; }

void Lexer::Token::setTipe(const TipeToken& tipe) { this->tipe = tipe; }

void Lexer::Token::setSumber(const std::string& sumber) {
  this->sumber = sumber;
}

void Lexer::Token::setBaris(const size_t& baris) { this->baris = baris; }

void Lexer::Token::setKarakter(const size_t& karakter) {
  this->karakter = karakter;
}

void Lexer::Token::setNilai(const std::string& nilai) { this->nilai = nilai; }

void Lexer::Token::setNilai(const char& nilai) { this->nilai = nilai; }
