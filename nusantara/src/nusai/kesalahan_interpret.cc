#include "nusad/nusad.h"
#include "nusal/alat.h"
#include "nusal/token.h"
#include <format>
#include <sstream>
#include <vector>
#include "nusai/kesalahan_interpret.h"

Nusai::KesalahanInterpret::KesalahanInterpret(const std::vector<Nusal::Token>& kToken, const std::string& pesan) {
    if(!kToken.empty()) {
        std::vector<Nusai::KesalahanInterpret::Data> kData;
        bool awal = true;
        Nusai::KesalahanInterpret::Data data;
        for(const auto& token : kToken) {
            if(
                data.baris == token.baris.nilai &&
                data.sumber == token.sumber
            ) {
                data.indexKarakterAkhir = token.karakter.nilai + token.nilai.length();
            }else{
                if(!awal) {
                    kData.push_back(data);
                }
                awal = false;
                data.sumber = token.sumber;
                data.baris = token.baris.nilai;
                data.indexKarakterAwal = token.karakter.nilai;
                data.indexKarakterAkhir = token.karakter.nilai + token.nilai.length();
            }
        }
        std::ostringstream ostream;
        for(const auto& data : kData) {
            std::vector<std::string> kKontenPerBaris;
            try {
                kKontenPerBaris = Nusal::bacaFilePerLine(data.sumber);
            } catch (const std::exception& error) {
                kKontenPerBaris = {};
            }
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
        ostream << pesan;
        this->pesan = ostream.str();
    }else{
        this->pesan = pesan;
    }
}

const char* Nusai::KesalahanInterpret::what() const noexcept {
  return this->pesan.c_str();
}