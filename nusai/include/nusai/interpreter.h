#pragma once

#include <nusal/tipe_token.h>
#include <any>
#include <functional>
#include <map>
#include <nusal/lexer.h>
#include <nusap/parser.h>
#include <nusap/visitor.h>
#include <string>
#include <vector>

namespace nusai {

    struct variable {
        nusal::tipe_token tipe;
        std::any nilai;
    };

    struct kawasan {
        std::map<std::string, variable> variables;
        std::map<std::string, std::function<std::any(std::vector<nusap::ekspresi_ctx>)>> functions;
    };

    class interpreter: private nusap::visitor {
        public:
            interpreter();
            void input(const std::string& input);
            void input(const std::string& sumber, const std::string& input);
            void input_filepath(const std::string& file_path);
        private:
            nusap::parser parser;
            std::string kawasan_global = "global";
            std::string kawasan_yang_digunakan = kawasan_global;
            std::map<std::string, kawasan> k_kawasan;
            std::any visit_nusantara(const nusap::nusantara_ctx& ctx) override;
            std::any visit_pernyataan(const nusap::pernyataan_ctx& ctx) override;
            std::any visit_pernyataan_blok_kode(const nusap::pernyataan_blok_kode_ctx& ctx) override;
            std::any visit_ekspresi(const nusap::ekspresi_ctx& ctx) override;
            std::any visit_blok_kode(const nusap::blok_kode_ctx& ctx) override;
            std::any visit_teks(const nusap::teks_ctx& ctx) override;
            std::any visit_bilangan(const nusap::bilangan_ctx& ctx) override;
            std::any visit_buat_variable(const nusap::buat_variable_ctx& ctx) override;
            std::any visit_buat_fungsi(const nusap::buat_fungsi_ctx& ctx) override;
            std::any visit_manggil_fungsi(const nusap::manggil_fungsi_ctx& ctx) override;
    };

}