#pragma once

#include <vector>

namespace Lexer {

  std::string bacaFile(const std::string& filePath);

  std::vector<std::string> bacaFilePerLine(const std::string& filePath);

} // namespace Lexer
