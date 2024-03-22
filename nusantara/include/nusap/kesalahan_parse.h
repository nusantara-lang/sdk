#pragma once

#include "nusal/token.h"

#include <exception>
#include <memory>
#include <string>

namespace Nusap {

  class KesalahanParse: public std::exception {
    public:
      KesalahanParse(
          const std::unique_ptr<Nusal::Token>& token, const std::string& pesan
      );

    private:
      [[nodiscard]] const char* what() const noexcept override;
      std::string pesan;
  };

} // namespace Nusap
