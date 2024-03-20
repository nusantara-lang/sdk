#include "nusap/tipe_node.h"

std::string nusap::ubah_ke_string(const tipe_node& node) {
  switch(node) {
    case tipe_node::token:
      return "token";
    case tipe_node::nusantara:
      return "nusantara";
    case tipe_node::muat_file:
      return "muat file";
    case tipe_node::nilai_teks:
      return "nilai teks";
    case tipe_node::pernyataan:
      return "pernyataan";
  }
}
