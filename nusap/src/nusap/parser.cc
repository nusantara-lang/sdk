#include "nusap/parser.h"

#include "nusal/lexer.h"
#include "nusal/nusal.h"
#include "nusal/tipe_token.h"
#include "nusal/token.h"
#include "nusap/kesalahan_parse.h"
#include "nusap/node.h"
#include "nusap/tipe_node.h"

#include <format>
#include <iostream>
#include <memory>

nusap::parser::parser():
    lexer(nusal::nusal_data_tipe_token()), token_saat_ini(nullptr) {}

void nusap::parser::input(const std::string& input) {
  this->lexer.input(input);
}

void nusap::parser::input(const std::string& sumber, const std::string& input) {
  this->lexer.input(sumber, input);
}

void nusap::parser::input_filepath(const std::string& file_path) {
  this->lexer.input_filepath(file_path);
}

void nusap::parser::token_selanjut_nya() {
  this->token_saat_ini = this->lexer.ambil_token();
}

bool nusap::parser::token_saat_ini_adalah(const nusal::tipe_token& tipe) {
  return (this->token_saat_ini != nullptr) &&
         (this->token_saat_ini->tipe == tipe);
}

bool nusap::parser::token_saat_ini_atau_adalah(
    const std::vector<nusal::tipe_token>& tipe
) {
  if(this->token_saat_ini != nullptr) {
    for(const auto& element : tipe) {
      if(this->token_saat_ini->tipe == element) { return true; }
    }
  }
  return false;
}

void nusap::parser::lewati_spasi_putih_dan_komentar() {
  while(token_saat_ini_atau_adalah({
      nusal::tipe_token::KEMBALI_KE_AWAL_KARAKTER,
      nusal::tipe_token::BARIS_BARU,
      nusal::tipe_token::TAB,
      nusal::tipe_token::SPASI,
      nusal::tipe_token::KOMENTAR_SATU_BARIS,
      nusal::tipe_token::KOMENTAR_BANYAK_BARIS
  })) {
    this->token_selanjut_nya();
  }
}

std::unique_ptr<nusap::node>
nusap::parser::buat_node_aturan(const nusap::tipe_node& tipe) {
  return std::make_unique<node>(tipe);
}

std::unique_ptr<nusap::node> nusap::parser::buat_node_token() {
  return std::make_unique<node>(
      tipe_node::token, std::make_unique<nusal::token>(*this->token_saat_ini)
  );
}

std::unique_ptr<nusap::node> nusap::parser::parse() {
  std::unique_ptr<node> nusantara =
      this->buat_node_aturan(tipe_node::nusantara);
  this->token_selanjut_nya();
  while(this->token_saat_ini != nullptr) {
    this->lewati_spasi_putih_dan_komentar();
    if(this->token_saat_ini->tipe == nusal::tipe_token::TIDAK_DIKETAHUI) {
      throw kesalahan_parser(
          *this->token_saat_ini,
          std::format(
              "Nusantara tidak dapat mengenali karakter '{}'.",
              this->token_saat_ini->nilai
          )
      );
    }
    nusantara->children.push_back(this->parse_pernyataan());
  }
  return nusantara;
}

std::unique_ptr<nusap::node> nusap::parser::parse_pernyataan() {
  std::unique_ptr<node> pernyataan =
      this->buat_node_aturan(tipe_node::pernyataan);
  if(this->token_saat_ini_adalah(nusal::tipe_token::IDENTIFIKASI)) {
    pernyataan->children.push_back(this->parse_buat_fungsi());
    return pernyataan;
  }
  if(this->token_saat_ini_atau_adalah(
         {nusal::tipe_token::TANDA_HUBUNG, nusal::tipe_token::ANGKA,
          nusal::tipe_token::TEKS}
     )) {
    pernyataan->children.push_back(this->parse_buat_variable());
    if(this->token_saat_ini_adalah(nusal::tipe_token::TITIK_KOMA)) {
      pernyataan->children.push_back(this->buat_node_token());
      this->token_selanjut_nya();
      this->lewati_spasi_putih_dan_komentar();
    } else {
      throw kesalahan_parser(*this->token_saat_ini, "Jangan lupa titik koma.");
    }
    return pernyataan;
  }
  throw kesalahan_parser(*this->token_saat_ini, "Pernyataan tidak valid.");
}

std::unique_ptr<nusap::node> nusap::parser::parse_pernyataan_blok_kode() {
  std::unique_ptr<node> pernyataan_blok_kode = this->buat_node_aturan(tipe_node::pernyataan_blok_kode);
  if(this->token_saat_ini_adalah(nusal::tipe_token::IDENTIFIKASI)) {
    nusal::lexer lexer_backup = this->lexer;
    nusal::token token_saat_ini_backup = *this->token_saat_ini;
    try {
      pernyataan_blok_kode->children.push_back(this->parse_buat_fungsi());
      return pernyataan_blok_kode;
    } catch (const std::exception& error) {
      this->lexer = lexer_backup;
      *this->token_saat_ini = token_saat_ini_backup;
    }
    pernyataan_blok_kode->children.push_back(this->parse_manggil_fungsi());
    if(this->token_saat_ini_adalah(nusal::tipe_token::TITIK_KOMA)) {
      pernyataan_blok_kode->children.push_back(this->buat_node_token());
      this->token_selanjut_nya();
      this->lewati_spasi_putih_dan_komentar();
    } else {
      throw kesalahan_parser(
          *this->token_saat_ini, "Jangan lupa titik koma."
      );
    }
    return pernyataan_blok_kode;
  }
  if(this->token_saat_ini_atau_adalah(
         {nusal::tipe_token::BILANGAN, nusal::tipe_token::TEKS}
     )) {
    pernyataan_blok_kode->children.push_back(this->parse_buat_variable());
    if(this->token_saat_ini_adalah(nusal::tipe_token::TITIK_KOMA)) {
      pernyataan_blok_kode->children.push_back(this->buat_node_token());
      this->token_selanjut_nya();
      this->lewati_spasi_putih_dan_komentar();
    } else {
      throw kesalahan_parser(*this->token_saat_ini, "Jangan lupa titik koma.");
    }
    return pernyataan_blok_kode;
  }
  throw kesalahan_parser(
      *this->token_saat_ini, "Pernyataan blok kode tidak valid."
  );
}

std::unique_ptr<nusap::node> nusap::parser::parse_ekspresi() {
  std::unique_ptr<node> ekspresi = this->buat_node_aturan(tipe_node::ekspresi);
  if(token_saat_ini_adalah(nusal::tipe_token::KUTIP_SATU)) {
    ekspresi->children.push_back(this->parse_teks());
    return ekspresi;
  }
  if(token_saat_ini_atau_adalah(
         {nusal::tipe_token::TANDA_HUBUNG, nusal::tipe_token::ANGKA}
     )) {
    ekspresi->children.push_back(this->parse_bilangan());
    return ekspresi;
  }
  throw kesalahan_parser(*this->token_saat_ini, "Ekspresi tidak valid.");
}

std::unique_ptr<nusap::node> nusap::parser::parse_teks() {
  std::unique_ptr<node> teks = this->buat_node_aturan(tipe_node::teks);
  if(token_saat_ini_adalah(nusal::tipe_token::KUTIP_SATU)) {
    teks->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
  } else {
    throw kesalahan_parser(
        *this->token_saat_ini, "Teks harus di awali kutip satu '."
    );
  }
  while(!token_saat_ini_adalah(nusal::tipe_token::KUTIP_SATU)) {
    if(token_saat_ini_atau_adalah(
           {nusal::tipe_token::BARIS_BARU,
            nusal::tipe_token::KEMBALI_KE_AWAL_KARAKTER}
       )) {
      throw kesalahan_parser(
          *this->token_saat_ini,
          "Tidak boleh ada baris baru secara eksplisit pada teks"
      );
    }
    teks->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
  }
  if(token_saat_ini_adalah(nusal::tipe_token::KUTIP_SATU)) {
    teks->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
  } else {
    throw kesalahan_parser(
        *this->token_saat_ini, "Teks harus di akhiri kutip satu '."
    );
  }
  return teks;
}

std::unique_ptr<nusap::node> nusap::parser::parse_bilangan() {
  std::unique_ptr<node> bilangan = this->buat_node_aturan(tipe_node::bilangan);
  if(token_saat_ini_adalah(nusal::tipe_token::TANDA_HUBUNG)) {
    bilangan->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
  }
  while(token_saat_ini_adalah(nusal::tipe_token::ANGKA)) {
    bilangan->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
  }
  if(token_saat_ini_adalah(nusal::tipe_token::TITIK)) {
    throw kesalahan_parser(
        *this->token_saat_ini,
        "Di indonesia biasa nya bilangan desimal pake koma ',' bukan '.'"
    );
  }
  if(token_saat_ini_adalah(nusal::tipe_token::KOMA)) {
    bilangan->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
    if(!token_saat_ini_adalah(nusal::tipe_token::ANGKA)) {
      throw kesalahan_parser(
          *this->token_saat_ini, "Setelah koma ',' seharus nya ada angka lagi."
      );
    }
    while(token_saat_ini_adalah(nusal::tipe_token::ANGKA)) {
      bilangan->children.push_back(this->buat_node_token());
      this->token_selanjut_nya();
    }
  }
  return bilangan;
}

std::unique_ptr<nusap::node> nusap::parser::parse_buat_variable() {
  std::unique_ptr<node> buat_variable =
      this->buat_node_aturan(tipe_node::buat_variable);
  nusal::tipe_token tipe = nusal::tipe_token::TIDAK_DIKETAHUI;
  if(token_saat_ini_atau_adalah(
         {nusal::tipe_token::TEKS, nusal::tipe_token::BILANGAN}
     )) {
    tipe = this->token_saat_ini->tipe;
    buat_variable->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
    this->lewati_spasi_putih_dan_komentar();
  } else {
    throw kesalahan_parser(*this->token_saat_ini, "Tipe data tidak valid.");
  }
  if(token_saat_ini_adalah(nusal::tipe_token::IDENTIFIKASI)) {
    buat_variable->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
    this->lewati_spasi_putih_dan_komentar();
  } else {
    throw kesalahan_parser(
        *this->token_saat_ini, "Nama untuk variable belum ditulis."
    );
  }
  if(token_saat_ini_adalah(nusal::tipe_token::SAMA_DENGAN)) {
    buat_variable->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
    this->lewati_spasi_putih_dan_komentar();
    if(tipe == nusal::tipe_token::TEKS) {
      buat_variable->children.push_back(this->parse_teks());
    } else if(tipe == nusal::tipe_token::BILANGAN) {
      buat_variable->children.push_back(this->parse_bilangan());
    }
  }
  return buat_variable;
}

std::unique_ptr<nusap::node> nusap::parser::parse_blok_kode() {
  std::unique_ptr<node> blok_kode =
      this->buat_node_aturan(tipe_node::blok_kode);
  if(token_saat_ini_adalah(nusal::tipe_token::KURUNG_KURAWAL_BUKA)) {
    blok_kode->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
    this->lewati_spasi_putih_dan_komentar();
  } else {
    throw kesalahan_parser(
        *this->token_saat_ini,
        "Blok kode harus di awali kurung kurawal buka '{'."
    );
  }
  while(!token_saat_ini_adalah(nusal::tipe_token::KURUNG_KURAWAL_TUTUP)) {
    blok_kode->children.push_back(this->parse_pernyataan_blok_kode());
  }
  if(token_saat_ini_adalah(nusal::tipe_token::KURUNG_KURAWAL_TUTUP)) {
    blok_kode->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
    this->lewati_spasi_putih_dan_komentar();
  } else {
    throw kesalahan_parser(
        *this->token_saat_ini,
        "Blok kode harus di akhiri kurung kurawal buka '{'."
    );
  }
  return blok_kode;
}

std::unique_ptr<nusap::node> nusap::parser::parse_buat_fungsi() {
  std::unique_ptr<node> buat_fungsi =
      this->buat_node_aturan(tipe_node::buat_fungsi);
  if(this->token_saat_ini_adalah(nusal::tipe_token::IDENTIFIKASI)) {
    buat_fungsi->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
    this->lewati_spasi_putih_dan_komentar();
  } else {
    throw kesalahan_parser(*this->token_saat_ini, "Nama fungsi belum ditulis.");
  }
  if(this->token_saat_ini_adalah(nusal::tipe_token::KURUNG_BUKA)) {
    buat_fungsi->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
    this->lewati_spasi_putih_dan_komentar();
  } else {
    throw kesalahan_parser(
        *this->token_saat_ini, "Seharusnya kurung buka setelah nama fungsi."
    );
  }
  if(token_saat_ini_atau_adalah(
         {nusal::tipe_token::TEKS, nusal::tipe_token::BILANGAN}
     )) {
    buat_fungsi->children.push_back(this->parse_buat_variable());
    while(token_saat_ini_adalah(nusal::tipe_token::KOMA)) {
      buat_fungsi->children.push_back(this->buat_node_token());
      this->token_selanjut_nya();
      this->lewati_spasi_putih_dan_komentar();
      if(token_saat_ini_atau_adalah(
             {nusal::tipe_token::TEKS, nusal::tipe_token::BILANGAN}
         )) {
        buat_fungsi->children.push_back(this->parse_buat_variable());
      } else {
        throw kesalahan_parser(
            *this->token_saat_ini, "Seharusnya setelah koma ada variabel lagi."
        );
      }
    }
  }
  if(this->token_saat_ini_adalah(nusal::tipe_token::KURUNG_TUTUP)) {
    buat_fungsi->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
    this->lewati_spasi_putih_dan_komentar();
  } else {
    throw kesalahan_parser(
        *this->token_saat_ini, "Setelah kurung buka harus nya kurung tutup ')'."
    );
  }
  if(token_saat_ini_adalah(nusal::tipe_token::KURUNG_KURAWAL_BUKA)) {
    buat_fungsi->children.push_back(this->parse_blok_kode());
  }else{
    throw kesalahan_parser(
        *this->token_saat_ini, "Fungsi yang dibuat harus di definisikan."
    );
  }
  return buat_fungsi;
}

std::unique_ptr<nusap::node> nusap::parser::parse_manggil_fungsi() {
  std::unique_ptr<node> manggil_fungsi = this->buat_node_aturan(tipe_node::manggil_fungsi);
  if(this->token_saat_ini_adalah(nusal::tipe_token::IDENTIFIKASI)) {
    manggil_fungsi->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
    this->lewati_spasi_putih_dan_komentar();
  } else {
    throw kesalahan_parser(*this->token_saat_ini, "Nama fungsi harus ditulis sebelum di panggil.");
  }
  if(this->token_saat_ini_adalah(nusal::tipe_token::KURUNG_BUKA)) {
    manggil_fungsi->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
    this->lewati_spasi_putih_dan_komentar();
  } else {
    throw kesalahan_parser(
        *this->token_saat_ini, "Seharusnya kurung buka setelah nama fungsi."
    );
  }
  if(token_saat_ini_atau_adalah(
         {nusal::tipe_token::TANDA_HUBUNG, nusal::tipe_token::ANGKA,
          nusal::tipe_token::KUTIP_SATU}
     )) {
    manggil_fungsi->children.push_back(this->parse_ekspresi());
    this->lewati_spasi_putih_dan_komentar();
    while(token_saat_ini_adalah(nusal::tipe_token::KOMA)) {
      manggil_fungsi->children.push_back(this->buat_node_token());
      this->token_selanjut_nya();
      this->lewati_spasi_putih_dan_komentar();
      if(token_saat_ini_atau_adalah(
             {nusal::tipe_token::TANDA_HUBUNG, nusal::tipe_token::ANGKA,
              nusal::tipe_token::KUTIP_SATU}
         )) {
        manggil_fungsi->children.push_back(this->parse_ekspresi());
        this->lewati_spasi_putih_dan_komentar();
      } else {
        throw kesalahan_parser(
            *this->token_saat_ini, "Seharusnya setelah koma ada ekspresi lagi."
        );
      }
    }
  }
  if(this->token_saat_ini_adalah(nusal::tipe_token::KURUNG_TUTUP)) {
    manggil_fungsi->children.push_back(this->buat_node_token());
    this->token_selanjut_nya();
    this->lewati_spasi_putih_dan_komentar();
  } else {
    throw kesalahan_parser(
        *this->token_saat_ini, "Setelah kurung buka harus nya kurung tutup ')'."
    );
  }
  return manggil_fungsi;
}
