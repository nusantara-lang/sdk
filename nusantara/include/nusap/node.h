#pragma once

#include "nusal/token.h"
#include "nusap/tipe_node.h"

#include <memory>
#include <vector>

namespace nusap {

  struct node {
      explicit node(const tipe_node& tipe);
      explicit node(const tipe_node& tipe, std::unique_ptr<nusal::token> token);
      tipe_node tipe;
      std::unique_ptr<nusal::token> token;
      std::vector<std::unique_ptr<node>> children;
  };

  void cetak_node(const std::unique_ptr<node>& node, const int& level = 0);

} // namespace nusap
