#include "nusai/interpreter.h"
#include "nusal/tipe_token.h"
#include "nusap/visitor.h"
#include <any>
#include <format>
#include <stdexcept>
#include <string>
#include <vector>

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

std::any nusai::interpreter::visit_nusantara(const nusap::nusantara_ctx& ctx) {
    this->k_kawasan[kawasan_global] = kawasan();
    for(const auto& child : ctx.k_pernyataan_ctx) {
        this->visit_pernyataan(child);
    }
    return {};
}

std::any nusai::interpreter::visit_pernyataan(const nusap::pernyataan_ctx& ctx) {
    if(ctx.buat_fungsi_ctx.has_value()) {
        this->visit_buat_fungsi(ctx.buat_fungsi_ctx.value());
    }else if(ctx.buat_variable_ctx.has_value()) {
        this->visit_buat_variable(ctx.buat_variable_ctx.value());
    }
    return {};
}

std::any nusai::interpreter::visit_pernyataan_blok_kode(const nusap::pernyataan_blok_kode_ctx& ctx) {
    if(ctx.buat_fungsi_ctx.has_value()) {
        this->visit_buat_fungsi(ctx.buat_fungsi_ctx.value());
    }else if(ctx.buat_variable_ctx.has_value()) {
        this->visit_buat_variable(ctx.buat_variable_ctx.value());
    }else if(ctx.manggil_fungsi_ctx.has_value()) {
        this->visit_manggil_fungsi(ctx.manggil_fungsi_ctx.value());
    }
    return {};
}

std::any nusai::interpreter::visit_ekspresi(const nusap::ekspresi_ctx& ctx) {
    if(ctx.bilangan_ctx.has_value()) {
        return this->visit_bilangan(ctx.bilangan_ctx.value());
    }
    if(ctx.teks_ctx.has_value()) {
        return this->visit_teks(ctx.teks_ctx.value());
    }
    return {};
}

std::any nusai::interpreter::visit_blok_kode(const nusap::blok_kode_ctx& ctx) {
    for(const auto& child : ctx.k_pernyataan_blok_kode_ctx) {
        this->visit_pernyataan_blok_kode(child);
    }
    return {};
}

std::any nusai::interpreter::visit_teks(const nusap::teks_ctx& ctx) {
    std::string hasil;
    for(const auto& child : ctx.k_token) {
        hasil += child.nilai;
    }
    return hasil;
}

std::any nusai::interpreter::visit_bilangan(const nusap::bilangan_ctx& ctx) {
    std::string hasil_str;
    for(const auto& child : ctx.k_token) {
        hasil_str += child.nilai;
    }
    hasil_str.replace(hasil_str.find(','), 1, ".");
    if(hasil_str.find('.') != std::string::npos) {
        double hasil = std::stod(hasil_str);
        return hasil;
    }
    int hasil = std::stoi(hasil_str);
    return hasil;
}

std::any nusai::interpreter::visit_buat_variable(const nusap::buat_variable_ctx& ctx) {
    variable var;
    var.tipe = ctx.tipe;
    if(ctx.tipe == nusal::tipe_token::TEKS) {
        if(ctx.teks_ctx.has_value()) {
            var.nilai = this->visit_teks(ctx.teks_ctx.value());
        }
    }else if(ctx.tipe == nusal::tipe_token::BILANGAN) {
        if(ctx.bilangan_ctx.has_value()) {
            var.nilai = this->visit_bilangan(ctx.bilangan_ctx.value());
        }
    }else{
        var.nilai = {};
    }
    auto& variables = this->k_kawasan[this->kawasan_yang_digunakan].variables;
    if(variables.find(ctx.id) == variables.end()) {
        return variables[ctx.id] = var;
    }else{
        throw std::runtime_error(std::format("Variable {} sudah ada.", ctx.id));
    }
}

std::any nusai::interpreter::visit_buat_fungsi(const nusap::buat_fungsi_ctx& ctx) {
    auto& functions = this->k_kawasan[this->kawasan_yang_digunakan].functions;
    functions[ctx.id] = [this, ctx](std::vector<nusap::ekspresi_ctx> k_ekspresi_ctx) -> std::any {
        size_t index = 0;
        for(auto child : ctx.k_buat_variable) {
            auto& ekspresi_ctx = k_ekspresi_ctx[index];
            if(ekspresi_ctx.bilangan_ctx.has_value()) {
                child.bilangan_ctx = ekspresi_ctx.bilangan_ctx;
            }else if(ekspresi_ctx.teks_ctx.has_value()) {
                child.teks_ctx = ekspresi_ctx.teks_ctx;
            }
            this->visit_buat_variable(child);
            index++;
        }
        return this->visit_blok_kode(ctx.blok_kode_ctx);
    };
    return {};
}

std::any nusai::interpreter::visit_manggil_fungsi(const nusap::manggil_fungsi_ctx& ctx) {
    this->k_kawasan[ctx.id] = kawasan();
    auto& functions = this->k_kawasan[this->kawasan_yang_digunakan].functions;
    if(!functions.contains(ctx.id)) {
        throw std::runtime_error(std::format("Fungsi {} belum dibuat.", ctx.id));
    }
    this->kawasan_yang_digunakan = ctx.id;
    std::any hasil = functions[ctx.id](ctx.k_ekspresi_ctx);
    this->kawasan_yang_digunakan = this->kawasan_global;
    this->k_kawasan.erase(ctx.id);
    return hasil;
}
