#include "nusap/node.h"
#include "nusap/tipe_node.h"
#include <iostream>

nusap::node::node(const tipe_node& tipe): tipe(tipe), token(nullptr) {}

nusap::node::node(const tipe_node& tipe, std::unique_ptr<nusal::token> token):
    tipe(tipe), token(std::move(token)) {}

void nusap::cetak_node(const std::unique_ptr<node>& node, const int& level) {
    if(!node) {return;}
    for (int i = 0; i < level; ++i) {
        std::cout << "  ";
    }
    std::cout << nusap::ubah_ke_string(node->tipe);
    if(node->token != nullptr) {
        std::cout << ": " << node->token->nilai << "\n";
    }else{
        std::cout << "\n";
    }
    for (const auto& child : node->children) {
        cetak_node(child, level + 1);
    }
}
