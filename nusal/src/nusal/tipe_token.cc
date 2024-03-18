#include "nusal/tipe_token.h"

std::string nusal::ubah_ke_string(const tipe_token& tipe_token) {
  switch(tipe_token) {
    case tipe_token::TIDAK_DIKETAHUI:
      return "tidak diketahui";
    case tipe_token::KEMBALI_KE_AWAL_KARAKTER:
      return "kembali ke awal karakter";
    case tipe_token::BARIS_BARU:
      return "baris baru";
    case tipe_token::TAB:
      return "tab";
    case tipe_token::SPASI:
      return "spasi";
    case tipe_token::KATA_KUNCI:
      return "kata kunci";
    case tipe_token::ALIAS:
      return "alias";
    case tipe_token::BILANGAN:
      return "bilangan";
    case tipe_token::TEKS:
      return "teks";
    case tipe_token::IDENTIFIKASI:
      return "identifikasi";
    case tipe_token::ANGKA:
      return "angka";
    case tipe_token::TAMBAH:
      return "tambah";
    case tipe_token::TANDA_HUBUNG:
      return "tanda hubung";
    case tipe_token::ASTERIS:
      return "asteris";
    case tipe_token::GARIS_MIRING:
      return "garis miring";
    case tipe_token::PERSEN:
      return "persen";
    case tipe_token::SAMA_DENGAN:
      return "sama dengan";
    case tipe_token::SERU:
      return "seru";
    case tipe_token::DOLAR:
      return "dolar";
    case tipe_token::GARIS_BAWAH:
      return "garis bawah";
    case tipe_token::KOMA:
      return "koma";
    case tipe_token::TITIK:
      return "titik";
    case tipe_token::TITIK_DUA:
      return "titik dua";
    case tipe_token::TITIK_KOMA:
      return "titik koma";
    case tipe_token::KUTIP_SATU:
      return "kutip satu";
    case tipe_token::GARIS_VERTIKAL:
      return "garis vertikal";
    case tipe_token::KURUNG_BUKA:
      return "kurung buka";
    case tipe_token::KURUNG_TUTUP:
      return "kurung tutup";
    case tipe_token::KURUNG_SIKU_BUKA:
      return "kurung siku buka";
    case tipe_token::KURUNG_SIKU_TUTUP:
      return "kurung siku tutup";
    case tipe_token::KURUNG_KURAWAL_BUKA:
      return "kurung kurawal buka";
    case tipe_token::KURUNG_KURAWAL_TUTUP:
      return "kurung kurawal tutup";
    case tipe_token::KARAKTER:
      return "karakter";
  }
}
