#include "nusap/parser.h"

#include "lexer/lexer.h"
#include "lexer/lexer.h"
#include "lexer/tipe_token.h"
#include "lexer/token.h"
#include "nusap/kesalahan_parse.h"
#include "nusap/node.h"
#include "nusap/tipe_node.h"

#include <algorithm>
#include <format>
#include <memory>

Nusap::Parser::Parser(): lexer(Lexer::nusantaraDataTipeToken()) {}

void Nusap::Parser::input(const std::string& input) {
  this->lexer.input(input);
}

void Nusap::Parser::input(const std::string& sumber, const std::string& input) {
  this->lexer.input(sumber, input);
}

void Nusap::Parser::inputFilePath(const std::string& filePath) {
  this->lexer.inputFilePath(filePath);
}

const std::vector<Lexer::TipeToken>& Nusap::Parser::skipTipeToken() {
  static std::vector<Lexer::TipeToken> hasil = {
      Lexer::TipeToken::kembali_ke_awal_karakter,
      Lexer::TipeToken::baris_baru,
      Lexer::TipeToken::tab,
      Lexer::TipeToken::spasi,
      Lexer::TipeToken::komentar_satu_baris,
      Lexer::TipeToken::komentar_banyak_baris
  };
  return hasil;
}

void Nusap::Parser::tokenSelanjutNya() {
  this->tokenSaatIni = this->lexer.ambilToken();
}

bool Nusap::Parser::tokenSaatIniAdalah(const Lexer::TipeToken& tipe) {
  return this->tokenSaatIni.tipe == tipe;
}

bool Nusap::Parser::tokenSaatIniAdalah(const std::vector<Lexer::TipeToken>& tipe
) {
  return std::ranges::any_of(tipe, [&](const auto& element) {
    return this->tokenSaatIniAdalah(element);
  });
}

bool Nusap::Parser::mengharapkanToken(
    const std::unique_ptr<Node>& aturan, const Lexer::TipeToken& tipe,
    const std::function<std::unique_ptr<Node>()>& callback, const bool& skip,
    const std::string& pesanKesalahan
) {
  if(skip) { this->parseSkipToken(); }
  bool hasil = this->tokenSaatIniAdalah(tipe);
  if(hasil) {
    auto node = callback();
    if(node->tipe == TipeNode::token) {
      this->tokenSelanjutNya();
      if(skip) { this->parseSkipToken(); }
    }
    aturan->children.push_back(std::move(node));
  }else{
    if(!pesanKesalahan.empty()) {
      throw KesalahanParse(
        this->tokenSaatIni, 
        pesanKesalahan
      );
    }
  }
  return hasil;
}

bool Nusap::Parser::mengharapkanToken(
    const std::unique_ptr<Node>& aturan,
    const std::vector<Lexer::TipeToken>& tipe,
    const std::function<std::unique_ptr<Node>()>& callback, const bool& skip
) {
  return std::ranges::any_of(tipe, [&](const auto& element) {
    return this->mengharapkanToken(aturan, element, callback, skip);
  });
}

std::unique_ptr<Nusap::Node>
Nusap::Parser::buatNodeAturan(const Nusap::TipeNode& tipe) {
  return std::make_unique<Node>(tipe);
}

std::unique_ptr<Nusap::Node> Nusap::Parser::buatNodeToken() {
  return std::make_unique<Node>(
      TipeNode::token, std::make_unique<Lexer::Token>(this->tokenSaatIni)
  );
}

void Nusap::Parser::parseSkipToken() {
  while(this->tokenSaatIniAdalah(this->skipTipeToken())) {
    this->tokenSelanjutNya();
  }
}

// PARSE AREA

std::unique_ptr<Nusap::Node> Nusap::Parser::parse() {
  std::unique_ptr<Nusap::Node> nusantara = buatNodeAturan(TipeNode::nusantara);
  this->tokenSelanjutNya();
  this->parseSkipToken();
  while(this->tokenSaatIni.tipe != Lexer::TipeToken::akhir_dari_file) {
    if(this->tokenSaatIniAdalah(Lexer::TipeToken::tidak_diketahui)) {
      throw Nusap::KesalahanParse(
          this->tokenSaatIni,
          std::format(
              "Nusantara tidak dapat mengenali karakter '{}'.",
              this->tokenSaatIni.nilai
          )
      );
    }
    nusantara->children.push_back(this->parsePernyataan());
  }
  return nusantara;
}

std::unique_ptr<Nusap::Node> Nusap::Parser::parsePernyataan() {
  std::unique_ptr<Nusap::Node> pernyataan =
      buatNodeAturan(TipeNode::pernyataan);
  if(this->mengharapkanToken(pernyataan, Lexer::TipeToken::muat, [&]() {
       return this->parseMuatFile();
     })) {
    if(!this->mengharapkanToken(
           pernyataan, Lexer::TipeToken::titik_koma,
           [&]() { return this->buatNodeToken(); }
       )) {
      throw KesalahanParse(this->tokenSaatIni, "Jangan lupa titik koma.");
    }
    return pernyataan;
  }
  if(this->mengharapkanToken(
         pernyataan,
         {Lexer::TipeToken::tanda_hubung, Lexer::TipeToken::angka,
          Lexer::TipeToken::kutip_satu},
         [&]() { return this->parseEkspresi(); }
     )) {
    if(!this->mengharapkanToken(
           pernyataan, Lexer::TipeToken::titik_koma,
           [&]() { return this->buatNodeToken(); }
       )) {
      throw KesalahanParse(this->tokenSaatIni, "Jangan lupa titik koma.");
    }
    return pernyataan;
  }
  throw KesalahanParse(this->tokenSaatIni, "Pernyataan tidak valid");
}

std::unique_ptr<Nusap::Node> Nusap::Parser::parseMuatFile() {
  std::unique_ptr<Nusap::Node> muatFile = buatNodeAturan(TipeNode::muat_file);
  if(!this->mengharapkanToken(muatFile, Lexer::TipeToken::muat, [&]() {
       return this->buatNodeToken();
     })) {
    throw KesalahanParse(
        this->tokenSaatIni,
        "Untuk memuat file harus di awali dengan kata kunci 'muat'."
    );
  }
  if(!this->mengharapkanToken(muatFile, Lexer::TipeToken::kutip_satu, [&]() {
       return this->parseNilaiTeks();
     })) {
    throw KesalahanParse(this->tokenSaatIni, "Lokasi file tidak valid.");
  }
  return muatFile;
}

std::unique_ptr<Nusap::Node> Nusap::Parser::parseNilaiTeks() {
  std::unique_ptr<Nusap::Node> nilaiTeks = buatNodeAturan(TipeNode::nilai_teks);
  if(!this->mengharapkanToken(nilaiTeks, Lexer::TipeToken::kutip_satu, [&]() {
       return this->buatNodeToken();
     })) {
    throw KesalahanParse(this->tokenSaatIni, "Teks harus di awali kutip 1.");
  }
  while(!tokenSaatIniAdalah(Lexer::TipeToken::kutip_satu)) {
    if(mengharapkanToken(
           nilaiTeks, Lexer::TipeToken::garis_miring_terbalik,
           [&]() { return this->buatNodeToken(); }, false
       )) {
      if(mengharapkanToken(
             nilaiTeks, Lexer::TipeToken::dolar,
             [&]() { return this->buatNodeToken(); }, false
         )) {
        continue;
      }
    } else if(mengharapkanToken(
                  nilaiTeks, Lexer::TipeToken::dolar,
                  [&]() { return this->buatNodeToken(); }, false
              )) {
      if(mengharapkanToken(
             nilaiTeks, Lexer::TipeToken::identifikasi,
             [&]() { return this->buatNodeToken(); }, false
         )) {
        continue;
      } else if(mengharapkanToken(
                    nilaiTeks, Lexer::TipeToken::kurung_kurawal_buka,
                    [&]() { return this->buatNodeToken(); }, false
                )) {
        if(!this->mengharapkanToken(
               nilaiTeks,
               {Lexer::TipeToken::tanda_hubung, Lexer::TipeToken::angka,
                Lexer::TipeToken::kutip_satu},
               [&]() { return this->parseEkspresi(); }
           )) {
          throw KesalahanParse(
              this->tokenSaatIni, "Ekspresi pada teks interpolasi tidak valid."
          );
        }
        if(!mengharapkanToken(
               nilaiTeks, Lexer::TipeToken::kurung_kurawal_tutup,
               [&]() { return this->buatNodeToken(); }, false
           )) {
          throw KesalahanParse(
              this->tokenSaatIni,
              "Setelah kurung kurawal buka harusnya kurung kurawal tutup."
          );
        }
        continue;
      } else {
        throw KesalahanParse(
            this->tokenSaatIni, "Teks interpolasi harus berisi nama variabel "
                                "atau sebuah ekspresi di dalam kurung kurawal."
        );
      }
    }
    nilaiTeks->children.push_back(this->buatNodeToken());
    this->tokenSelanjutNya();
  }
  if(!this->mengharapkanToken(nilaiTeks, Lexer::TipeToken::kutip_satu, [&]() {
       return this->buatNodeToken();
     })) {
    throw KesalahanParse(this->tokenSaatIni, "Teks harus di akhiri kutip 1.");
  }
  return nilaiTeks;
}

std::unique_ptr<Nusap::Node> Nusap::Parser::parseNilaiBilangan() {
  std::unique_ptr<Nusap::Node> nilaiBilangan = buatNodeAturan(TipeNode::nilai_bilangan);
  this->mengharapkanToken(nilaiBilangan, Lexer::TipeToken::tanda_hubung, [&]() {
    return this->buatNodeToken();
  }, false);
  while(mengharapkanToken(
      nilaiBilangan, Lexer::TipeToken::angka,
      [&]() { return this->buatNodeToken(); }, false
  )) {}
  if(this->tokenSaatIniAdalah(Lexer::TipeToken::titik)) {
    throw KesalahanParse(
        this->tokenSaatIni,
        "Di indonesia biasa nya bilangan desimal menggunakan koma."
    );
  }
  if(this->mengharapkanToken(nilaiBilangan, Lexer::TipeToken::koma, [&]() {
       return this->buatNodeToken();
     }, false)) {
    size_t index = 0;
    while(mengharapkanToken(
        nilaiBilangan, Lexer::TipeToken::angka,
        [&]() { return this->buatNodeToken(); }, false
    )) {
      ++index;
    }
    if(index <= 0) {
      throw KesalahanParse(
          this->tokenSaatIni, "Setelah koma seharus nya ada angka lagi agar "
                              "menjadi bilangan desimal."
      );
    }
  }
  return nilaiBilangan;
}

std::unique_ptr<Nusap::Node> Nusap::Parser::parseNilai() {
  std::unique_ptr<Nusap::Node> nilai = buatNodeAturan(TipeNode::nilai);
  if(this->mengharapkanToken(
         nilai, {Lexer::TipeToken::tanda_hubung, Lexer::TipeToken::angka},
         [&]() { return this->parseNilaiBilangan(); }
     )) {
    return nilai;
  } else if(this->mengharapkanToken(nilai, Lexer::TipeToken::kutip_satu, [&]() {
              return this->parseNilaiTeks();
            })) {
    return nilai;
  }
  throw KesalahanParse(this->tokenSaatIni, "Nilai tidak valid.");
}

std::unique_ptr<Nusap::Node> Nusap::Parser::parseEkspresi() {
  std::unique_ptr<Nusap::Node> ekspresi = buatNodeAturan(TipeNode::ekspresi);
  if(this->mengharapkanToken(
         ekspresi,
         {Lexer::TipeToken::tanda_hubung, Lexer::TipeToken::angka,
          Lexer::TipeToken::kutip_satu},
         [&]() { return this->parseNilai(); }
     )) {
    return ekspresi;
  }
  throw KesalahanParse(this->tokenSaatIni, "Ekspresi tidak valid.");
}
