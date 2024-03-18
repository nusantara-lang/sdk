#include "nusai/interpreter.h"

nusai::interpreter::interpreter() = default;

void nusai::interpreter::input(const std::string& input) {
    this->parser.input(input);
    this->interpret();
}

void nusai::interpreter::input(const std::string& sumber, const std::string& input) {
    this->parser.input(sumber, input);
    this->interpret();
}

void nusai::interpreter::input_filepath(const std::string& file_path) {
    this->parser.input_filepath(file_path);
    this->interpret();
}
void nusai::interpreter::interpret() {
    this->interpret(*this->parser.parse());
}

void nusai::interpreter::interpret(const nusap::node& root) {
    switch(root.tipe) {
      case nusap::tipe_node::nusantara:
        for(const auto& child : root.children) {
            this->interpret(*child);
        }
        break;
      case nusap::tipe_node::token:
        this->tokens.push_back(*root.token);
        break;
      case nusap::tipe_node::pernyataan:
      case nusap::tipe_node::pernyataan_blok_kode:
      case nusap::tipe_node::ekspresi:
      case nusap::tipe_node::teks:
      case nusap::tipe_node::bilangan:
      case nusap::tipe_node::buat_variable:
      case nusap::tipe_node::buat_fungsi:
      case nusap::tipe_node::manggil_fungsi:
      case nusap::tipe_node::blok_kode:
        break;
    }
}
