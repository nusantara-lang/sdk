#include "nusap/visitor.h"
#include "nusap/tipe_node.h"

std::any nusap::visitor::visit(const node& node) {
    if(node.tipe == tipe_node::nusantara) {
        nusantara_ctx ctx;
        return this->visit_nusantara(ctx);
    }
    if(node.tipe == tipe_node::pernyataan) {
        pernyataan_ctx ctx;
        return this->visit_pernyataan(ctx);
    }
    if(node.tipe == tipe_node::pernyataan_blok_kode) {
        pernyataan_blok_kode_ctx ctx;
        return this->visit_pernyataan_blok_kode(ctx);
    }
    if(node.tipe == tipe_node::ekspresi) {
        ekspresi_ctx ctx;
        return this->visit_ekspresi(ctx);
    }
    if(node.tipe == tipe_node::blok_kode) {
        blok_kode_ctx ctx;
        return this->visit_blok_kode(ctx);
    }
    if(node.tipe == tipe_node::teks) {
        teks_ctx ctx;
        return this->visit_teks(ctx);
    }
    if(node.tipe == tipe_node::bilangan) {
        bilangan_ctx ctx;
        return this->visit_bilangan(ctx);
    }
    if(node.tipe == tipe_node::buat_variable) {
        buat_variable_ctx ctx;
        return this->visit_buat_variable(ctx);
    }
    if(node.tipe == tipe_node::buat_fungsi) {
        buat_fungsi_ctx ctx;
        return this->visit_buat_fungsi(ctx);
    }
    if(node.tipe == tipe_node::manggil_fungsi) {
        manggil_fungsi_ctx ctx;
        return this->visit_manggil_fungsi(ctx);
    }
    return {};
}