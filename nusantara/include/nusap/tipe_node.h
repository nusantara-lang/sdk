#pragma once

#include <string>

namespace Nusap {

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

} // namespace nusap
