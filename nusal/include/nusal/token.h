#pragma once

#include <format>
#include <string>

namespace nusal {

	template<typename T>
	struct token {
        token() = default;
        token(
            const T& tipe,
            const std::string& nama,
            const std::string& sumber,
            const size_t& baris,
            const size_t& karakter,
            const std::string& nilai
        ):
			    tipe(tipe),
			    nama(nama),
			    sumber(sumber),
			    baris(baris),
			    karakter(karakter),
			    nilai(nilai)
				{}
        T tipe = T::tidak_diketahui;
        std::string nama = "tidak_diketahui";
        std::string sumber = "tidak diketahui";
        size_t baris = 0;
        size_t karakter = 0;
        std::string nilai = "";
    };

		template<typename T>
    std::string ubah_ke_string(const token<T>& token) {
		  return std::format(
				"{}:{}:{} {} {}",
				token.sumber, 
				token.baris, 
				token.karakter, 
				token.nama, 
				(token.nilai == "\n") ? "\\n" :
				(token.nilai == "\t") ? "\\t" :
				token.nilai
			);
		}

}
