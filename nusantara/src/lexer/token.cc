#include "lexer/token.h"

#include "lexer/tipe_token.h"

#include <format>

Lexer::baris::baris(const size_t& nilai): nilai(nilai) {}

Lexer::karakter::karakter(const size_t& nilai): nilai(nilai) {}

Lexer::Token::Token(
    const TipeToken& tipe, std::string sumber, const Lexer::baris& baris,
    const Lexer::karakter& karakter, std::string nilai
):
    tipe(tipe),
    sumber(std::move(sumber)), baris(baris), karakter(karakter),
    nilai(std::move(nilai)) {}

std::string Lexer::ubahKeString(const Token& token) {
  return std::format(
      "{}:{}:{} {} {}", token.sumber, token.baris.nilai + 1,
      token.karakter.nilai + 1, ubahKeString(token.tipe),
      (token.nilai == "\n")      ? "\\n"
      : (token.nilai == "\t")    ? "\\t"
      : (token.nilai == "\r")    ? "\\r"
      : (token.nilai[0] == '\0') ? "\\0"
                                 : token.nilai
  );
}
