#pragma once

#include "ncpp/string/i_stringfy.h"

namespace Ncpp {
  template<typename Nilai> class ITipeData: public IStringfy {
    public:
      ITipeData() = default;
      ~ITipeData() override = default;
      ITipeData(const ITipeData&) = default;
      ITipeData(ITipeData&&) noexcept = default;
      ITipeData& operator=(const ITipeData&) = default;
      ITipeData& operator=(ITipeData&&) noexcept = default;
      [[nodiscard]] std::string ubahKeString() const override {
        return IStringfy::ubahKeString();
      }
    private:
    protected:
      Nilai nilai;
  };
} // namespace Ncpp
