#pragma once

#include <string>

namespace Ncpp {
    class IStringfy {
        public:
          IStringfy() = default;
          IStringfy(const IStringfy&) = default;
          IStringfy(IStringfy&&) = delete;
          IStringfy& operator=(const IStringfy&) = default;
          IStringfy& operator=(IStringfy&&) = delete;
          virtual ~IStringfy() = default;
          [[nodiscard]] virtual std::string ubahKeString() const;
        private:
    };
}