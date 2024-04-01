#include "data/parser_rule_data.h"
#include "data/tipe_token_data.h"
#include "lexer/lexer.h"
#include "lexer/tipe_token.h"
#include "lexer/token.h"
#include "lexer/token_stream.h"
#include "parser/parse_tree.h"
#include "parser/parser.h"

#include <cstring>
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <span>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
  auto args = std::span(argv, size_t(argc));
  try {
    if(!(argc > 1)) {
      std::cout << "Nusantara Interpreter"
                << "\n\n";
      std::cout << "Penggunaan: interpreter <nusa-file>*"
                << "\n";
      return 0;
    }
    std::vector<Lexer::TipeToken> tipeTokens({
        {Lexer::TipeToken::Nama(TT_KEMBALI_KE_AWAL_KARAKTER),
         Lexer::TipeToken::Pola(TP_KEMBALI_KE_AWAL_KARAKTER),                                     true },
        {Lexer::TipeToken::Nama(TT_BARIS_BARU),
         Lexer::TipeToken::Pola(TP_BARIS_BARU),                                                   true },
        {Lexer::TipeToken::Nama(TT_TAB),                      Lexer::TipeToken::Pola(TP_TAB),     true },
        {Lexer::TipeToken::Nama(TT_SPASI),                    Lexer::TipeToken::Pola(TP_SPASI),
         true                                                                                          },
        {Lexer::TipeToken::Nama(TT_KOMENTAR_SATU_BARIS),
         Lexer::TipeToken::Pola(TP_KOMENTAR_SATU_BARIS),                                          true },
        {Lexer::TipeToken::Nama(TT_KOMENTAR_BANYAK_BARIS),
         Lexer::TipeToken::Pola(TP_KOMENTAR_BANYAK_BARIS),                                        true },
        {Lexer::TipeToken::Nama(TT_MUAT),                     Lexer::TipeToken::Pola(TP_MUAT),    false
        },
        {Lexer::TipeToken::Nama(TT_LUAR),                     Lexer::TipeToken::Pola(TP_LUAR),    false
        },
        {Lexer::TipeToken::Nama(TT_BILANGAN),
         Lexer::TipeToken::Pola(TP_BILANGAN),                                                     false},
        {Lexer::TipeToken::Nama(TT_TEKS),                     Lexer::TipeToken::Pola(TP_TEKS),    false
        },
        {Lexer::TipeToken::Nama(TT_DINAMIS),                  Lexer::TipeToken::Pola(TP_DINAMIS),
         false                                                                                         },
        {Lexer::TipeToken::Nama(TT_IDENTIFIKASI),
         Lexer::TipeToken::Pola(TP_IDENTIFIKASI),                                                 false},
        {Lexer::TipeToken::Nama(TT_ANGKA),                    Lexer::TipeToken::Pola(TP_ANGKA),
         false                                                                                         },
        {Lexer::TipeToken::Nama(TT_TAMBAH),                   Lexer::TipeToken::Pola(TP_TAMBAH),
         false                                                                                         },
        {Lexer::TipeToken::Nama(TT_TANDA_HUBUNG),
         Lexer::TipeToken::Pola(TP_TANDA_HUBUNG),                                                 false},
        {Lexer::TipeToken::Nama(TT_ASTERIS),                  Lexer::TipeToken::Pola(TP_ASTERIS),
         false                                                                                         },
        {Lexer::TipeToken::Nama(TT_GARIS_MIRING),
         Lexer::TipeToken::Pola(TP_GARIS_MIRING),                                                 false},
        {Lexer::TipeToken::Nama(TT_PERSEN),                   Lexer::TipeToken::Pola(TP_PERSEN),
         false                                                                                         },
        {Lexer::TipeToken::Nama(TT_SAMA_DENGAN),
         Lexer::TipeToken::Pola(TP_SAMA_DENGAN),                                                  false},
        {Lexer::TipeToken::Nama(TT_SERU),                     Lexer::TipeToken::Pola(TP_SERU),    false
        },
        {Lexer::TipeToken::Nama(TT_DOLAR),                    Lexer::TipeToken::Pola(TP_DOLAR),
         false                                                                                         },
        {Lexer::TipeToken::Nama(TT_GARIS_BAWAH),
         Lexer::TipeToken::Pola(TP_GARIS_BAWAH),                                                  false},
        {Lexer::TipeToken::Nama(TT_KOMA),                     Lexer::TipeToken::Pola(TP_KOMA),    false
        },
        {Lexer::TipeToken::Nama(TT_TITIK),                    Lexer::TipeToken::Pola(TP_TITIK),
         false                                                                                         },
        {Lexer::TipeToken::Nama(TT_TITIK_DUA),
         Lexer::TipeToken::Pola(TP_TITIK_DUA),                                                    false},
        {Lexer::TipeToken::Nama(TT_TITIK_KOMA),
         Lexer::TipeToken::Pola(TP_TITIK_KOMA),                                                   false},
        {Lexer::TipeToken::Nama(TT_KUTIP_SATU),
         Lexer::TipeToken::Pola(TP_KUTIP_SATU),                                                   false},
        {Lexer::TipeToken::Nama(TT_GARIS_VERTIKAL),
         Lexer::TipeToken::Pola(TP_GARIS_VERTIKAL),                                               false},
        {Lexer::TipeToken::Nama(TT_KURUNG_BUKA),
         Lexer::TipeToken::Pola(TP_KURUNG_BUKA),                                                  false},
        {Lexer::TipeToken::Nama(TT_KURUNG_TUTUP),
         Lexer::TipeToken::Pola(TP_KURUNG_TUTUP),                                                 false},
        {Lexer::TipeToken::Nama(TT_KURUNG_SIKU_BUKA),
         Lexer::TipeToken::Pola(TP_KURUNG_SIKU_BUKA),                                             false},
        {Lexer::TipeToken::Nama(TT_KURUNG_SIKU_TUTUP),
         Lexer::TipeToken::Pola(TP_KURUNG_SIKU_TUTUP),                                            false},
        {Lexer::TipeToken::Nama(TT_KURUNG_KURAWAL_BUKA),
         Lexer::TipeToken::Pola(TP_KURUNG_KURAWAL_BUKA),                                          false},
        {Lexer::TipeToken::Nama(TT_KURUNG_KURAWAL_TUTUP),
         Lexer::TipeToken::Pola(TP_KURUNG_KURAWAL_TUTUP),                                         false},
        {Lexer::TipeToken::Nama(TT_KARAKTER),
         Lexer::TipeToken::Pola(TP_KARAKTER),                                                     false},
        {Lexer::TipeToken::Nama(TT_AKHIR_DARI_FILE),
         Lexer::TipeToken::Pola(TP_AKHIR_DARI_FILE),                                              false},
        {Lexer::TipeToken::Nama(TT_TIDAK_DIKETAHUI),
         Lexer::TipeToken::Pola(TP_TIDAK_DIKETAHUI),                                              false}
    });
    Lexer::Lexer lexer(
        tipeTokens, tipeTokens.size() - 1, tipeTokens.size() - 2
    );
    if(argc > 1) {
      for(size_t index = 1; index < static_cast<size_t>(argc); ++index) {
        lexer.inputFilePath(args[index]);
      }
      Lexer::TokenStream tokenStream(lexer);
      Lexer::Token token;
      std::map<
          std::string,
          std::function<void(Parser::Parser&, Parser::ParseRuleTree&)>>
          rules({
              {PR_NUSANTARA,
               [](Parser::Parser& parser, Parser::ParseRuleTree& rule) {
                 while(!parser.getTokenStream().tokenSaatIniAdalah(
                     TT_AKHIR_DARI_FILE
                 )) {
                   rule.addChild(std::make_unique<Parser::ParseTokenTree>(
                       parser.getTokenStream().tokenSelanjutNya(true)
                   ));
                 }
               }}
      });
      Parser::Parser parser(tokenStream, rules);
      std::unique_ptr<Parser::ParseTree> tree(parser.parse(PR_NUSANTARA));
      std::cout << tree->ubahKeString();
    }
  } catch(const std::exception& error) { std::cout << error.what() << "\n"; }
  return 0;
}
