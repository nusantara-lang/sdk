#include "nusai/interpreter.h"
#include "nusai/kesalahan_interpret.h"
#include "nusal/token.h"
#include "nusap/parser.h"
#include <any>
#include <string>

Nusai::Interpreter::Interpreter() = default;

void Nusai::Interpreter::input(const std::string& input) {
		std::string sumber("tidak diketahui");
		if(this->kParser.find(sumber) == this->kParser.end()) {
			auto& parser = this->kParser[sumber];
			parser = Nusap::Parser();
			parser.input(input);
			if(const auto node = parser.parse()) {
				this->visit(*node);
			}
		}	
}

void Nusai::Interpreter::input(const std::string& sumber, const std::string& input) {
  if(this->kParser.find(sumber) == this->kParser.end()) {
			auto& parser = this->kParser[sumber];
			parser = Nusap::Parser();
			parser.input(sumber, input);
			if(const auto node = parser.parse()) {
				this->visit(*node);
			}
	} 
}

void Nusai::Interpreter::inputFilePath(const std::string& filePath) {
  if(this->kParser.find(filePath) == this->kParser.end()) {
			auto& parser = this->kParser[filePath];
			parser = Nusap::Parser();
			parser.inputFilePath(filePath);
			if(const auto node = parser.parse()) {
				this->visit(*node);
			}
	}
}

std::any Nusai::Interpreter::visitToken(const Nusap::TokenCtx& ctx) {
	this->kToken.push_back(ctx.token);
    return ctx.token;
}

std::any Nusai::Interpreter::visitNilaiTeks(const Nusap::NilaiTeksCtx& ctx) {
		std::string teks;
		size_t index = 0;
		for(const auto& tokenCtx : ctx.kTokenCtx) {
			std::any tokenAny = this->visitToken(tokenCtx);
			if(index > 0 && index < (ctx.kTokenCtx.size() - 1)) {
				if(const auto* token = std::any_cast<Nusal::Token>(&tokenAny)) {
					teks += token->nilai;
				}
			}
			++index;
		}
    return teks;
}

std::any Nusai::Interpreter::visitMuatFile(const Nusap::MuatFileCtx& ctx) {
	this->visitToken(ctx.tokenMuatCtx);
	std::any nilaiTeksAny = this->visitNilaiTeks(ctx.nilaiTeksCtx);
	if(const auto* nilaiTeks = std::any_cast<std::string>(&nilaiTeksAny)) {
		this->inputFilePath(*nilaiTeks);
	}
  return {};
}

std::any Nusai::Interpreter::visitPernyataan(const Nusap::PernyataanCtx& ctx) {
	if(ctx.muatFileCtx.has_value()) {
		std::any hasil = this->visitMuatFile(ctx.muatFileCtx.value());
		if(ctx.tokenTitikKomaCtx.has_value()) {
			this->visitToken(ctx.tokenTitikKomaCtx.value());
		}else{
			throw Nusai::KesalahanInterpret(this->kToken, "Jangan lupa titik koma.");
		}
		return hasil;
	}
	throw Nusai::KesalahanInterpret(this->kToken, "Pernyataan tidak valid.");
}

std::any Nusai::Interpreter::visitNusantara(const Nusap::NusantaraCtx& ctx) {
		for(const auto& pernyataanCtx : ctx.kPernyataanCtx) {
			this->visitPernyataan(pernyataanCtx);
			this->kToken.clear();
		}
    return 0;
}

