#pragma once

#include "ncpp/tipe_data/i_nilai_bilangan.h"
#include "ncpp/tipe_data/i_tipe_data.h"

#include <memory>

namespace Ncpp {
  class BilanganBulat;
  class BilanganDesimal;

  class Bilangan: public ITipeData<std::unique_ptr<INilaiBilangan>> {
    public:
      Bilangan();
      ~Bilangan() override;
      Bilangan(const Bilangan& other);
      Bilangan& operator=(const Bilangan& other);
      Bilangan(Bilangan&& other) noexcept;
      Bilangan& operator=(Bilangan&& other) noexcept;
      explicit Bilangan(const std::string& nilai);
      [[nodiscard]] bool iniBulat() const;
      [[nodiscard]] bool iniDesimal() const;
      [[nodiscard]] std::string ubahKeString() const override;
      Bilangan operator+(const Bilangan& nilai) const;
      Bilangan operator-(const Bilangan& nilai) const;
      Bilangan operator*(const Bilangan& nilai) const;
      Bilangan operator/(const Bilangan& nilai) const;
      Bilangan operator%(const Bilangan& nilai) const;
      Bilangan operator~() const;
      Bilangan& operator++();
      const Bilangan operator++(int);
      Bilangan& operator--();
      const Bilangan operator--(int);
      Bilangan operator&(const Bilangan& nilai) const;
      Bilangan operator^(const Bilangan& nilai) const;
      Bilangan operator|(const Bilangan& nilai) const;
      Bilangan operator<<(const Bilangan& nilai) const;
      Bilangan operator>>(const Bilangan& nilai) const;
      bool operator<(const Bilangan& nilai) const;
      bool operator<=(const Bilangan& nilai) const;
      bool operator>(const Bilangan& nilai) const;
      bool operator>=(const Bilangan& nilai) const;
      bool operator==(const Bilangan& nilai) const;
      bool operator!=(const Bilangan& nilai) const;
      Bilangan& operator+=(const Bilangan& nilai);
      Bilangan& operator-=(const Bilangan& nilai);
      Bilangan& operator*=(const Bilangan& nilai);
      Bilangan& operator/=(const Bilangan& nilai);
      Bilangan& operator%=(const Bilangan& nilai);
      Bilangan& operator&=(const Bilangan& nilai);
      Bilangan& operator^=(const Bilangan& nilai);
      Bilangan& operator|=(const Bilangan& nilai);
      Bilangan& operator<<=(const Bilangan& nilai);
      Bilangan& operator>>=(const Bilangan& nilai);
    private:
    protected:
      [[nodiscard]] const BilanganBulat& ambilNilaiBulat() const;
      [[nodiscard]] const BilanganDesimal& ambilNilaiDesimal() const;
  };
} // namespace Ncpp
