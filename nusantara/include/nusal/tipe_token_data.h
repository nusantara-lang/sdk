#pragma once

#include "nusal/tipe_token.h"

#include <string>

namespace Nusal {

  struct TipeTokenData {
      TipeTokenData();
      TipeTokenData(const TipeToken& tipe, std::string pola);
      TipeToken tipe;
      std::string pola;
  };

} // namespace Nusal
