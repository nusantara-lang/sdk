#pragma once

#include <string>

namespace Parser {

  enum class TipeNode {
    token,
    nusantara,
    muat_file,
    nilai_teks,
    pernyataan,
    nilai_bilangan,
    ekspresi,
    nilai,
  };

  std::string ubahKeString(const TipeNode& node);

} // namespace Parser
