#pragma once

#include "lexer/lexer.h"
#include "lexer/token.h"

#include <functional>
#include <string>

namespace Lexer {

  class TokenStream {
    public:
      explicit TokenStream(Lexer& lexer);
      bool tokenSaatIniAdalah(const std::string& tipe);
      bool tokenSaatIniAdalah(const std::vector<std::string>& tipe);
      const Token& tokenSelanjutNya(const bool& skip = true);
      const Token& getTokenSaatIni();

    private:
      std::reference_wrapper<Lexer> lexer;
      Token tokenSaatIni;

    protected:
  };

} // namespace Lexer
