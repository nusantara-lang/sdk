#pragma once

#include "nusal/token.h"
#include "nusal/tipe_token_data.h"
#include <memory>
#include <vector>

namespace nusal {

	std::unique_ptr<token> buat_token(
    std::string& input, 
    size_t& baris,
    size_t& karakter,
    const std::string& sumber,
    const std::vector<tipe_token_data>& datas
  );

	std::string baca_file(const std::string& file_path);

}
