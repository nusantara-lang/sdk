#include "nusap/node.h"

#include "nusal/tipe_token.h"
#include "nusap/tipe_node.h"

#include <iostream>

nusap::node::node(const tipe_node& tipe): tipe(tipe), token(nullptr) {}

nusap::node::node(const tipe_node& tipe, std::unique_ptr<nusal::token> token):
    tipe(tipe), token(std::move(token)) {}

void nusap::cetak_node(const std::unique_ptr<node>& node, const int& level) {
  if(!node) { return; }
  for(int i = 0; i < level; ++i) { std::cout << "  "; }
  if(node->token != nullptr) {
    std::cout << nusal::ubah_ke_string(node->token->tipe) << ": "
              << node->token->nilai << "\n";
  } else {
    std::cout << nusap::ubah_ke_string(node->tipe) << "\n";
  }
  for(const auto& child : node->children) { cetak_node(child, level + 1); }
}
