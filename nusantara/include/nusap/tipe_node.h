#pragma once

#include <string>

namespace nusap {

  enum class tipe_node {
    token,
    nusantara,
    muat_file,
    nilai_teks,
    pernyataan
  };

  std::string ubah_ke_string(const tipe_node& node);

} // namespace nusap
