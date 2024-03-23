#include "semantic_analysis/semantic_analysis.h"

void SemanticAnalysis::input(const std::string& input) {
    this->parser.input(input);
}

void SemanticAnalysis::input(const std::string& sumber, const std::string& input) {
    this->parser.input(sumber, input);
}

void SemanticAnalysis::inputFilePath(const std::string& filePath) {
    this->parser.inputFilePath(filePath);
}

std::any SemanticAnalysis::visitToken(const Parser::TokenCtx& ctx) {
    return {};
}

std::any SemanticAnalysis::visitNilaiTeks(const Parser::NilaiTeksCtx& ctx) {
    return {};
}

std::any SemanticAnalysis::visitMuatFile(const Parser::MuatFileCtx& ctx) {
    return {};
}

std::any SemanticAnalysis::visitPernyataan(const Parser::PernyataanCtx& ctx) {
    return {};
}

std::any SemanticAnalysis::visitNusantara(const Parser::NusantaraCtx& ctx) {
    return {};
}

std::any SemanticAnalysis::visitNilaiBilangan(const Parser::NilaiBilanganCtx& ctx) {
    return {};
}

std::any SemanticAnalysis::visitEkspresi(const Parser::EkspresiCtx& ctx) {
    return {};
}

std::any SemanticAnalysis::visitNilai(const Parser::NilaiCtx& ctx) {
    return {};
}