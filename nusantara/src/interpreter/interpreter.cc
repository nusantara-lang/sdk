#include "interpreter/interpreter.h"

#include "interpreter/kesalahan_interpret.h"
#include "lexer/tipe_token.h"
#include "lexer/token.h"
#include "ncpp/tipe_data/bilangan.h"
#include "parser/parser.h"

#include <any>
#include <format>
#include <iostream>
#include <string>

Interpreter::Interpreter::Interpreter() { this->awal(); };

void Interpreter::Interpreter::awal() {
  if(kKawasan.empty()) { this->kKawasan.emplace_back(); }
}

void Interpreter::Interpreter::input(const std::string& input) {
  std::string sumber("tidak diketahui");
  if(this->kParser.find(sumber) == this->kParser.end()) {
    auto& parser = this->kParser[sumber];
    parser = Parser::Parser();
    parser.input(input);
    if(const auto node = parser.parse()) { this->visit(*node); }
  }
}

void Interpreter::Interpreter::input(
    const std::string& sumber, const std::string& input
) {
  if(this->kParser.find(sumber) == this->kParser.end()) {
    auto& parser = this->kParser[sumber];
    parser = Parser::Parser();
    parser.input(sumber, input);
    if(const auto node = parser.parse()) { this->visit(*node); }
  }
}

void Interpreter::Interpreter::inputFilePath(const std::string& filePath) {
  if(this->kParser.find(filePath) == this->kParser.end()) {
    auto& parser = this->kParser[filePath];
    parser = Parser::Parser();
    parser.inputFilePath(filePath);
    if(const auto node = parser.parse()) { this->visit(*node); }
  }
}

Interpreter::Interpreter::Kawasan&
Interpreter::Interpreter::ambilKawasanTerakhir() {
  return this->kKawasan[this->kKawasan.size() - 1];
}

Interpreter::Interpreter::Variabel& Interpreter::Interpreter::buatVariabel(
    const Lexer::TipeToken& tipe, const std::string& nama, const std::any& nilai
) {
  Variabel var;
  var.tipe = tipe;
  var.nilai = nilai;
  Variabel& variabel = this->ambilKawasanTerakhir().kVariabel[nama];
  variabel = std::move(var);
  return variabel;
}

Interpreter::Interpreter::Variabel&
Interpreter::Interpreter::ambilVariabel(const std::string& nama) {
  return this->ambilKawasanTerakhir().kVariabel[nama];
}

Interpreter::Interpreter::Fungsi& Interpreter::Interpreter::buatFungsi(
    const Lexer::TipeToken& tipe, const std::string& nama,
    const std::function<std::any(std::map<std::string, Variabel>&)>& definisi
) {
  Fungsi fun;
  fun.tipe = tipe;
  fun.definisi = definisi;
  Fungsi& fungsi = this->ambilKawasanTerakhir().kFungsi[nama];
  fungsi = std::move(fun);
  return fungsi;
}

Interpreter::Interpreter::Fungsi&
Interpreter::Interpreter::ambilFungsi(const std::string& nama) {
  return this->ambilKawasanTerakhir().kFungsi[nama];
}

// VISIT AREA

std::any Interpreter::Interpreter::visitToken(const Parser::TokenCtx& ctx) {
  this->kToken.push_back(ctx.token);
  return ctx.token;
}

std::any
Interpreter::Interpreter::visitNilaiTeks(const Parser::NilaiTeksCtx& ctx) {
  std::string teks;
  size_t indexEkspresi = 0;
  for(size_t index = 0; index < ctx.kTokenCtx.size(); ++index) {
    if(index <= 0 || index >= (ctx.kTokenCtx.size() - 1)) { continue; }
    std::any tokenAny = this->visitToken(ctx.kTokenCtx[index]);
    if(const auto* token = std::any_cast<Lexer::Token>(&tokenAny)) {
      if(token->tipe == Lexer::TipeToken::garis_miring_terbalik) {
        ++index;
        std::any tokenAny2 = this->visitToken(ctx.kTokenCtx[index]);
        if(auto* token2 = std::any_cast<Lexer::Token>(&tokenAny2)) {
          std::string& nilai = token2->nilai;
          if(nilai.starts_with('n')) {
            nilai.replace(nilai.find('n'), 1, "\n");
          } else if(nilai.starts_with('t')) {
            nilai.replace(nilai.find('t'), 1, "\t");
          }
          teks += nilai;
          continue;
        }
      } else if(token->tipe == Lexer::TipeToken::dolar) {
        ++index;
        std::any tokenAny2 = this->visitToken(ctx.kTokenCtx[index]);
        if(auto* token2 = std::any_cast<Lexer::Token>(&tokenAny2)) {
          if(token2->tipe == Lexer::TipeToken::identifikasi) {
            throw KesalahanInterpret(
                this->kToken, std::format("Nusantara belum mendukung nama "
                                          "variabel sebagai teks interpolasi.")
            );
          } else if(token2->tipe == Lexer::TipeToken::kurung_kurawal_buka) {
            if(ctx.kEkspresiCtx.empty()) {
              throw KesalahanInterpret(
                  this->kToken, "Tidak ada ekspresi pada teks interpolasi."
              );
            }
            std::any ekspresiAny =
                this->visitEkspresi(ctx.kEkspresiCtx[indexEkspresi]);
            if(const auto* ekspresi =
                   std::any_cast<std::string>(&ekspresiAny)) {
              teks += *ekspresi;
            } else if(const auto* ekspresi = std::any_cast<Ncpp::Bilangan>(&ekspresiAny)) {
              teks += ekspresi->ubahKeString();
            } else {
              throw KesalahanInterpret(
                  this->kToken, std::format(
                                    "Nusantara belum mendukung tipe '{}' "
                                    "sebagai ekspresi dari teks interpolasi.",
                                    ekspresiAny.type().name()
                                )
              );
            }
            ++indexEkspresi;
            ++index;
            continue;
          } else {
            throw KesalahanInterpret(
                this->kToken, "Teks interpolasi harus berisi nama variabel "
                              "atau sebuah ekspresi di dalam kurung kurawal."
            );
          }
        }
      }
      teks += token->nilai;
    }
  }
  return teks;
}

std::any Interpreter::Interpreter::visitMuatFile(const Parser::MuatFileCtx& ctx
) {
  this->visitToken(ctx.tokenMuatCtx);
  std::any nilaiTeksAny = this->visitNilaiTeks(ctx.nilaiTeksCtx);
  if(const auto* nilaiTeks = std::any_cast<std::string>(&nilaiTeksAny)) {
    this->inputFilePath(*nilaiTeks);
  }
  return {};
}

std::any
Interpreter::Interpreter::visitPernyataan(const Parser::PernyataanCtx& ctx) {
  if(ctx.muatFileCtx.has_value()) {
    std::any hasil = this->visitMuatFile(ctx.muatFileCtx.value());
    this->visitToken(ctx.tokenTitikKomaCtx.value());
    return hasil;
  }
  if(ctx.ekspresiCtx.has_value()) {
    std::any hasil = this->visitEkspresi(ctx.ekspresiCtx.value());
    this->visitToken(ctx.tokenTitikKomaCtx.value());
    if(const auto* hasilPtr = std::any_cast<std::string>(&hasil)) {
      std::cout << *hasilPtr << "\n";
    } else if(const auto* hasilPtr = std::any_cast<Ncpp::Bilangan>(&hasil)) {
      std::cout << *hasilPtr << "\n";
    }
    return hasil;
  }
  throw KesalahanInterpret(this->kToken, "Pernyataan tidak valid.");
}

std::any
Interpreter::Interpreter::visitNusantara(const Parser::NusantaraCtx& ctx) {
  for(const auto& pernyataanCtx : ctx.kPernyataanCtx) {
    this->visitPernyataan(pernyataanCtx);
    this->kToken.clear();
  }
  return 0;
}

std::any Interpreter::Interpreter::visitNilaiBilangan(
    [[maybe_unused]] const Parser::NilaiBilanganCtx& ctx
) {
  std::string bilangan;
  for(const auto& tokenCtx : ctx.kTokenCtx) {
    std::any tokenAny = this->visitToken(tokenCtx);
    if(const auto* token = std::any_cast<Lexer::Token>(&tokenAny)) {
      bilangan += token->nilai;
    }
  }
  return Ncpp::Bilangan(bilangan);
}

std::any Interpreter::Interpreter::visitEkspresi(const Parser::EkspresiCtx& ctx
) {
  if(ctx.nilaiCtx.has_value()) {
    return this->visitNilai(ctx.nilaiCtx.value());
  }
  throw KesalahanInterpret(this->kToken, "Ekspresi tidak valid.");
}

std::any Interpreter::Interpreter::visitNilai(const Parser::NilaiCtx& ctx) {
  if(ctx.nilaiBilanganCtx.has_value()) {
    return this->visitNilaiBilangan(ctx.nilaiBilanganCtx.value());
  } else if(ctx.nilaiTeksCtx.has_value()) {
    return this->visitNilaiTeks(ctx.nilaiTeksCtx.value());
  }
  throw KesalahanInterpret(this->kToken, "Nilai tidak valid.");
}
