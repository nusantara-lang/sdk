#include "parser/kesalahan_parse.h"

#include "lexer/alat.h"

#include <format>
#include <sstream>
#include <string>
#include <vector>

Parser::KesalahanParse::KesalahanParse(
    const Lexer::Token& token, const std::string& pesan
) {
  std::vector<std::string> kKontenPerBaris;
  try {
    kKontenPerBaris = Lexer::bacaFilePerLine(token.sumber);
  } catch(const std::exception& error) { kKontenPerBaris = {}; }
  std::ostringstream ostream;
  ostream << std::format(
                 "{}:{}:{}", token.sumber, token.baris.nilai + 1,
                 token.karakter.nilai + 1
             )
          << "\n\n";
  std::string prefix = std::format("{}| ", token.baris.nilai + 1);
  if(kKontenPerBaris.size() > token.baris.nilai) {
    ostream << prefix << kKontenPerBaris[token.baris.nilai] << "\n";
    ostream << std::string(token.karakter.nilai + prefix.length(), ' ')
            << std::string(token.nilai.length(), '^') << "\n";
  }
  ostream << "[P] " << pesan;
  this->pesan = ostream.str();
}

const char* Parser::KesalahanParse::what() const noexcept {
  return this->pesan.c_str();
}