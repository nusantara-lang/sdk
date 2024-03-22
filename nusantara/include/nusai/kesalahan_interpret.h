#pragma once

#include "nusal/token.h"

#include <exception>
#include <string>
#include <vector>

namespace Nusai {

  class KesalahanInterpret: public std::exception {
    public:
      KesalahanInterpret(
          const std::vector<Nusal::Token>& kToken, const std::string& pesan
      );

      struct Data {
          std::string sumber;
          size_t baris = 0;
          size_t indexKarakterAwal = 0;
          size_t indexKarakterAkhir = 0;
      };

    private:
      [[nodiscard]] const char* what() const noexcept override;
      std::string pesan;
  };

} // namespace Nusai
