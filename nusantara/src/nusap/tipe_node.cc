#include "nusap/tipe_node.h"

std::string Nusap::ubahKeString(const TipeNode& node) {
  switch(node) {
    case TipeNode::token:
      return "token";
    case TipeNode::nusantara:
      return "nusantara";
    case TipeNode::muat_file:
      return "muat file";
    case TipeNode::nilai_teks:
      return "nilai teks";
    case TipeNode::pernyataan:
      return "pernyataan";
  }
}
