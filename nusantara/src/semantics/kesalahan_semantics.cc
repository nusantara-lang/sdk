#include "semantics/kesalahan_semantics.h"

#include "lexer/alat.h"
#include "lexer/token.h"

#include <format>
#include <sstream>
#include <vector>

Semantics::KesalahanSemantics::KesalahanSemantics(
    const std::vector<Lexer::Token>& kToken, const std::string& pesan
) {
  if(!kToken.empty()) {
    std::vector<Semantics::KesalahanSemantics::Data> kData;
    bool awal = true;
    Semantics::KesalahanSemantics::Data data;
    for(const auto& token : kToken) {
      if(data.baris == token.getBaris() && data.sumber == token.getSumber()) {
        data.indexKarakterAkhir = token.getKarakter() + token.getNilai().size();
      } else {
        if(!awal) { kData.push_back(data); }
        awal = false;
        data.sumber = token.getSumber();
        data.baris = token.getBaris();
        data.indexKarakterAwal = token.getKarakter();
        data.indexKarakterAkhir = token.getKarakter() + token.getNilai().size();
      }
    }
    kData.push_back(data);
    std::ostringstream ostream;
    for(const auto& data : kData) {
      std::vector<std::string> kKontenPerBaris;
      try {
        kKontenPerBaris = Lexer::bacaFilePerLine(data.sumber);
      } catch(const std::exception& error) { kKontenPerBaris = {}; }
      ostream << std::format(
                     "{}:{}:{}", data.sumber, data.baris + 1,
                     data.indexKarakterAwal + 1
                 )
              << "\n\n";
      std::string prefix = std::format("{}| ", data.baris + 1);
      if(kKontenPerBaris.size() >= data.baris) {
        ostream << prefix << kKontenPerBaris[data.baris] << "\n";
        ostream << std::string(data.indexKarakterAwal + prefix.length(), ' ')
                << std::string(data.indexKarakterAkhir, '^') << "\n";
      }
    }
    ostream << "[S] " << pesan;
    this->pesan = ostream.str();
  } else {
    this->pesan = "[S] " + pesan;
  }
}

const char* Semantics::KesalahanSemantics::what() const noexcept {
  return this->pesan.c_str();
}
