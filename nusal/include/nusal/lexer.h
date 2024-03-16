#pragma once

#include "nusal/token.h"
#include <memory>
#include <map>

namespace nusal {

		class lexer {
        public:
            lexer() = default;
            void input(const std::string& input);
            void input(const std::string& sumber, const std::string& input);
            void input_filepath(const std::string& file_path);
            std::unique_ptr<token> ambil_token();
            static const std::string sumber_tidak_diketahui;
        private:
            size_t baris = 0;
            size_t karakter = 0;
            std::map<std::string, std::string> sumber_berserta_input = {};
    };

}
