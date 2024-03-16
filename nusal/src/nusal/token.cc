#include "nusal/token.h"
#include <format>

nusal::token::token(
    const tipe_token& tipe,
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

std::string nusal::ubah_ke_string(const token& token) {
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
