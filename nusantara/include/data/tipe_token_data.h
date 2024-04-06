#pragma once

#include "lexer/tipe_token.h"

#include <vector>
#define TP_KEMBALI_KE_AWAL_KARAKTER "[\r]"
#define TT_KEMBALI_KE_AWAL_KARAKTER "kembali ke awal karakter"

#define TP_BARIS_BARU "[\n]"
#define TT_BARIS_BARU "baris baru"

#define TP_TAB "[\t]"
#define TT_TAB "tab"

#define TP_SPASI "[ ]"
#define TT_SPASI "spasi"

#define TP_KOMENTAR_SATU_BARIS "//[^\n]*"
#define TT_KOMENTAR_SATU_BARIS "komentar satu baris"

#define TP_KOMENTAR_BANYAK_BARIS "/\\*[^/*]*\\*/"
#define TT_KOMENTAR_BANYAK_BARIS "komentar banyak baris"

#define TP_MUAT "muat"
#define TT_MUAT "muat"

#define TP_LUAR "luar"
#define TT_LUAR "luar"

#define TP_BILANGAN "bilangan"
#define TT_BILANGAN "bilangan"

#define TP_TEKS "teks"
#define TT_TEKS "teks"

#define TP_DINAMIS "dinamis"
#define TT_DINAMIS "dinamis"

#define TP_IDENTIFIKASI "[a-zA-Z_][a-zA-Z0-9_]*"
#define TT_IDENTIFIKASI "identifikasi"

#define TP_ANGKA "[0-9]"
#define TT_ANGKA "angka"

#define TP_TAMBAH "[+]"
#define TT_TAMBAH "tambah"

#define TP_TANDA_HUBUNG "-"
#define TT_TANDA_HUBUNG "tanda hubung"

#define TP_ASTERIS "[*]"
#define TT_ASTERIS "asteris"

#define TP_GARIS_MIRING "/"
#define TT_GARIS_MIRING "garis miring"

#define TP_GARIS_MIRING_TERBALIK "\\\\"
#define TT_GARIS_MIRING_TERBALIK "garis miring terbalik"

#define TP_PERSEN "[%]"
#define TT_PERSEN "persen"

#define TP_SAMA_DENGAN "="
#define TT_SAMA_DENGAN "sama dengan"

#define TP_SERU "!"
#define TT_SERU "seru"

#define TP_DOLAR "[$]"
#define TT_DOLAR "dolar"

#define TP_GARIS_BAWAH "_"
#define TT_GARIS_BAWAH "garis bawah"

#define TP_KOMA ","
#define TT_KOMA "koma"

#define TP_TITIK "\\."
#define TT_TITIK "titik"

#define TP_TITIK_DUA ":"
#define TT_TITIK_DUA "titik dua"

#define TP_TITIK_KOMA ";"
#define TT_TITIK_KOMA "titik koma"

#define TP_KUTIP_SATU "'"
#define TT_KUTIP_SATU "kutip satu"

#define TP_GARIS_VERTIKAL R"(\|)"
#define TT_GARIS_VERTIKAL "garis vertikal"

#define TP_KURUNG_BUKA R"(\()"
#define TT_KURUNG_BUKA "kurung buka"

#define TP_KURUNG_TUTUP R"(\))"
#define TT_KURUNG_TUTUP "kurung tutup"

#define TP_KURUNG_SIKU_BUKA R"(\[)"
#define TT_KURUNG_SIKU_BUKA "kurung siku buka"

#define TP_KURUNG_SIKU_TUTUP R"(\])"
#define TT_KURUNG_SIKU_TUTUP "kurung siku tutup"

#define TP_KURUNG_KURAWAL_BUKA R"(\{)"
#define TT_KURUNG_KURAWAL_BUKA "kurung kurawal buka"

#define TP_KURUNG_KURAWAL_TUTUP R"(\})"
#define TT_KURUNG_KURAWAL_TUTUP "kurung kurawal tutup"

#define TP_KARAKTER "."
#define TT_KARAKTER "karakter"

#define TP_AKHIR_DARI_FILE "\\0"
#define TT_AKHIR_DARI_FILE "akhir dari file"

#define TP_TIDAK_DIKETAHUI ""
#define TT_TIDAK_DIKETAHUI "tidak diketahui"

inline std::vector<Lexer::TipeToken> tipeTokensData() {
  return {
      {Lexer::TipeToken::Nama(TT_KEMBALI_KE_AWAL_KARAKTER),
       Lexer::TipeToken::Pola(TP_KEMBALI_KE_AWAL_KARAKTER),                                      true },
      {Lexer::TipeToken::Nama(TT_BARIS_BARU),
       Lexer::TipeToken::Pola(TP_BARIS_BARU),                                                    true },
      {Lexer::TipeToken::Nama(TT_TAB),                      Lexer::TipeToken::Pola(TP_TAB),      true },
      {Lexer::TipeToken::Nama(TT_SPASI),                    Lexer::TipeToken::Pola(TP_SPASI),    true
      },
      {Lexer::TipeToken::Nama(TT_KOMENTAR_SATU_BARIS),
       Lexer::TipeToken::Pola(TP_KOMENTAR_SATU_BARIS),                                           true },
      {Lexer::TipeToken::Nama(TT_KOMENTAR_BANYAK_BARIS),
       Lexer::TipeToken::Pola(TP_KOMENTAR_BANYAK_BARIS),                                         true },
      {Lexer::TipeToken::Nama(TT_MUAT),                     Lexer::TipeToken::Pola(TP_MUAT),     false},
      {Lexer::TipeToken::Nama(TT_LUAR),                     Lexer::TipeToken::Pola(TP_LUAR),     false},
      {Lexer::TipeToken::Nama(TT_BILANGAN),                 Lexer::TipeToken::Pola(TP_BILANGAN),
       false                                                                                          },
      {Lexer::TipeToken::Nama(TT_TEKS),                     Lexer::TipeToken::Pola(TP_TEKS),     false},
      {Lexer::TipeToken::Nama(TT_DINAMIS),                  Lexer::TipeToken::Pola(TP_DINAMIS),
       false                                                                                          },
      {Lexer::TipeToken::Nama(TT_IDENTIFIKASI),
       Lexer::TipeToken::Pola(TP_IDENTIFIKASI),                                                  false},
      {Lexer::TipeToken::Nama(TT_ANGKA),                    Lexer::TipeToken::Pola(TP_ANGKA),    false
      },
      {Lexer::TipeToken::Nama(TT_TAMBAH),                   Lexer::TipeToken::Pola(TP_TAMBAH),
       false                                                                                          },
      {Lexer::TipeToken::Nama(TT_TANDA_HUBUNG),
       Lexer::TipeToken::Pola(TP_TANDA_HUBUNG),                                                  false},
      {Lexer::TipeToken::Nama(TT_ASTERIS),                  Lexer::TipeToken::Pola(TP_ASTERIS),
       false                                                                                          },
      {Lexer::TipeToken::Nama(TT_GARIS_MIRING),
       Lexer::TipeToken::Pola(TP_GARIS_MIRING),                                                  false},
      {Lexer::TipeToken::Nama(TT_GARIS_MIRING_TERBALIK),
       Lexer::TipeToken::Pola(TP_GARIS_MIRING_TERBALIK),                                         false},
      {Lexer::TipeToken::Nama(TT_PERSEN),                   Lexer::TipeToken::Pola(TP_PERSEN),
       false                                                                                          },
      {Lexer::TipeToken::Nama(TT_SAMA_DENGAN),
       Lexer::TipeToken::Pola(TP_SAMA_DENGAN),                                                   false},
      {Lexer::TipeToken::Nama(TT_SERU),                     Lexer::TipeToken::Pola(TP_SERU),     false},
      {Lexer::TipeToken::Nama(TT_DOLAR),                    Lexer::TipeToken::Pola(TP_DOLAR),    false
      },
      {Lexer::TipeToken::Nama(TT_GARIS_BAWAH),
       Lexer::TipeToken::Pola(TP_GARIS_BAWAH),                                                   false},
      {Lexer::TipeToken::Nama(TT_KOMA),                     Lexer::TipeToken::Pola(TP_KOMA),     false},
      {Lexer::TipeToken::Nama(TT_TITIK),                    Lexer::TipeToken::Pola(TP_TITIK),    false
      },
      {Lexer::TipeToken::Nama(TT_TITIK_DUA),
       Lexer::TipeToken::Pola(TP_TITIK_DUA),                                                     false},
      {Lexer::TipeToken::Nama(TT_TITIK_KOMA),
       Lexer::TipeToken::Pola(TP_TITIK_KOMA),                                                    false},
      {Lexer::TipeToken::Nama(TT_KUTIP_SATU),
       Lexer::TipeToken::Pola(TP_KUTIP_SATU),                                                    false},
      {Lexer::TipeToken::Nama(TT_GARIS_VERTIKAL),
       Lexer::TipeToken::Pola(TP_GARIS_VERTIKAL),                                                false},
      {Lexer::TipeToken::Nama(TT_KURUNG_BUKA),
       Lexer::TipeToken::Pola(TP_KURUNG_BUKA),                                                   false},
      {Lexer::TipeToken::Nama(TT_KURUNG_TUTUP),
       Lexer::TipeToken::Pola(TP_KURUNG_TUTUP),                                                  false},
      {Lexer::TipeToken::Nama(TT_KURUNG_SIKU_BUKA),
       Lexer::TipeToken::Pola(TP_KURUNG_SIKU_BUKA),                                              false},
      {Lexer::TipeToken::Nama(TT_KURUNG_SIKU_TUTUP),
       Lexer::TipeToken::Pola(TP_KURUNG_SIKU_TUTUP),                                             false},
      {Lexer::TipeToken::Nama(TT_KURUNG_KURAWAL_BUKA),
       Lexer::TipeToken::Pola(TP_KURUNG_KURAWAL_BUKA),                                           false},
      {Lexer::TipeToken::Nama(TT_KURUNG_KURAWAL_TUTUP),
       Lexer::TipeToken::Pola(TP_KURUNG_KURAWAL_TUTUP),                                          false},
      {Lexer::TipeToken::Nama(TT_KARAKTER),                 Lexer::TipeToken::Pola(TP_KARAKTER),
       false                                                                                          },
      {Lexer::TipeToken::Nama(TT_AKHIR_DARI_FILE),
       Lexer::TipeToken::Pola(TP_AKHIR_DARI_FILE),                                               false},
      {Lexer::TipeToken::Nama(TT_TIDAK_DIKETAHUI),
       Lexer::TipeToken::Pola(TP_TIDAK_DIKETAHUI),                                               false}
  };
}
