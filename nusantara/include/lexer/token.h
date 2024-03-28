#pragma once

#include "lexer/tipe_token.h"
#include "ncpp/stream/i_streamable.h"

#include <string>

namespace Lexer {

  class Token: public Ncpp::IStreamable {
    public:
        struct Baris {
            Baris() = default;

            explicit Baris(const size_t& nilai);

            size_t nilai = 0;
        };

        struct Karakter {
            Karakter() = default;

            explicit Karakter(const size_t& nilai);

            size_t nilai = 0;
        };

        Token();

        Token(
          const TipeToken& tipe, std::string sumber, const Baris& baris,
          const Karakter& karakter, std::string nilai
        );
        Token(
          const TipeToken& tipe, std::string sumber, const Baris& baris,
          const Karakter& karakter, const char& nilai
        );
        [[nodiscard]] std::string ubahKeString() const override;

        [[nodiscard]] const TipeToken& getTipe() const;
        [[nodiscard]] const std::string& getSumber() const;
        [[nodiscard]] const size_t& getBaris() const;
        [[nodiscard]] const size_t& getKarakter() const;
        [[nodiscard]] const std::string& getNilai() const;

        void setTipe(const TipeToken& tipe);
        void setSumber(const std::string& sumber);
        void setBaris(const size_t& baris);
        void setKarakter(const size_t& karakter);
        void setNilai(const std::string& nilai);
        void setNilai(const char& nilai);

    private:
        TipeToken tipe;
        std::string sumber;
        size_t baris = 0;
        size_t karakter = 0;
        std::string nilai;

    protected:
  };

} // namespace Lexer
