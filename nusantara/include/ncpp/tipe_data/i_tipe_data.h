#pragma once

#include "ncpp/string/i_stringfy.h"

namespace Ncpp {
    template<typename Nilai>
    class ITipeData: public IStringfy {
        public:
            explicit ITipeData(const Nilai& nilai);
        private:
            Nilai nilai;
    };
}