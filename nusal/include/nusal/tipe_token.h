#pragma once

#include <string>

namespace nusal {

  enum class tipe_token {
    TIDAK_DIKETAHUI,
    KEMBALI_KE_AWAL_KARAKTER,
    BARIS_BARU,
    TAB,
    SPASI,
    KATA_KUNCI,
    ALIAS,
    BILANGAN,
    TEKS,
    HURUF,
    ANGKA,
    TAMBAH,
    TANDA_HUBUNG,
    ASTERIS,
    GARIS_MIRING,
    PERSEN,
    SAMA_DENGAN,
    SERU,
    DOLAR,
    GARIS_BAWAH,
    KOMA,
    TITIK,
    TITIK_DUA,
    TITIK_KOMA,
    KUTIP_SATU,
    GARIS_VERTIKAL,
    KURUNG_BUKA,
    KURUNG_TUTUP,
    KURUNG_SIKU_BUKA,
    KURUNG_SIKU_TUTUP,
    KURUNG_KURAWAL_BUKA,
    KURUNG_KURAWAL_TUTUP
  };

  std::string ubah_ke_string(const tipe_token& tipe_token);

} // namespace nusal
