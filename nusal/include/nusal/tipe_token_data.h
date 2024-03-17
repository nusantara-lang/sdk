#pragma once

#include <string>

namespace nusal {

	template<typename T>
	struct tipe_token_data {
        tipe_token_data(
            const T& tipe,
            const std::string& nama,
            const std::string& pola
        ):
			    tipe(tipe),
			    nama(nama),
			    pola(pola)
				{}
        T tipe;
        std::string nama;
        std::string pola;
  };

}
