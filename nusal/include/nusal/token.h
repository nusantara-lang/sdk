#pragma once

#include "nusal/tipe_token.h"

#include <string>

namespace nusal {

  struct baris {
      baris() = default;

      explicit baris(const size_t& nilai);

      size_t nilai = 0;
  };

  struct karakter {
      karakter() = default;

      explicit karakter(const size_t& nilai);

      size_t nilai = 0;
  };

  struct token {
      token() = default;

      token(
          const tipe_token& tipe, std::string nama, std::string sumber,
          const baris& baris, const karakter& karakter, std::string nilai
      );

      tipe_token tipe = tipe_token::TIDAK_DIKETAHUI;
      std::string nama = "tidak diketahui";
      std::string sumber = "tidak diketahui";
      baris baris;
      karakter karakter;
      std::string nilai;
  };

  std::string ubah_ke_string(const token& token);

} // namespace nusal
