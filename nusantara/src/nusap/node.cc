#include "nusap/node.h"

#include "lexer/tipe_token.h"
#include "nusap/tipe_node.h"

#include <iostream>

Nusap::Node::Node(const TipeNode& tipe): tipe(tipe), token(nullptr) {}

Nusap::Node::Node(const TipeNode& tipe, std::unique_ptr<Lexer::Token> token):
    tipe(tipe), token(std::move(token)) {}

void Nusap::cetakNode(const std::unique_ptr<Node>& node, const int& level) {
  if(!node) { return; }
  for(int i = 0; i < level; ++i) { std::cout << "  "; }
  if(node->token != nullptr) {
    std::cout << Lexer::ubahKeString(node->token->tipe) << ": "
              << node->token->nilai << "\n";
  } else {
    std::cout << Nusap::ubahKeString(node->tipe) << "\n";
  }
  for(const auto& child : node->children) { cetakNode(child, level + 1); }
}
