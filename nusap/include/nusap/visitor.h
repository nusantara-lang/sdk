#pragma once

#include "nusal/tipe_token.h"
#include "nusal/token.h"
#include "nusap/node.h"
#include <any>
#include <optional>
#include <string>
#include <vector>

namespace nusap {

    struct pernyataan_ctx;

    struct nusantara_ctx {
        explicit nusantara_ctx(const node& node);
        std::vector<pernyataan_ctx> k_pernyataan_ctx;
    };

    struct teks_ctx {
        explicit teks_ctx(const node& node);
        std::vector<nusal::token> k_token;
    };

    struct bilangan_ctx {
        explicit bilangan_ctx(const node& node);
        std::vector<nusal::token> k_token;
    };

    struct buat_variable_ctx {
        explicit buat_variable_ctx(const node& node);
        nusal::tipe_token tipe;
        std::string id;
        std::optional<teks_ctx> teks_ctx;
        std::optional<bilangan_ctx> bilangan_ctx;
    };

    struct pernyataan_blok_kode_ctx;

    struct blok_kode_ctx {
        blok_kode_ctx() = default;
        explicit blok_kode_ctx(const node& node);
        std::vector<pernyataan_blok_kode_ctx> k_pernyataan_blok_kode_ctx;
    };

    struct buat_fungsi_ctx {
        explicit buat_fungsi_ctx(const node& node);
        std::string id;
        std::vector<buat_variable_ctx> k_buat_variable;
        blok_kode_ctx blok_kode_ctx;
    };

    struct pernyataan_ctx {
        explicit pernyataan_ctx(const node& node);
        std::optional<buat_fungsi_ctx> buat_fungsi_ctx;
        std::optional<buat_variable_ctx> buat_variable_ctx;
    };

    struct ekspresi_ctx;

    struct manggil_fungsi_ctx {
        explicit manggil_fungsi_ctx(const node& node);
        std::string id;
        std::vector<ekspresi_ctx> k_ekspresi_ctx;
    };

    struct pernyataan_blok_kode_ctx {
        explicit pernyataan_blok_kode_ctx(const node& node);
        std::optional<buat_fungsi_ctx> buat_fungsi_ctx;
        std::optional<manggil_fungsi_ctx> manggil_fungsi_ctx;
        std::optional<buat_variable_ctx> buat_variable_ctx;
    };

    struct ekspresi_ctx {
        explicit ekspresi_ctx(const node& node);
        std::optional<teks_ctx> teks_ctx;
        std::optional<bilangan_ctx> bilangan_ctx;
    };

    class visitor {
        public:
            visitor() = default;
          visitor(const visitor&) = default;
          visitor(visitor&&) = delete;
          visitor& operator=(const visitor&) = default;
          visitor& operator=(visitor&&) = delete;
          virtual ~visitor() = default;

          std::any visit(const node& node);

          virtual std::any visit_nusantara(const nusantara_ctx& ctx) = 0;
          virtual std::any visit_pernyataan(const pernyataan_ctx& ctx) = 0;
          virtual std::any visit_pernyataan_blok_kode(const pernyataan_blok_kode_ctx& ctx) = 0;
          virtual std::any visit_ekspresi(const ekspresi_ctx& ctx) = 0;
          virtual std::any visit_blok_kode(const blok_kode_ctx& ctx) = 0;
          virtual std::any visit_teks(const teks_ctx& ctx) = 0;
          virtual std::any visit_bilangan(const bilangan_ctx& ctx) = 0;
          virtual std::any visit_buat_variable(const buat_variable_ctx& ctx) = 0;
          virtual std::any visit_buat_fungsi(const buat_fungsi_ctx& ctx) = 0;
          virtual std::any visit_manggil_fungsi(const manggil_fungsi_ctx& ctx) = 0;

        private:
    };

}