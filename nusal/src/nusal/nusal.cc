#include "nusal/nusal.h"

#include "nusal/tipe_token_data.h"

const std::vector<nusal::tipe_token_data>& nusal::nusal_data_tipe_token() {
  static std::vector<tipe_token_data> output = {
      {tipe_token::KEMBALI_KE_AWAL_KARAKTER,
       ubah_ke_string(tipe_token::KEMBALI_KE_AWAL_KARAKTER),                             "[\r]"    },
      {tipe_token::BARIS_BARU,               ubah_ke_string(tipe_token::BARIS_BARU),     "[\n]"    },
      {tipe_token::TAB,                      ubah_ke_string(tipe_token::TAB),            "[\t]"    },
      {tipe_token::SPASI,                    ubah_ke_string(tipe_token::SPASI),          "[ ]"     },
      {tipe_token::KATA_KUNCI,               ubah_ke_string(tipe_token::KATA_KUNCI),
       "kata_kunci"                                                                                },
      {tipe_token::ALIAS,                    ubah_ke_string(tipe_token::ALIAS),          "alias"   },
      {tipe_token::BILANGAN,                 ubah_ke_string(tipe_token::BILANGAN),       "bilangan"},
      {tipe_token::TEKS,                     ubah_ke_string(tipe_token::TEKS),           "teks"    },
      {tipe_token::HURUF,                    ubah_ke_string(tipe_token::HURUF),          "[a-zA-Z]"},
      {tipe_token::ANGKA,                    ubah_ke_string(tipe_token::ANGKA),          "[0-9]"   },
      {tipe_token::TAMBAH,                   ubah_ke_string(tipe_token::TAMBAH),         "[+]"     },
      {tipe_token::TANDA_HUBUNG,             ubah_ke_string(tipe_token::TANDA_HUBUNG),   "-"       },
      {tipe_token::ASTERIS,                  ubah_ke_string(tipe_token::ASTERIS),        "[*]"     },
      {tipe_token::GARIS_MIRING,             ubah_ke_string(tipe_token::GARIS_MIRING),   "/"       },
      {tipe_token::PERSEN,                   ubah_ke_string(tipe_token::PERSEN),         "[%]"     },
      {tipe_token::SAMA_DENGAN,              ubah_ke_string(tipe_token::SAMA_DENGAN),    "="       },
      {tipe_token::SERU,                     ubah_ke_string(tipe_token::SERU),           "!"       },
      {tipe_token::DOLAR,                    ubah_ke_string(tipe_token::DOLAR),          "[$]"     },
      {tipe_token::GARIS_BAWAH,              ubah_ke_string(tipe_token::GARIS_BAWAH),    "_"       },
      {tipe_token::KOMA,                     ubah_ke_string(tipe_token::KOMA),           ","       },
      {tipe_token::TITIK,                    ubah_ke_string(tipe_token::TITIK),          "\\."     },
      {tipe_token::TITIK_DUA,                ubah_ke_string(tipe_token::TITIK_DUA),      ":"       },
      {tipe_token::TITIK_KOMA,               ubah_ke_string(tipe_token::TITIK_KOMA),     ";"       },
      {tipe_token::KUTIP_SATU,               ubah_ke_string(tipe_token::KUTIP_SATU),     "'"       },
      {tipe_token::GARIS_VERTIKAL,           ubah_ke_string(tipe_token::GARIS_VERTIKAL),
       R"(\|)"                                                                                     },
      {tipe_token::KURUNG_BUKA,              ubah_ke_string(tipe_token::KURUNG_BUKA),    R"(\()"
      },
      {tipe_token::KURUNG_TUTUP,             ubah_ke_string(tipe_token::KURUNG_TUTUP),
       R"(\))"                                                                                     },
      {tipe_token::KURUNG_SIKU_BUKA,
       ubah_ke_string(tipe_token::KURUNG_SIKU_BUKA),                                     R"(\[)"   },
      {tipe_token::KURUNG_SIKU_TUTUP,
       ubah_ke_string(tipe_token::KURUNG_SIKU_TUTUP),                                    R"(\])"   },
      {tipe_token::KURUNG_KURAWAL_BUKA,
       ubah_ke_string(tipe_token::KURUNG_KURAWAL_BUKA),                                  R"(\{)"   },
      {tipe_token::KURUNG_KURAWAL_TUTUP,
       ubah_ke_string(tipe_token::KURUNG_KURAWAL_TUTUP),                                 R"(\})"   },
  };
  return output;
}
