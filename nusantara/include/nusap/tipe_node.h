#pragma once

#include <string>

namespace nusap {

  enum class tipe_node {
    nusantara,
    token,
    pernyataan,
    pernyataan_blok_kode,
    ekspresi,
    teks,
    bilangan,
    buat_variable,
    buat_fungsi,
    manggil_fungsi,
    blok_kode
  };

  std::string ubah_ke_string(const tipe_node& node);

} // namespace nusap
