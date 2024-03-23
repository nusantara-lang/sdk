#pragma once

#include "lexer/token.h"

#include <exception>
#include <string>

namespace Parser {

  class KesalahanParse: public std::exception {
    public:
      KesalahanParse(const Lexer::Token& token, const std::string& pesan);

    private:
      [[nodiscard]] const char* what() const noexcept override;
      std::string pesan;
  };

} // namespace Parser
