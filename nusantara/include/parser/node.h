#pragma once

#include "lexer/token.h"
#include "parser/tipe_node.h"

#include <memory>
#include <vector>

namespace Parser {

  struct Node {
      explicit Node(const TipeNode& tipe);
      explicit Node(const TipeNode& tipe, std::unique_ptr<Lexer::Token> token);
      TipeNode tipe;
      std::unique_ptr<Lexer::Token> token;
      std::vector<std::unique_ptr<Node>> children;
  };

  void cetakNode(const std::unique_ptr<Node>& node, const int& level = 0);

} // namespace Parser
