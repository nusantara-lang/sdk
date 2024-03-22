#include "nusap/visitor.h"

#include "nusad/nusad.h"
#include "nusal/tipe_token.h"
#include "nusal/token.h"
#include "nusap/tipe_node.h"
#include <stdexcept>

Nusap::NusantaraCtx::NusantaraCtx(const Node& node) {
  for(const auto& child : node.children) {
    this->kPernyataanCtx.emplace_back(*child);
  }
}

Nusap::TokenCtx::TokenCtx(const Node& node): token(*node.token) {}

Nusap::NilaiTeksCtx::NilaiTeksCtx(const Node& node) {
  for(size_t index = 0; index < node.children.size(); ++index) {
    if(node.children[index] == nullptr) {
      continue;
    }
    if(node.children[index]->tipe == TipeNode::token) {
      // const auto& token = node.children[index]->token;
      // if(token->tipe == Nusal::TipeToken::garis_miring_terbalik) {
      //   this->kTokenCtx.emplace_back(*node.children[index]);
      //   ++index;
      //   if(token->tipe == Nusal::TipeToken::dolar) {
      //     this->kTokenCtx.emplace_back(*node.children[index]);
      //     continue;
      //   }
      // }
      // if(token->tipe == Nusal::TipeToken::dolar) {
      //   this->kTokenCtx.emplace_back(*node.children[index]);
      //   ++index;
      //   if(token->tipe == Nusal::TipeToken::kurung_kurawal_buka) {
      //     this->kTokenCtx.emplace_back(*node.children[index]);
      //     ++index;
      //     this->kEkspresiCtx.emplace_back(*node.children[index]);
      //     continue;
      //   }
      // }
      this->kTokenCtx.emplace_back(*node.children[index]); 
    }
  }
}

Nusap::MuatFileCtx::MuatFileCtx(const Node& node):
    tokenMuatCtx(Nusap::TokenCtx(*node.children[0])),
    nilaiTeksCtx(Nusap::NilaiTeksCtx(*node.children[1])) {}

Nusap::PernyataanCtx::PernyataanCtx(const Node& node) {
  const auto& child0 = node.children[0];
  if(child0->tipe == TipeNode::muat_file) {
    this->muatFileCtx = Nusap::MuatFileCtx(*child0);
    this->tokenTitikKomaCtx = Nusap::TokenCtx(*node.children[1]);
  } else if(child0->tipe == TipeNode::ekspresi) {
    this->ekspresiCtx = Nusap::EkspresiCtx(*child0);
    this->tokenTitikKomaCtx = Nusap::TokenCtx(*node.children[1]);
  }
}

Nusap::NilaiBilanganCtx::NilaiBilanganCtx(const Node& node) {
  for(const auto& node : node.children) { this->kTokenCtx.emplace_back(*node); }
}

Nusap::EkspresiCtx::EkspresiCtx(const Node& node):
    nilaiCtx(NilaiCtx(*node.children[0])) {}

Nusap::NilaiCtx::NilaiCtx(const Node& node) {
  const auto& child0 = *node.children[0];
  if(child0.tipe == TipeNode::nilai_bilangan) {
    this->nilaiBilanganCtx = NilaiBilanganCtx(child0);
  } else if(child0.tipe == TipeNode::nilai_teks) {
    this->nilaiTeksCtx = NilaiTeksCtx(child0);
  }
}

std::any Nusap::Visitor::visit(const Node& node) {
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
