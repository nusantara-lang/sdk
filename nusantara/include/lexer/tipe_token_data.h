#pragma once

#include "lexer/tipe_token.h"

#include <string>

namespace Lexer {

  struct TipeTokenData {
      TipeTokenData();
      TipeTokenData(const TipeToken& tipe, std::string pola);
      TipeToken tipe;
      std::string pola;
  };

} // namespace Lexer
