#pragma once

#include <string>
#include <utility>

namespace nusal {

  template<typename T> struct tipe_token_data {
      tipe_token_data(const T& tipe, std::string nama, std::string pola):
          tipe(tipe), nama(std::move(nama)), pola(std::move(pola)) {}

      T tipe;
      std::string nama;
      std::string pola;
  };

} // namespace nusal
