#pragma once

#include "nusal/tipe_token.h"

#include <string>

namespace Nusal {

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

  struct Token {
      Token() = default;

      Token(
          const TipeToken& tipe, std::string sumber, const baris& baris,
          const karakter& karakter, std::string nilai
      );

      TipeToken tipe = TipeToken::tidak_diketahui;
      std::string sumber = "tidak diketahui";
      baris baris;
      karakter karakter;
      std::string nilai;
  };

  std::string ubahKeString(const Token& token);

} // namespace nusal
