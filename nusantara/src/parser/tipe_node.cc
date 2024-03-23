#include "parser/tipe_node.h"

std::string Parser::ubahKeString(const TipeNode& node) {
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
    case TipeNode::nilai_bilangan:
      return "nilai bilangan";
    case TipeNode::ekspresi:
      return "ekspresi";
    case TipeNode::nilai:
      return "nilai";
  }
}
