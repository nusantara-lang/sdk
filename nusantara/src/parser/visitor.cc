#include "parser/visitor.h"

#include "lexer/token.h"
#include "parser/tipe_node.h"

Parser::NusantaraCtx::NusantaraCtx(const Node& node) {
  for(const auto& child : node.children) {
    this->kPernyataanCtx.emplace_back(*child);
  }
}

Parser::TokenCtx::TokenCtx(const Node& node): token(*node.token) {}

Parser::NilaiTeksCtx::NilaiTeksCtx(const Node& node) {
  for(const auto& childNode : node.children) {
    if(childNode->tipe == TipeNode::token) {
      this->kTokenCtx.emplace_back(*childNode);
    }
    if(childNode->tipe == TipeNode::ekspresi) {
      this->kEkspresiCtx.emplace_back(*childNode);
    }
  }
}

Parser::MuatFileCtx::MuatFileCtx(const Node& node):
    tokenMuatCtx(Parser::TokenCtx(*node.children[0])),
    nilaiTeksCtx(Parser::NilaiTeksCtx(*node.children[1])) {}

Parser::PernyataanCtx::PernyataanCtx(const Node& node) {
  const auto& child0 = node.children[0];
  if(child0->tipe == TipeNode::muat_file) {
    this->muatFileCtx = Parser::MuatFileCtx(*child0);
    this->tokenTitikKomaCtx = Parser::TokenCtx(*node.children[1]);
  } else if(child0->tipe == TipeNode::ekspresi) {
    this->ekspresiCtx = Parser::EkspresiCtx(*child0);
    this->tokenTitikKomaCtx = Parser::TokenCtx(*node.children[1]);
  }
}

Parser::NilaiBilanganCtx::NilaiBilanganCtx(const Node& node) {
  for(const auto& node : node.children) { this->kTokenCtx.emplace_back(*node); }
}

Parser::EkspresiCtx::EkspresiCtx(const Node& node):
    nilaiCtx(NilaiCtx(*node.children[0])) {}

Parser::NilaiCtx::NilaiCtx(const Node& node) {
  const auto& child0 = *node.children[0];
  if(child0.tipe == TipeNode::nilai_bilangan) {
    this->nilaiBilanganCtx = NilaiBilanganCtx(child0);
  } else if(child0.tipe == TipeNode::nilai_teks) {
    this->nilaiTeksCtx = NilaiTeksCtx(child0);
  }
}

std::any Parser::Visitor::visit(const Node& node) {
  if(node.tipe == TipeNode::nusantara) {
    return this->visitNusantara(NusantaraCtx(node));
  }
  if(node.tipe == TipeNode::token) { return this->visitToken(TokenCtx(node)); }
  if(node.tipe == TipeNode::nilai_teks) {
    return this->visitNilaiTeks(NilaiTeksCtx(node));
  }
  if(node.tipe == TipeNode::muat_file) {
    return this->visitMuatFile(MuatFileCtx(node));
  }
  if(node.tipe == TipeNode::pernyataan) {
    return this->visitPernyataan(PernyataanCtx(node));
  }
  if(node.tipe == TipeNode::nilai_bilangan) {
    return this->visitNilaiBilangan(NilaiBilanganCtx(node));
  }
  if(node.tipe == TipeNode::ekspresi) {
    return this->visitEkspresi(EkspresiCtx(node));
  }
  if(node.tipe == TipeNode::nilai) { return this->visitNilai(NilaiCtx(node)); }
  return {};
}