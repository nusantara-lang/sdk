#pragma once

#include "ncpp/tipe_data/i_nilai_bilangan.h"
#include "ncpp/tipe_data/i_tipe_data.h"

#include <mpfr.h>
#include <regex>
#include <string>

namespace Ncpp {
  class BilanganBulat;

  class BilanganDesimal: public ITipeData<mpfr_t>, public INilaiBilangan {
    public:
      BilanganDesimal();
      ~BilanganDesimal() override;
      BilanganDesimal(const BilanganDesimal& other);
      BilanganDesimal& operator=(const BilanganDesimal& other);
      BilanganDesimal(BilanganDesimal&& other) noexcept;
      BilanganDesimal& operator=(BilanganDesimal&& other) noexcept;
      explicit BilanganDesimal(const std::string& nilai);
      [[nodiscard]] std::string ubahKeString() const override;
      [[nodiscard]] std::string ubahKeStringTetap(const long& presisi
      ) const;
      [[nodiscard]] std::string ubahKeStringPresisi(const long& presisi
      ) const;
      static std::regex pattern();
      static BilanganDesimal ubah(const BilanganBulat& nilai);
      static const short basis;
      static const short presisiStringBawaan;
      static const double toleransi;
      static const mpfr_rnd_t pembulatan;
      [[nodiscard]] long presisi() const;
      BilanganDesimal operator+(const BilanganBulat& nilai) const;
      BilanganDesimal operator+(const BilanganDesimal& nilai) const;
      BilanganDesimal operator-(const BilanganBulat& nilai) const;
      BilanganDesimal operator-(const BilanganDesimal& nilai) const;
      BilanganDesimal operator*(const BilanganBulat& nilai) const;
      BilanganDesimal operator*(const BilanganDesimal& nilai) const;
      BilanganDesimal operator/(const BilanganBulat& nilai) const;
      BilanganDesimal operator/(const BilanganDesimal& nilai) const;
      BilanganDesimal operator%(const BilanganBulat& nilai) const;
      BilanganDesimal operator%(const BilanganDesimal& nilai) const;
      BilanganDesimal& operator++();
      const BilanganDesimal operator++(int);
      BilanganDesimal& operator--();
      const BilanganDesimal operator--(int);
      bool operator<(const BilanganDesimal& nilai) const;
      bool operator<(const BilanganBulat& nilai) const;
      bool operator<=(const BilanganDesimal& nilai) const;
      bool operator<=(const BilanganBulat& nilai) const;
      bool operator>(const BilanganDesimal& nilai) const;
      bool operator>(const BilanganBulat& nilai) const;
      bool operator>=(const BilanganDesimal& nilai) const;
      bool operator>=(const BilanganBulat& nilai) const;
      bool operator==(const BilanganDesimal& nilai) const;
      bool operator==(const BilanganBulat& nilai) const;
      bool operator!=(const BilanganDesimal& nilai) const;
      bool operator!=(const BilanganBulat& nilai) const;
      BilanganDesimal& operator+=(const BilanganBulat& nilai);
      BilanganDesimal& operator+=(const BilanganDesimal& nilai);
      BilanganDesimal& operator-=(const BilanganBulat& nilai);
      BilanganDesimal& operator-=(const BilanganDesimal& nilai);
      BilanganDesimal& operator*=(const BilanganBulat& nilai);
      BilanganDesimal& operator*=(const BilanganDesimal& nilai);
      BilanganDesimal& operator/=(const BilanganBulat& nilai);
      BilanganDesimal& operator/=(const BilanganDesimal& nilai);
      BilanganDesimal& operator%=(const BilanganBulat& nilai);
      BilanganDesimal& operator%=(const BilanganDesimal& nilai);
      [[nodiscard]] const mpfr_t& ambil() const;
    private:
    protected:
  };

} // namespace Ncpp
