#include "nusal/token.h"

#include "nusal/tipe_token.h"

#include <format>

nusal::baris::baris(const size_t& nilai): nilai(nilai) {}

nusal::karakter::karakter(const size_t& nilai): nilai(nilai) {}

nusal::token::token(
    const tipe_token& tipe, std::string sumber, const nusal::baris& baris,
    const nusal::karakter& karakter, std::string nilai
):
    tipe(tipe),
    sumber(std::move(sumber)), baris(baris), karakter(karakter),
    nilai(std::move(nilai)) {}

std::string nusal::ubah_ke_string(const token& token) {
  return std::format(
      "{}:{}:{} {} {}", token.sumber, token.baris.nilai, token.karakter.nilai,
      ubah_ke_string(token.tipe),
      (token.nilai == "\n")   ? "\\n"
      : (token.nilai == "\t") ? "\\t"
      : (token.nilai == "\r") ? "\\r"
                              : token.nilai
  );
}
