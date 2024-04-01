#pragma once

#include "ncpp/stream/i_streamable.h"

#include <string>

namespace Lexer {

  class TipeToken: public Ncpp::IStreamable {
    public:
      struct Nama {
          explicit Nama(std::string nilai);
          std::string nilai;
      };

      struct Pola {
          explicit Pola(std::string nilai);
          std::string nilai;
      };

      TipeToken() = default;

      TipeToken(const Nama& nama, const Pola& pola, const bool& skip);
      [[nodiscard]] std::string ubahKeString() const override;

      [[nodiscard]] const std::string& getNama() const;
      [[nodiscard]] const std::string& getPola() const;
      [[nodiscard]] const bool& isSkip() const;

    private:
      std::string nama;
      std::string pola;
      bool skip = false;

    protected:
  };

} // namespace Lexer
