#include "nusal/tipe_token.h"

std::string Nusal::ubahKeString(const TipeToken& tipeToken) {
  switch(tipeToken) {
    case TipeToken::tidak_diketahui:
      return "tidak diketahui";
    case TipeToken::kembali_ke_awal_karakter:
      return "kembali ke awal karakter";
    case TipeToken::baris_baru:
      return "baris baru";
    case TipeToken::tab:
      return "tab";
    case TipeToken::spasi:
      return "spasi";
    case TipeToken::muat:
      return "muat";
    case TipeToken::luar:
      return "luar";
    case TipeToken::bilangan:
      return "bilangan";
    case TipeToken::teks:
      return "teks";
    case TipeToken::dinamis:
      return "dinamis";
    case TipeToken::identifikasi:
      return "identifikasi";
    case TipeToken::angka:
      return "angka";
    case TipeToken::tambah:
      return "tambah";
    case TipeToken::tanda_hubung:
      return "tanda hubung";
    case TipeToken::asteris:
      return "asteris";
    case TipeToken::garis_miring:
      return "garis miring";
    case TipeToken::persen:
      return "persen";
    case TipeToken::sama_dengan:
      return "sama dengan";
    case TipeToken::seru:
      return "seru";
    case TipeToken::dolar:
      return "dolar";
    case TipeToken::garis_bawah:
      return "garis bawah";
    case TipeToken::koma:
      return "koma";
    case TipeToken::titik:
      return "titik";
    case TipeToken::titik_dua:
      return "titik dua";
    case TipeToken::titik_koma:
      return "titik koma";
    case TipeToken::kutip_satu:
      return "kutip satu";
    case TipeToken::garis_vertikal:
      return "garis vertikal";
    case TipeToken::kurung_buka:
      return "kurung buka";
    case TipeToken::kurung_tutup:
      return "kurung tutup";
    case TipeToken::kurung_siku_buka:
      return "kurung siku buka";
    case TipeToken::kurung_siku_tutup:
      return "kurung siku tutup";
    case TipeToken::kurung_kurawal_buka:
      return "kurung kurawal buka";
    case TipeToken::kurung_kurawal_tutup:
      return "kurung kurawal tutup";
    case TipeToken::karakter:
      return "karakter";
    case TipeToken::komentar_satu_baris:
      return "komentar satu baris";
    case TipeToken::komentar_banyak_baris:
      return "komentar banyak baris";
  }
}
