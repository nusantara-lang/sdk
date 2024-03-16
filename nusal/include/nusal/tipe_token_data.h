#pragma once

#include "nusal/tipe_token.h"

namespace nusal {

	struct tipe_token_data {
        tipe_token_data(
            const tipe_token& tipe,
            const std::string& nama,
            const std::string& pola
        );
        tipe_token tipe;
        std::string nama;
        std::string pola;
  };

}
