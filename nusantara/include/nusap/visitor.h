#pragma once

#include "nusal/token.h"
#include "nusap/node.h"
#include <any>
#include <string>
#include <vector>

namespace nusap {

    struct token_ctx {
        explicit token_ctx(const node& node);
        nusal::token token;
    };

    struct nilai_teks_ctx {
        explicit nilai_teks_ctx(const node& node);
        std::vector<token_ctx> k_token_ctx;
    };

    struct muat_file_ctx {
        explicit muat_file_ctx(const node& node);
        std::string lokasiFile;
    };

    struct pernyataan_ctx {
        explicit pernyataan_ctx(const node& node);
        muat_file_ctx muat_file_ctx;
    };

    struct nusantara_ctx {
        explicit nusantara_ctx(const node& node);
        std::vector<pernyataan_ctx> k_pernyataan_ctx;
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

          virtual std::any visit_token(const token_ctx& ctx) = 0;
          virtual std::any visit_nilai_teks(const nilai_teks_ctx& ctx) = 0;
          virtual std::any visit_muat_file(const muat_file_ctx& ctx) = 0;
          virtual std::any visit_pernyataan(const pernyataan_ctx& ctx) = 0;
          virtual std::any visit_nusantara(const nusantara_ctx& ctx) = 0;

        private:
    };

}