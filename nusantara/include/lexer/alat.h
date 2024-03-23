#pragma once

#include "lexer/tipe_token_data.h"
#include "lexer/token.h"

#include <memory>
#include <vector>

namespace Lexer {

  std::unique_ptr<Token> buatToken(
      std::string& input, baris& baris, karakter& karakter,
      const std::string& sumber, const std::vector<TipeTokenData>& data
  );

  std::string bacaFile(const std::string& filePath);

  std::vector<std::string> bacaFilePerLine(const std::string& filePath);

} // namespace Lexer
