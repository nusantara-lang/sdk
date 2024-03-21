#pragma once

#include "nusal/token.h"
#include "nusap/node.h"
#include <any>
#include <optional>
#include <vector>

namespace Nusap {

    struct TokenCtx {
        explicit TokenCtx(const Node& node);
        Nusal::Token token;
    };

    struct NilaiTeksCtx {
        explicit NilaiTeksCtx(const Node& node);
        std::vector<TokenCtx> kTokenCtx;
    };

    struct MuatFileCtx {
        explicit MuatFileCtx(const Node& node);
        TokenCtx tokenMuatCtx;
        NilaiTeksCtx nilaiTeksCtx;
    };

    struct PernyataanCtx {
        explicit PernyataanCtx(const Node& node);
        std::optional<MuatFileCtx> muatFileCtx;
        std::optional<TokenCtx> tokenTitikKomaCtx;
    };

    struct NusantaraCtx {
        explicit NusantaraCtx(const Node& node);
        std::vector<PernyataanCtx> kPernyataanCtx;
    };

    class Visitor {
        public:
          Visitor() = default;
          Visitor(const Visitor&) = default;
          Visitor(Visitor&&) = delete;
          Visitor& operator=(const Visitor&) = default;
          Visitor& operator=(Visitor&&) = delete;
          virtual ~Visitor() = default;

          std::any visit(const Node& node);

          virtual std::any visitToken(const TokenCtx& ctx) = 0;
          virtual std::any visitNilaiTeks(const NilaiTeksCtx& ctx) = 0;
          virtual std::any visitMuatFile(const MuatFileCtx& ctx) = 0;
          virtual std::any visitPernyataan(const PernyataanCtx& ctx) = 0;
          virtual std::any visitNusantara(const NusantaraCtx& ctx) = 0;

        private:
    };

}
