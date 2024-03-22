#include "nusal/nusal.h"

#include "nusal/tipe_token_data.h"

const std::vector<Nusal::TipeTokenData>& Nusal::nusalDataTipeToken() {
  static std::vector<TipeTokenData> output = {
      {TipeToken::kembali_ke_awal_karakter, "[\r]"                  },
      {TipeToken::baris_baru,               "[\n]"                  },
      {TipeToken::tab,                      "[\t]"                  },
      {TipeToken::spasi,                    "[ ]"                   },
      {TipeToken::komentar_satu_baris,      "//[^\n]*"              },
      {TipeToken::komentar_banyak_baris,    "/\\*[^/*]*\\*/"        },
      {TipeToken::muat,                     "muat"                  },
      {TipeToken::luar,                     "luar"                  },
      {TipeToken::bilangan,                 "bilangan"              },
      {TipeToken::teks,                     "teks"                  },
      {TipeToken::dinamis,                  "dinamis"               },
      {TipeToken::identifikasi,             "[a-zA-Z_][a-zA-Z0-9_]*"},
      {TipeToken::angka,                    "[0-9]"                 },
      {TipeToken::tambah,                   "[+]"                   },
      {TipeToken::tanda_hubung,             "-"                     },
      {TipeToken::asteris,                  "[*]"                   },
      {TipeToken::garis_miring,             "/"                     },
      {TipeToken::persen,                   "[%]"                   },
      {TipeToken::sama_dengan,              "="                     },
      {TipeToken::seru,                     "!"                     },
      {TipeToken::dolar,                    "[$]"                   },
      {TipeToken::garis_bawah,              "_"                     },
      {TipeToken::koma,                     ","                     },
      {TipeToken::titik,                    "\\."                   },
      {TipeToken::titik_dua,                ":"                     },
      {TipeToken::titik_koma,               ";"                     },
      {TipeToken::kutip_satu,               "'"                     },
      {TipeToken::garis_vertikal,           R"(\|)"                 },
      {TipeToken::kurung_buka,              R"(\()"                 },
      {TipeToken::kurung_tutup,             R"(\))"                 },
      {TipeToken::kurung_siku_buka,         R"(\[)"                 },
      {TipeToken::kurung_siku_tutup,        R"(\])"                 },
      {TipeToken::kurung_kurawal_buka,      R"(\{)"                 },
      {TipeToken::kurung_kurawal_tutup,     R"(\})"                 },
      {TipeToken::garis_miring_terbalik,    R"(\\)"                 },
      {TipeToken::karakter,                 "."                     },
  };
  return output;
}
