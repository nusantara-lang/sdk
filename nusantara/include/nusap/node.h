#pragma once

#include "nusal/token.h"
#include "nusap/tipe_node.h"

#include <memory>
#include <vector>

namespace Nusap {

  struct Node {
      explicit Node(const TipeNode& tipe);
      explicit Node(const TipeNode& tipe, std::unique_ptr<Nusal::Token> token);
      TipeNode tipe;
      std::unique_ptr<Nusal::Token> token;
      std::vector<std::unique_ptr<Node>> children;
  };

  void cetakNode(const std::unique_ptr<Node>& node, const int& level = 0);

} // namespace nusap
