#pragma once

#include "ncpp/string/i_stringfy.h"

namespace Ncpp {
    class IStreamable: public IStringfy {
        public:
            [[nodiscard]] std::string ubahKeString() const override {return IStringfy::ubahKeString();}
        private:
            friend std::ostream& operator<<(std::ostream& ostrean, const IStreamable& obj) {
                ostrean << obj.ubahKeString();
                return ostrean;
            }
    };
}