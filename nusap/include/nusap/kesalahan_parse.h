#pragma once

#include "nusal/token.h"
#include <exception>
#include <string>

namespace nusap {

    class kesalahan_parser: public std::exception {
        public:
            kesalahan_parser(const nusal::token& token, const std::string& pesan);
        private:
            [[nodiscard]] const char * what() const noexcept override;
            std::string pesan;      
    };

}