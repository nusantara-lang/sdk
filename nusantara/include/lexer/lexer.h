#pragma once

#include "lexer/tipe_token_data.h"
#include "lexer/token.h"

#include <map>
#include <string>
#include <vector>

namespace Lexer {

  const std::vector<TipeTokenData>& nusantaraDataTipeToken();

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

} // namespace Lexer
