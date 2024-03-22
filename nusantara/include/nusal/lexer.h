#pragma once

#include "nusal/tipe_token_data.h"
#include "nusal/token.h"

#include <map>
#include <string>
#include <vector>

namespace Nusal {

  class Lexer {
    public:
      explicit Lexer(const std::vector<TipeTokenData>& tipeTokenData);

      void input(const std::string& input);

      void input(const std::string& sumber, const std::string& input);

      void inputFilePath(const std::string& filePath);

      Token ambilToken();

    private:
      std::vector<TipeTokenData> tipeTokenData;
      baris baris;
      karakter karakter;
      std::map<std::string, std::string> sumberBersertaInput = {};
  };

} // namespace Nusal
