#pragma once

#include <string>
namespace nusap {

  enum class tipe_node {
    nusantara,
    pernyataan,
    membuat_kata_kunci,
    token
  };

  std::string ubah_ke_string(const tipe_node& node);

}
