#include "nusal/token.h"

#include <format>

nusal::baris::baris(const size_t& nilai): nilai(nilai) {}

nusal::karakter::karakter(const size_t& nilai): nilai(nilai) {}

nusal::token::token(
    const tipe_token& tipe, std::string nama, std::string sumber,
    const nusal::baris& baris, const nusal::karakter& karakter,
    std::string nilai
):
    tipe(tipe),
    nama(std::move(nama)), sumber(std::move(sumber)), baris(baris),
    karakter(karakter), nilai(std::move(nilai)) {}

std::string nusal::ubah_ke_string(const token& token) {
  return std::format(
      "{}:{}:{} {} {}", token.sumber, token.baris.nilai, token.karakter.nilai,
      token.nama,
      (token.nilai == "\n")   ? "\\n"
      : (token.nilai == "\t") ? "\\t"
      : (token.nilai == "\r") ? "\\r"
                              : token.nilai
  );
}
