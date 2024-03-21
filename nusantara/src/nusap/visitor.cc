#include "nusap/visitor.h"
#include "nusap/tipe_node.h"

Nusap::NusantaraCtx::NusantaraCtx(const Node& node) {
    for(const auto& child : node.children) {
        this->kPernyataanCtx.emplace_back(*child);
    }
}

Nusap::TokenCtx::TokenCtx(const Node& node) : token(*node.token) {}

Nusap::NilaiTeksCtx::NilaiTeksCtx(const Node& node) {
    for(const auto& node : node.children) {
        this->kTokenCtx.emplace_back(*node);
    }
}

Nusap::MuatFileCtx::MuatFileCtx(const Node& node): tokenMuatCtx(Nusap::TokenCtx(*node.children[0])), nilaiTeksCtx(Nusap::NilaiTeksCtx(*node.children[1])) {}

Nusap::PernyataanCtx::PernyataanCtx(const Node& node) {
	const auto& child0 = node.children[0];
	if(child0->tipe == TipeNode::muat_file) {
		this->muatFileCtx = Nusap::MuatFileCtx(*child0);
        this->tokenTitikKomaCtx = Nusap::TokenCtx(*node.children[1]);
	}
}

std::any Nusap::Visitor::visit(const Node& node) {
    if(node.tipe == TipeNode::nusantara) {
        return this->visitNusantara(NusantaraCtx(node));
    }
    if(node.tipe == TipeNode::token) {
        return this->visitToken(TokenCtx(node));
    }
    if(node.tipe == TipeNode::nilai_teks) {
        return this->visitNilaiTeks(NilaiTeksCtx(node));
    }
    if(node.tipe == TipeNode::muat_file) {
        return this->visitMuatFile(MuatFileCtx(node));
    }
    if(node.tipe == TipeNode::pernyataan) {
        return this->visitPernyataan(PernyataanCtx(node));
    }
    return {};
}
