#pragma once

#include "ncpp/tipe_data/i_nilai_bilangan.h"
#include "ncpp/tipe_data/i_tipe_data.h"

#include <gmp.h>
#include <regex>
#include <string>

namespace Ncpp {
  class BilanganDesimal;

  class BilanganBulat: public ITipeData<mpz_t>, public INilaiBilangan {
    public:
      BilanganBulat();
      ~BilanganBulat() override;
      BilanganBulat(const BilanganBulat& other);
      BilanganBulat& operator=(const BilanganBulat& other);
      BilanganBulat(BilanganBulat&& other) noexcept;
      BilanganBulat& operator=(BilanganBulat&& other) noexcept;
      explicit BilanganBulat(const short& nilai);
      explicit BilanganBulat(const int& nilai);
      explicit BilanganBulat(const long& nilai);
      explicit BilanganBulat(const long long& nilai);
      explicit BilanganBulat(const unsigned& nilai);
      explicit BilanganBulat(const unsigned short& nilai);
      explicit BilanganBulat(const unsigned long& nilai);
      explicit BilanganBulat(const unsigned long long& nilai);
      explicit BilanganBulat(const std::string& nilai);
      [[nodiscard]] std::string ubahKeString() const override;
      static std::regex pattern();
      static BilanganBulat ubah(const BilanganDesimal& nilai);
      static const int basis;
      BilanganBulat operator+(const BilanganBulat& nilai) const;
      BilanganDesimal operator+(const BilanganDesimal& nilai) const;
      BilanganBulat operator-(const BilanganBulat& nilai) const;
      BilanganDesimal operator-(const BilanganDesimal& nilai) const;
      BilanganBulat operator*(const BilanganBulat& nilai) const;
      BilanganDesimal operator*(const BilanganDesimal& nilai) const;
      BilanganDesimal operator/(const BilanganBulat& nilai) const;
      BilanganDesimal operator/(const BilanganDesimal& nilai) const;
      BilanganBulat operator%(const BilanganBulat& nilai) const;
      BilanganDesimal operator%(const BilanganDesimal& nilai) const;
      BilanganBulat operator~() const;
      BilanganBulat& operator++();
      const BilanganBulat operator++(int);
      BilanganBulat& operator--();
      const BilanganBulat operator--(int);
      BilanganBulat operator&(const BilanganBulat& nilai) const;
      BilanganBulat operator^(const BilanganBulat& nilai) const;
      BilanganBulat operator|(const BilanganBulat& nilai) const;
      BilanganBulat operator<<(const BilanganBulat& nilai) const;
      BilanganBulat operator>>(const BilanganBulat& nilai) const;
      bool operator<(const BilanganBulat& nilai) const;
      bool operator<(const BilanganDesimal& nilai) const;
      bool operator<=(const BilanganBulat& nilai) const;
      bool operator<=(const BilanganDesimal& nilai) const;
      bool operator>(const BilanganBulat& nilai) const;
      bool operator>(const BilanganDesimal& nilai) const;
      bool operator>=(const BilanganBulat& nilai) const;
      bool operator>=(const BilanganDesimal& nilai) const;
      bool operator==(const BilanganBulat& nilai) const;
      bool operator==(const BilanganDesimal& nilai) const;
      bool operator!=(const BilanganBulat& nilai) const;
      bool operator!=(const BilanganDesimal& nilai) const;
      BilanganBulat& operator+=(const BilanganBulat& nilai);
      BilanganBulat& operator-=(const BilanganBulat& nilai);
      BilanganBulat& operator*=(const BilanganBulat& nilai);
      BilanganBulat& operator/=(const BilanganBulat& nilai);
      BilanganBulat& operator%=(const BilanganBulat& nilai);
      BilanganBulat& operator&=(const BilanganBulat& nilai);
      BilanganBulat& operator^=(const BilanganBulat& nilai);
      BilanganBulat& operator|=(const BilanganBulat& nilai);
      BilanganBulat& operator<<=(const BilanganBulat& nilai);
      BilanganBulat& operator>>=(const BilanganBulat& nilai);
      [[nodiscard]] mpz_t& ambil() const;
    private:
    protected:
  };

} // namespace Ncpp
