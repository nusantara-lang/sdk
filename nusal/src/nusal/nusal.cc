#include "nusal/nusal.h"

#include "nusal/tipe_token_data.h"

const std::vector<nusal::tipe_token_data>& nusal::nusal_data_tipe_token() {
  static std::vector<tipe_token_data> output = {
      {tipe_token::KEMBALI_KE_AWAL_KARAKTER, "[\r]"                  },
      {tipe_token::BARIS_BARU,               "[\n]"                  },
      {tipe_token::TAB,                      "[\t]"                  },
      {tipe_token::SPASI,                    "[ ]"                   },
      {tipe_token::KATA_KUNCI,               "kata_kunci"            },
      {tipe_token::ALIAS,                    "alias"                 },
      {tipe_token::BILANGAN,                 "bilangan"              },
      {tipe_token::TEKS,                     "teks"                  },
      {tipe_token::IDENTIFIKASI,             "[a-zA-Z_][a-zA-Z0-9_]*"},
      {tipe_token::ANGKA,                    "[0-9]"                 },
      {tipe_token::TAMBAH,                   "[+]"                   },
      {tipe_token::TANDA_HUBUNG,             "-"                     },
      {tipe_token::ASTERIS,                  "[*]"                   },
      {tipe_token::GARIS_MIRING,             "/"                     },
      {tipe_token::PERSEN,                   "[%]"                   },
      {tipe_token::SAMA_DENGAN,              "="                     },
      {tipe_token::SERU,                     "!"                     },
      {tipe_token::DOLAR,                    "[$]"                   },
      {tipe_token::GARIS_BAWAH,              "_"                     },
      {tipe_token::KOMA,                     ","                     },
      {tipe_token::TITIK,                    "\\."                   },
      {tipe_token::TITIK_DUA,                ":"                     },
      {tipe_token::TITIK_KOMA,               ";"                     },
      {tipe_token::KUTIP_SATU,               "'"                     },
      {tipe_token::GARIS_VERTIKAL,           R"(\|)"                 },
      {tipe_token::KURUNG_BUKA,              R"(\()"                 },
      {tipe_token::KURUNG_TUTUP,             R"(\))"                 },
      {tipe_token::KURUNG_SIKU_BUKA,         R"(\[)"                 },
      {tipe_token::KURUNG_SIKU_TUTUP,        R"(\])"                 },
      {tipe_token::KURUNG_KURAWAL_BUKA,      R"(\{)"                 },
      {tipe_token::KURUNG_KURAWAL_TUTUP,     R"(\})"                 },
      {tipe_token::KARAKTER,                 "."                     },
  };
  return output;
}
