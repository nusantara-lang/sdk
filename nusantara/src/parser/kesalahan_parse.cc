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
    kKontenPerBaris = Lexer::bacaFilePerLine(token.getSumber());
  } catch(const std::exception& error) { kKontenPerBaris = {}; }
  std::ostringstream ostream;
  ostream << std::format(
                 "{}:{}:{}", token.getSumber(), token.getBaris() + 1,
                 token.getKarakter() + 1
             )
          << "\n\n";
  std::string prefix = std::format("{}| ", token.getBaris() + 1);
  if(kKontenPerBaris.size() > token.getBaris()) {
    ostream << prefix << kKontenPerBaris[token.getBaris()] << "\n";
    ostream << std::string(token.getKarakter() + prefix.length(), ' ')
            << std::string(
                   !token.getNilai().empty() ? token.getNilai().size() : 1, '^'
               )
            << "\n";
  }
  ostream << "[P] " << pesan;
  this->pesan = ostream.str();
}

const char* Parser::KesalahanParse::what() const noexcept {
  return this->pesan.c_str();
}
