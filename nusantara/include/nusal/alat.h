#pragma once

#include "nusal/tipe_token_data.h"
#include "nusal/token.h"
#include <vector>

namespace Nusal {

  Token buatToken(
      std::string& input, baris& baris, karakter& karakter,
      const std::string& sumber, const std::vector<TipeTokenData>& data
  );

  std::string bacaFile(const std::string& filePath);

  std::vector<std::string> bacaFilePerLine(const std::string& filePath);

} // namespace Nusal
