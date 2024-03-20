#include "nusap/visitor.h"
#include "nusap/tipe_node.h"
#include <string>

nusap::nusantara_ctx::nusantara_ctx(const node& node) {
    for(const auto& child : node.children) {
        this->k_pernyataan_ctx.emplace_back(*child);
    }
}

nusap::token_ctx::token_ctx(const node& node) : token(*node.token) {}

nusap::nilai_teks_ctx::nilai_teks_ctx(const node& node) {
    size_t childrenSize = node.children.size();
    for(size_t index = 0; index < childrenSize; ++index) {
        if(index > 0 && index < (childrenSize - 1)) {
            this->k_token_ctx.emplace_back(*node.children[index]);
        }
    }
}

nusap::muat_file_ctx::muat_file_ctx(const node& node) {
    size_t childrenSize = node.children.size();
    std::string lokasiFile;
    for(size_t index = 1; index < childrenSize; ++index) {
        lokasiFile += node.children[index]->token->nilai;
    }
    this->lokasiFile = lokasiFile;
}

nusap::pernyataan_ctx::pernyataan_ctx(const node& node): muat_file_ctx(*node.children[0]) {}

std::any nusap::visitor::visit(const node& node) {
    if(node.tipe == tipe_node::nusantara) {
        return this->visit_nusantara(nusantara_ctx(node));
    }
    if(node.tipe == tipe_node::token) {
        return this->visit_token(token_ctx(node));
    }
    if(node.tipe == tipe_node::nilai_teks) {
        return this->visit_nilai_teks(nilai_teks_ctx(node));
    }
    if(node.tipe == tipe_node::muat_file) {
        return this->visit_muat_file(muat_file_ctx(node));
    }
    if(node.tipe == tipe_node::pernyataan) {
        return this->visit_pernyataan(pernyataan_ctx(node));
    }
    return {};
}