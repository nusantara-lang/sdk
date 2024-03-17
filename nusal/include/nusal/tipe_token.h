#pragma once

#include <string>

namespace nusal {

  enum class tipe_token {
    spasi,
    baris_baru,
    tab,
    angka,
    simbol,
    huruf,
    tidak_diketahui
  };

  std::string ubah_ke_string(const tipe_token& tipe_token);

} // namespace nusal
