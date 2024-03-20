#include "nusai/interpreter.h"
#include <iostream>
#include <string>

nusai::interpreter::interpreter() = default;

void nusai::interpreter::input(const std::string& input) {
    this->parser.input(input);
    this->visit(*this->parser.parse());
}

void nusai::interpreter::input(const std::string& sumber, const std::string& input) {
    this->parser.input(sumber, input);
    this->visit(*this->parser.parse());
}

void nusai::interpreter::input_filepath(const std::string& file_path) {
    this->parser.input_filepath(file_path);
    this->visit(*this->parser.parse());
}

std::any nusai::interpreter::visit_token(const nusap::token_ctx& ctx) {
    return {};
}

std::any nusai::interpreter::visit_nilai_teks(const nusap::nilai_teks_ctx& ctx) {
    return {};
}

std::any nusai::interpreter::visit_muat_file(const nusap::muat_file_ctx& ctx) {
    return {};
}

std::any nusai::interpreter::visit_pernyataan(const nusap::pernyataan_ctx& ctx) {
    return {};
}

std::any nusai::interpreter::visit_nusantara(const nusap::nusantara_ctx& ctx) {
    std::cout << "Interpreter belum bisa digunakan." << "\n";
    return {};
}

