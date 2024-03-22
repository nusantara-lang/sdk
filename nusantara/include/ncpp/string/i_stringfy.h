#pragma once

#include <string>

namespace Ncpp {
    class IStringfy {
        public:
          IStringfy(const IStringfy&) = default;
          IStringfy(IStringfy&&) = delete;
          IStringfy& operator=(const IStringfy&) = default;
          IStringfy& operator=(IStringfy&&) = delete;
          virtual ~IStringfy() = default;
          virtual std::string ubahKeString();
        private:
    };
}