#include "nusap/tipe_node.h"

std::string nusap::ubah_ke_string(const tipe_node& node) {
    switch (node) {
      case tipe_node::nusantara:
        return "nusantara";
      case tipe_node::token:
        return "token";
      case tipe_node::pernyataan:
        return "pernyataan";
      case tipe_node::ekspresi:
        return "ekspresi";
      case tipe_node::teks:
        return "teks";
      case tipe_node::bilangan:
        return "bilangan";
      case tipe_node::buat_variable:
        return "buat variable";
      case tipe_node::buat_fungsi:
        return "buat fungsi";
      case tipe_node::manggil_fungsi:
        return "manggil fungsi";
      case tipe_node::pernyataan_blok_kode:
        return "pernyataan blok kode";
      case tipe_node::blok_kode:
        return "blok kode";
    }
}