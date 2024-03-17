#pragma once

#include "nusal/tipe_token.h"
#include "nusal/tipe_token_data.h"
#include <vector>

namespace nusal { 

    static std::vector<tipe_token_data<tipe_token>> nusa_data_tipe_token = {
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
	 
}
