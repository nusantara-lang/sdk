#pragma once

#include <string>

namespace Nusal {

  enum class TipeToken {
    tidak_diketahui,
    kembali_ke_awal_karakter,
    baris_baru,
    tab,
    spasi,
    komentar_satu_baris,
    komentar_banyak_baris,
    muat,
    luar,
    bilangan,
    teks,
    dinamis,
    identifikasi,
    angka,
    tambah,
    tanda_hubung,
    asteris,
    garis_miring,
    persen,
    sama_dengan,
    seru,
    dolar,
    garis_bawah,
    koma,
    titik,
    titik_dua,
    titik_koma,
    kutip_satu,
    garis_vertikal,
    kurung_buka,
    kurung_tutup,
    kurung_siku_buka,
    kurung_siku_tutup,
    kurung_kurawal_buka,
    kurung_kurawal_tutup,
    garis_miring_terbalik,
    karakter
  };

  std::string ubahKeString(const TipeToken& tipeToken);

} // namespace Nusal
