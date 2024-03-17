#include "nusap/tipe_node.h"

std::string nusap::ubah_ke_string(const tipe_node& node) {
    switch (node) {
      case tipe_node::nusantara:
        return "nusantara";
      case tipe_node::pernyataan:
        return "pernyataan";
      case tipe_node::membuat_kata_kunci:
        return "membuat kata kunci";
      case tipe_node::token:
        return "token";
    }
}