#pragma once

#include "nusal/token.h"
#include <map>
#include <nusal/tipe_token.h>
#include <any>
#include <nusal/lexer.h>
#include <nusap/parser.h>
#include <nusap/visitor.h>
#include <string>
#include <vector>

namespace Nusai {

    class Interpreter: private Nusap::Visitor {
        public:
            Interpreter();
            void input(const std::string& input);
            void input(const std::string& sumber, const std::string& input);
            void inputFilePath(const std::string& filePath);
        private:
			std::map<std::string, Nusap::Parser> kParser;
            std::vector<Nusal::Token> kToken;

            std::any visitToken(const Nusap::TokenCtx& ctx) override;
            std::any visitNilaiTeks(const Nusap::NilaiTeksCtx& ctx) override;
            std::any visitMuatFile(const Nusap::MuatFileCtx& ctx) override;
            std::any visitPernyataan(const Nusap::PernyataanCtx& ctx) override;
            std::any visitNusantara(const Nusap::NusantaraCtx& ctx) override;
    };

}
