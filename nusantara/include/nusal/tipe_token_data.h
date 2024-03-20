#pragma once

#include "nusal/tipe_token.h"

#include <string>

namespace nusal {

  struct tipe_token_data {
      tipe_token_data();
      tipe_token_data(const tipe_token& tipe, std::string pola);
      tipe_token tipe;
      std::string pola;
  };

} // namespace nusal
