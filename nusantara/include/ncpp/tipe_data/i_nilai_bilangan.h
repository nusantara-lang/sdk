#pragma once

namespace Ncpp {
  class INilaiBilangan {
    public:
      INilaiBilangan() = default;
      INilaiBilangan(const INilaiBilangan&) = default;
      INilaiBilangan(INilaiBilangan&&) noexcept = default;
      INilaiBilangan& operator=(const INilaiBilangan&) = default;
      INilaiBilangan& operator=(INilaiBilangan&&) noexcept = default;
      virtual ~INilaiBilangan() = default;
    private:
  };
} // namespace Ncpp
