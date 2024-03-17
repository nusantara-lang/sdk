#pragma once

#include <format>
#include <string>
#include <utility>

namespace nusal {

  struct baris {
      baris() = default;

      explicit baris(const size_t& nilai): nilai(nilai) {}

      size_t nilai = 0;
  };

  struct karakter {
      karakter() = default;

      explicit karakter(const size_t& nilai): nilai(nilai) {}

      size_t nilai = 0;
  };

  template<typename T> struct token {
      token() = default;

      token(
          const T& tipe, std::string nama, std::string sumber,
          const baris& baris, const karakter& karakter, std::string nilai
      ):
          tipe(tipe),
          nama(std::move(nama)), sumber(std::move(sumber)), baris(baris),
          karakter(karakter), nilai(std::move(nilai)) {}

      T tipe = T::TIDAK_DIKETAHUI;
      std::string nama = "tidak_diketahui";
      std::string sumber = "tidak diketahui";
      baris baris;
      karakter karakter;
      std::string nilai;
  };

  template<typename T> std::string ubah_ke_string(const token<T>& token) {
    return std::format(
        "{}:{}:{} {} {}", token.sumber, token.baris.nilai, token.karakter.nilai,
        token.nama,
        (token.nilai == "\n")   ? "\\n"
        : (token.nilai == "\t") ? "\\t"
        : (token.nilai == "\r") ? "\\r"
                                : token.nilai
    );
  }

} // namespace nusal
