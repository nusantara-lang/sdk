#pragma once

#include "lexer/token.h"

#include <exception>
#include <string>
#include <vector>

namespace Semantics {

  class KesalahanSemantics: public std::exception {
    public:
      KesalahanSemantics(
          const std::vector<Lexer::Token>& kToken, const std::string& pesan
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

} // namespace Semantics
