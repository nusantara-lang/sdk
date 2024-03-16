#pragma once

#include "nusal/tipe_token.h"

namespace nusal {

	struct token {
        token() = default;
        token(
            const tipe_token& tipe,
            const std::string& nama,
            const std::string& sumber,
            const size_t& baris,
            const size_t& karakter,
            const std::string& nilai
        );
        tipe_token tipe = tipe_token::tidak_diketahui;
        std::string nama = "tidak_diketahui";
        std::string sumber = "tidak diketahui";
        size_t baris = 0;
        size_t karakter = 0;
        std::string nilai = "";
    };

    std::string ubah_ke_string(const token& token);

}
