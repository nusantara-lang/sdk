#include "nusai/interpreter.h"

#include "nusai/kesalahan_interpret.h"
#include "nusal/tipe_token.h"
#include "nusal/token.h"
#include "nusap/parser.h"

#include <any>
#include <iostream>
#include <string>

Nusai::Interpreter::Interpreter() { this->awal(); };

void Nusai::Interpreter::awal() {
  if(kKawasan.empty()) { this->kKawasan.emplace_back(); }
}

void Nusai::Interpreter::input(const std::string& input) {
  std::string sumber("tidak diketahui");
  if(this->kParser.find(sumber) == this->kParser.end()) {
    auto& parser = this->kParser[sumber];
    parser = Nusap::Parser();
    parser.input(input);
    if(const auto node = parser.parse()) { this->visit(*node); }
  }
}

void Nusai::Interpreter::input(
    const std::string& sumber, const std::string& input
) {
  if(this->kParser.find(sumber) == this->kParser.end()) {
    auto& parser = this->kParser[sumber];
    parser = Nusap::Parser();
    parser.input(sumber, input);
    if(const auto node = parser.parse()) { this->visit(*node); }
  }
}

void Nusai::Interpreter::inputFilePath(const std::string& filePath) {
  if(this->kParser.find(filePath) == this->kParser.end()) {
    auto& parser = this->kParser[filePath];
    parser = Nusap::Parser();
    parser.inputFilePath(filePath);
    if(const auto node = parser.parse()) { this->visit(*node); }
  }
}

Nusai::Interpreter::Kawasan& Nusai::Interpreter::ambilKawasanTerakhir() {
  return this->kKawasan[this->kKawasan.size() - 1];
}

Nusai::Interpreter::Variabel& Nusai::Interpreter::buatVariabel(
    const Nusal::TipeToken& tipe, const std::string& nama, const std::any& nilai
) {
  Variabel var;
  var.tipe = tipe;
  var.nilai = nilai;
  Variabel& variabel = this->ambilKawasanTerakhir().kVariabel[nama];
  variabel = std::move(var);
  return variabel;
}

Nusai::Interpreter::Variabel&
Nusai::Interpreter::ambilVariabel(const std::string& nama) {
  return this->ambilKawasanTerakhir().kVariabel[nama];
}

Nusai::Interpreter::Fungsi& Nusai::Interpreter::buatFungsi(
    const Nusal::TipeToken& tipe, const std::string& nama,
    const std::function<std::any(std::map<std::string, Variabel>&)>& definisi
) {
  Fungsi fun;
  fun.tipe = tipe;
  fun.definisi = definisi;
  Fungsi& fungsi = this->ambilKawasanTerakhir().kFungsi[nama];
  fungsi = std::move(fun);
  return fungsi;
}

Nusai::Interpreter::Fungsi&
Nusai::Interpreter::ambilFungsi(const std::string& nama) {
  return this->ambilKawasanTerakhir().kFungsi[nama];
}

// VISIT AREA

std::any Nusai::Interpreter::visitToken(const Nusap::TokenCtx& ctx) {
  this->kToken.push_back(ctx.token);
  return ctx.token;
}

std::any Nusai::Interpreter::visitNilaiTeks(const Nusap::NilaiTeksCtx& ctx) {
  std::string teks;
  for(size_t index = 0; index < ctx.kTokenCtx.size(); ++index) {
    if(index <= 0 || index >= (ctx.kTokenCtx.size() - 1)) { continue; }
    std::any tokenAny = this->visitToken(ctx.kTokenCtx[index]);
    if(const auto* token = std::any_cast<Nusal::Token>(&tokenAny)) {
      if(token->tipe == Nusal::TipeToken::garis_miring_terbalik) {
        ++index;
        std::any tokenAny2 = this->visitToken(ctx.kTokenCtx[index]);
        if(auto* token2 = std::any_cast<Nusal::Token>(&tokenAny2)) {
          if(token2->nilai.starts_with('n')) {
            token2->nilai[0] = '\n';
          } else if(token2->nilai.starts_with('t')) {
            token2->nilai[0] = '\t';
          }
          teks += token2->nilai;
        }
        continue;
      }
      teks += token->nilai;
    }
  }
  return teks;
}

std::any Nusai::Interpreter::visitMuatFile(const Nusap::MuatFileCtx& ctx) {
  this->visitToken(ctx.tokenMuatCtx);
  std::any nilaiTeksAny = this->visitNilaiTeks(ctx.nilaiTeksCtx);
  if(const auto* nilaiTeks = std::any_cast<std::string>(&nilaiTeksAny)) {
    this->inputFilePath(*nilaiTeks);
  }
  return {};
}

std::any Nusai::Interpreter::visitPernyataan(const Nusap::PernyataanCtx& ctx) {
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
    }
    return hasil;
  }
  throw Nusai::KesalahanInterpret(this->kToken, "Pernyataan tidak valid.");
}

std::any Nusai::Interpreter::visitNusantara(const Nusap::NusantaraCtx& ctx) {
  for(const auto& pernyataanCtx : ctx.kPernyataanCtx) {
    this->visitPernyataan(pernyataanCtx);
    this->kToken.clear();
  }
  return 0;
}

std::any Nusai::Interpreter::visitNilaiBilangan(
    [[maybe_unused]] const Nusap::NilaiBilanganCtx& ctx
) {
  for(const auto& tokenCtx : ctx.kTokenCtx) {
    std::any tokenAny = this->visitToken(tokenCtx);
  }
  throw KesalahanInterpret(
      this->kToken, "Nilai bilangan belum dapat di lakukan."
  );
}

std::any Nusai::Interpreter::visitEkspresi(const Nusap::EkspresiCtx& ctx) {
  if(ctx.nilaiCtx.has_value()) {
    return this->visitNilai(ctx.nilaiCtx.value());
  }
  throw KesalahanInterpret(this->kToken, "Ekspresi tidak valid.");
}

std::any Nusai::Interpreter::visitNilai(const Nusap::NilaiCtx& ctx) {
  if(ctx.nilaiBilanganCtx.has_value()) {
    return this->visitNilaiBilangan(ctx.nilaiBilanganCtx.value());
  } else if(ctx.nilaiTeksCtx.has_value()) {
    return this->visitNilaiTeks(ctx.nilaiTeksCtx.value());
  }
  throw KesalahanInterpret(this->kToken, "Nilai tidak valid.");
}
