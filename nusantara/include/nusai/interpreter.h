#pragma once

#include <functional>
#include <map>
#include <nusal/tipe_token.h>
#include <any>
#include <nusal/lexer.h>
#include <nusap/parser.h>
#include <nusap/visitor.h>
#include <string>

namespace nusai {

    class interpreter: private nusap::visitor {
        public:
            interpreter();
            void input(const std::string& input);
            void input(const std::string& sumber, const std::string& input);
            void input_filepath(const std::string& file_path);
        private:
						std::map<std::string, nusap::parser> k_parser;

            std::any visit_token(const nusap::token_ctx& ctx) override;
            std::any visit_nilai_teks(const nusap::nilai_teks_ctx& ctx) override;
            std::any visit_muat_file(const nusap::muat_file_ctx& ctx) override;
            std::any visit_pernyataan(const nusap::pernyataan_ctx& ctx) override;
            std::any visit_nusantara(const nusap::nusantara_ctx& ctx) override;
    };

}
