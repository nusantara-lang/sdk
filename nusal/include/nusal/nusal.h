#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace nusal {

    enum class tipe_token {
        spasi,
        baris_baru,
        tab,
        angka,
        simbol,
        huruf,
        akhir,
        tidak_diketahui
    };

    std::string ubah_ke_string(const tipe_token& tipe_token);

    struct token {
        token() = default;
        token(
            const tipe_token& tipe,
            const std::string& nama,
            const std::string& sumber,
            const size_t& baris,
            const size_t& karakter,
            const std::string& nilai
        );
        tipe_token tipe = tipe_token::tidak_diketahui;
        std::string nama = "tidak_diketahui";
        std::string sumber = "tidak diketahui";
        size_t baris = 0;
        size_t karakter = 0;
        std::string nilai = "";
    };

    std::string ubah_ke_string(const token& token);

    struct tipe_token_data {
        tipe_token_data(
            const tipe_token& tipe,
            const std::string& nama,
            const std::string& pola
        );
        tipe_token tipe;
        std::string nama;
        std::string pola;
    };

    std::unique_ptr<token> buat_token(
        std::string& input, 
        size_t& baris,
        size_t& karakter,
        const std::string& sumber,
        const std::vector<tipe_token_data>& datas,
        bool& akhir
    );

    static std::vector<tipe_token_data> nusa_data_tipe_token = {
        {
            tipe_token::spasi, 
            ubah_ke_string(tipe_token::spasi), 
            "[ ]"
        },
        {
            tipe_token::baris_baru, 
            ubah_ke_string(tipe_token::baris_baru), 
            "[\n]"
        },
        {
            tipe_token::tab, 
            ubah_ke_string(tipe_token::tab), 
            "[\t]"
        },
        {
            tipe_token::angka, 
            ubah_ke_string(tipe_token::angka), 
            "[0-9]"
        },
        {
            tipe_token::simbol, 
            ubah_ke_string(tipe_token::simbol), 
            R"([`~!@#$%^&*()-_=+\[\]{}\\|;:'",<.>/?])"
        },
        {
            tipe_token::huruf, 
            ubah_ke_string(tipe_token::huruf), 
            "[a-zA-Z]"
        }
    };

    class lexer {
        public:
            lexer() = default;
            void input(const std::string& input);
            void input(const std::string& sumber, const std::string& input);
            std::unique_ptr<token> ambil_token();
            static const std::string sumber_tidak_diketahui;
        private:
            size_t baris = 0;
            size_t karakter = 0;
            bool akhir;
            std::map<std::string, std::string> sumber_berserta_input = {};
    };
}