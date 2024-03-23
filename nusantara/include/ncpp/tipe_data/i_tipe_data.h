#pragma once

#include "ncpp/stream/i_streamable.h"

namespace Ncpp {
  template<typename Nilai> class ITipeData: public IStreamable {
    public:
      ITipeData() = default;
      ~ITipeData() override = default;
      ITipeData(const ITipeData&) = default;
      ITipeData(ITipeData&&) noexcept = default;
      ITipeData& operator=(const ITipeData&) = default;
      ITipeData& operator=(ITipeData&&) noexcept = default;
      [[nodiscard]] std::string ubahKeString() const override {
        return IStreamable::ubahKeString();
      }
    private:
    protected:
      Nilai nilai;
  };
} // namespace Ncpp
