#include "nusap/visitor.h"
#include "nusal/tipe_token.h"
#include "nusap/tipe_node.h"

nusap::nusantara_ctx::nusantara_ctx(const node& node) {
    /* 0. rule : pernyataan */
    for(const auto& child : node.children) {
        this->k_pernyataan_ctx.emplace_back(*child);
    }
}

nusap::teks_ctx::teks_ctx(const node& node) {
    /* 
    0. token : kutip_satu 
    1*?. token
    end. token : kutip_satu
    */
    size_t index = 0;
    for(const auto& child : node.children) {
        if(index > 0 && index < (node.children.size() - 1)) {
            this->k_token.emplace_back(*child->token);
        }
        ++index;
    }
}

nusap::bilangan_ctx::bilangan_ctx(const node& node) {
    /* semua. token */
    for(const auto& child : node.children) {
        this->k_token.emplace_back(*child->token);
    }
}

nusap::buat_variable_ctx::buat_variable_ctx(const node& node) 
: 
tipe(node.children[0]->token->tipe), 
id(node.children[1]->token->nilai) 
{
    /*
    0. token : tipe
    1. token : identifikasi
    2. token : sama dengan
    3. rule : teks | bilangan
    */
    if(node.children[2]->token->tipe == nusal::tipe_token::SAMA_DENGAN) {
        if(this->tipe == nusal::tipe_token::TEKS) {
            this->teks_ctx = nusap::teks_ctx(*node.children[3]);
        }else if(this->tipe == nusal::tipe_token::BILANGAN) {
            this->bilangan_ctx = nusap::bilangan_ctx(*node.children[3]);
        }
    }
}

nusap::blok_kode_ctx::blok_kode_ctx(const node& node) {
    /* 
    0. token : kurung kurawal buka 
    1*?. rule : pernyataan_blok_kode
    end. token : kurung kurawal tutup 
    */
    size_t index = 0;
    for(const auto& child : node.children) {
        if(index > 0 && index < (node.children.size() - 1)) {
            this->k_pernyataan_blok_kode_ctx.emplace_back(*child);
        }
        ++index;
    }
}

nusap::buat_fungsi_ctx::buat_fungsi_ctx(const node& node) 
: 
id(node.children[0]->token->nilai) 
{
    /*
    0. token : identifikasi
    1. token : kurung buka
    2*? rule : buat variable
    end token : kurung tutup
    ++end. rule : blok kode
    */
    size_t index = 2;
    while(node.children[index]->tipe == tipe_node::buat_variable) {
        this->k_buat_variable.emplace_back(*node.children[index]);
        ++index;
    }
    ++index;
    this->blok_kode_ctx = nusap::blok_kode_ctx(*node.children[index]);
}

nusap::pernyataan_ctx::pernyataan_ctx(const node& node) {
    /*
    0*. rule : buat fungsi | buat variable
    */
    if(node.children[0]->tipe == tipe_node::buat_fungsi) {
        this->buat_fungsi_ctx = nusap::buat_fungsi_ctx(*node.children[0]);
    }else if(node.children[0]->tipe == tipe_node::buat_variable) {
        this->buat_variable_ctx = nusap::buat_variable_ctx(*node.children[0]);
    }
}

nusap::manggil_fungsi_ctx::manggil_fungsi_ctx(const node& node) 
: 
id(node.children[0]->token->nilai) {
    /*
    0. token : identifikasi
    1. token : kurung buka
    2*?. rule : ekspresi
    end. token : kurung tutup
    */
    size_t index = 2;
    while(node.children[index]->tipe == tipe_node::ekspresi) {
        this->k_ekspresi_ctx.emplace_back(*node.children[index]);
        ++index;
    }
}

nusap::pernyataan_blok_kode_ctx::pernyataan_blok_kode_ctx(const node& node) {
    /*
    0*. rule : buat fungsi | buat variable | manggil fungsi
    */
    if(node.children[0]->tipe == tipe_node::buat_fungsi) {
        this->buat_fungsi_ctx = nusap::buat_fungsi_ctx(*node.children[0]);
    }else if(node.children[0]->tipe == tipe_node::manggil_fungsi) {
        this->manggil_fungsi_ctx = nusap::manggil_fungsi_ctx(*node.children[0]);
    }else if(node.children[0]->tipe == tipe_node::buat_variable) {
        this->buat_variable_ctx = nusap::buat_variable_ctx(*node.children[0]);
    }
}

nusap::ekspresi_ctx::ekspresi_ctx(const node& node) {
    /*
    0*. rule : teks | bilangan
    */
    if(node.children[0]->tipe == tipe_node::teks) {
        this->teks_ctx = nusap::teks_ctx(*node.children[0]);
    }else if(node.children[0]->tipe == tipe_node::bilangan) {
        this->bilangan_ctx = nusap::bilangan_ctx(*node.children[0]);
    }
}

std::any nusap::visitor::visit(const node& node) {
    if(node.tipe == tipe_node::nusantara) {
        return this->visit_nusantara(nusantara_ctx(node));
    }
    if(node.tipe == tipe_node::pernyataan) {
        return this->visit_pernyataan(pernyataan_ctx(node));
    }
    if(node.tipe == tipe_node::pernyataan_blok_kode) {
        return this->visit_pernyataan_blok_kode(pernyataan_blok_kode_ctx(node));
    }
    if(node.tipe == tipe_node::ekspresi) {         
        return this->visit_ekspresi(ekspresi_ctx(node));
    }
    if(node.tipe == tipe_node::blok_kode) {         
        return this->visit_blok_kode(blok_kode_ctx(node));
    }
    if(node.tipe == tipe_node::teks) {         
        return this->visit_teks(teks_ctx(node));
    }
    if(node.tipe == tipe_node::bilangan) {         
        return this->visit_bilangan(bilangan_ctx(node));
    }
    if(node.tipe == tipe_node::buat_variable) {         
        return this->visit_buat_variable(buat_variable_ctx(node));
    }
    if(node.tipe == tipe_node::buat_fungsi) {         
        return this->visit_buat_fungsi(buat_fungsi_ctx(node));
    }
    if(node.tipe == tipe_node::manggil_fungsi) {         
        return this->visit_manggil_fungsi(manggil_fungsi_ctx(node));
    }
    return {};
}