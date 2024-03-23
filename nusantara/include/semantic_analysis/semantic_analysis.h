#pragma once

#include "parser/parser.h"
#include "parser/visitor.h"

class SemanticAnalysis: public Parser::Visitor {
    public:
        void input(const std::string& input);
        void input(const std::string& sumber, const std::string& input);
        void inputFilePath(const std::string& filePath);
    private:
        Parser::Parser parser;
        std::any visitToken(const Parser::TokenCtx& ctx) override;
        std::any visitNilaiTeks(const Parser::NilaiTeksCtx& ctx) override;
        std::any visitMuatFile(const Parser::MuatFileCtx& ctx) override;
        std::any visitPernyataan(const Parser::PernyataanCtx& ctx) override;
        std::any visitNusantara(const Parser::NusantaraCtx& ctx) override;
        std::any visitNilaiBilangan(const Parser::NilaiBilanganCtx& ctx) override;
        std::any visitEkspresi(const Parser::EkspresiCtx& ctx) override;
        std::any visitNilai(const Parser::NilaiCtx& ctx) override;
    protected:
};