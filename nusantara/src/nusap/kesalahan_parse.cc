#include "nusap/kesalahan_parse.h"

#include "nusal/alat.h"

#include <format>
#include <sstream>
#include <string>
#include <vector>

Nusap::KesalahanParse::KesalahanParse(
    const Nusal::Token& token, const std::string& pesan
) {
  std::vector<std::string> kKontenPerBaris;
  try {
    kKontenPerBaris = Nusal::bacaFilePerLine(token.sumber);
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

const char* Nusap::KesalahanParse::what() const noexcept {
  return this->pesan.c_str();
}
