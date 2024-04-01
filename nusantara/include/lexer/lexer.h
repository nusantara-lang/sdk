#pragma once

#include "lexer/tipe_token.h"
#include "lexer/token.h"

#include <functional>
#include <map>
#include <string>
#include <vector>

namespace Lexer {

  class Lexer {
    public:
      Lexer(
          std::vector<TipeToken>& tipeTokens,
          const size_t& indexTipeTokenTidakDiketahui,
          const size_t& indexTipeTokenAkhirDariFile
      );

      void input(const std::string& input);

      void input(const std::string& sumber, const std::string& input);

      void inputFilePath(const std::string& filePath);

      Token tokenSelanjutNya();

      [[nodiscard]] const std::vector<TipeToken>& getTipeTokens() const;

    private:
      std::reference_wrapper<std::vector<TipeToken>> tipeTokens;
      Token::Baris baris;
      Token::Karakter karakter;
      std::map<std::string, std::string> sumberBersertaInput = {};
      size_t indexTipeTokenTidakDiketahui;
      size_t indexTipeTokenAkhirDariFile;
      std::unique_ptr<Token>
      generateToken(std::string& input, const std::string& sumber);
  };

} // namespace Lexer
