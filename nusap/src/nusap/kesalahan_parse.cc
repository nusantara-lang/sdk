#include "nusap/kesalahan_parse.h"

#include "nusal/alat.h"

#include <format>
#include <sstream>
#include <string>
#include <vector>

nusap::kesalahan_parser::kesalahan_parser(
    const nusal::token& token, const std::string& pesan
) {

  std::string konten = nusal::baca_file(token.sumber);
  std::vector<std::string> kumpulan_konten_perbaris;
  std::stringstream stream(konten);
  std::string konten_perbaris;
  while(std::getline(stream, konten_perbaris, '\n')) {
    kumpulan_konten_perbaris.push_back(konten_perbaris);
  }

  std::ostringstream ostream;
  ostream << std::format(
                 "{}:{}:{}", token.sumber, token.baris.nilai + 1,
                 token.karakter.nilai + 1
             )
          << "\n\n";
  std::string prefix = std::format("{}| ", token.baris.nilai + 1);
  ostream << prefix << kumpulan_konten_perbaris[token.baris.nilai] << "\n";
  ostream << std::string(token.karakter.nilai + prefix.length(), ' ')
          << std::string(token.nilai.length(), '^') << "\n";
  ostream << pesan << "\n";
  this->pesan = ostream.str();
}

const char* nusap::kesalahan_parser::what() const noexcept {
  return this->pesan.c_str();
}
