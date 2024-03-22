#include "nusap/kesalahan_parse.h"

#include "nusal/alat.h"

#include <format>
#include <sstream>
#include <string>
#include <vector>

Nusap::KesalahanParse::KesalahanParse(
    const std::unique_ptr<Nusal::Token>& token, const std::string& pesan
) {
  if(token != nullptr) {
    std::vector<std::string> kKontenPerBaris;
    try {
      kKontenPerBaris = Nusal::bacaFilePerLine(token->sumber);
    } catch(const std::exception& error) { kKontenPerBaris = {}; }
    std::ostringstream ostream;
    ostream << std::format(
                   "{}:{}:{}", token->sumber, token->baris.nilai + 1,
                   token->karakter.nilai + 1
               )
            << "\n\n";
    std::string prefix = std::format("{}| ", token->baris.nilai + 1);
    if(kKontenPerBaris.size() > token->baris.nilai) {
      ostream << prefix << kKontenPerBaris[token->baris.nilai] << "\n";
      ostream << std::string(token->karakter.nilai + prefix.length(), ' ')
              << std::string(token->nilai.length(), '^') << "\n";
    }
    ostream << pesan;
    this->pesan = ostream.str();
  } else {
    this->pesan = pesan;
  }
}

const char* Nusap::KesalahanParse::what() const noexcept {
  return this->pesan.c_str();
}
