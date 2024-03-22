#pragma once

#include "ncpp/string/i_stringfy.h"

namespace Ncpp {
  template<typename Nilai> class ITipeData: public IStringfy {
    public:
      ITipeData() = default;
      ~ITipeData() override;
      ITipeData(const ITipeData&) = default;
      ITipeData(ITipeData&&) noexcept = default;
      ITipeData& operator=(const ITipeData&) = default;
      ITipeData& operator=(ITipeData&&) noexcept = default;
      [[nodiscard]] std::string ubahKeString() const override {
        return IStringfy::ubahKeString();
      }

    private:
      Nilai nilai;

    protected:
      Nilai& ambil() const;
  };
} // namespace Ncpp
