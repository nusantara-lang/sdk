#include "nusai/interpreter.h"

#include "nusal/token.h"
#include "nusap/parser.h"
#include <any>
#include <stdexcept>
#include <string>

nusai::interpreter::interpreter() = default;

void nusai::interpreter::input(const std::string& input) {
		std::string sumber("tidak diketahui");
		if(this->k_parser.find(sumber) == this->k_parser.end()) {
			auto& parser = this->k_parser[sumber];
			parser = nusap::parser();
			parser.input(input);
			if(const auto node = parser.parse()) {
				this->visit(*node);
			}
		}	
}

void nusai::interpreter::input(const std::string& sumber, const std::string& input) {
  if(this->k_parser.find(sumber) == this->k_parser.end()) {
			auto& parser = this->k_parser[sumber];
			parser = nusap::parser();
			parser.input(sumber, input);
			if(const auto node = parser.parse()) {
				this->visit(*node);
			}
	} 
}

void nusai::interpreter::input_filepath(const std::string& file_path) {
  if(this->k_parser.find(file_path) == this->k_parser.end()) {
			auto& parser = this->k_parser[file_path];
			parser = nusap::parser();
			parser.input_filepath(file_path);
			if(const auto node = parser.parse()) {
				this->visit(*node);
			}
	}
}

std::any nusai::interpreter::visit_token(const nusap::token_ctx& ctx) {
    return ctx.token;
}

std::any nusai::interpreter::visit_nilai_teks(const nusap::nilai_teks_ctx& ctx) {
		std::string teks;
		for(const auto& token_ctx : ctx.k_token_ctx) {
			std::any tokenAny = this->visit_token(token_ctx);
			if(const auto* token = std::any_cast<nusal::token>(&tokenAny)) {
				teks += token->nilai;
			}
		}
    return teks;
}

std::any nusai::interpreter::visit_muat_file(const nusap::muat_file_ctx& ctx) {
	std::any nilaiTeksAny = this->visit_nilai_teks(ctx.nilai_teks_ctx);
	if(const auto* nilaiTeks = std::any_cast<std::string>(&nilaiTeksAny)) {
		this->input_filepath(*nilaiTeks);
	}
  return {};
}

std::any nusai::interpreter::visit_pernyataan(const nusap::pernyataan_ctx& ctx) {
	if(ctx.muat_file_ctx.has_value()) {
		return this->visit_muat_file(ctx.muat_file_ctx.value());
	}
	throw std::runtime_error("Pernyataan tidak valid.");
}

std::any nusai::interpreter::visit_nusantara(const nusap::nusantara_ctx& ctx) {
		for(const auto& pernyataan_ctx : ctx.k_pernyataan_ctx) {
			this->visit_pernyataan(pernyataan_ctx);
		}
    return 0;
}

