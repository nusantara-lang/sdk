#include "lexer/lexer.h"
#include "lexer/tipe_token.h"
#include "lexer/token.h"
#include "lexer/token_stream.h"
#include "parser/parse_rule.h"
#include "parser/parse_tree.h"
#include "parser/parser.h"

#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <span>
#include <vector>

#define SPASI_PUTIH "spasi putih"
#define ANGKA "angka"
#define HURUF "huruf"
#define SIMBOL "simbol"
#define AKHIR_DARI_FILE "akhir dari file"
#define TIDAK_DIKETAHUI "tidak diketahui"

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
        {Lexer::TipeToken::Nama(SPASI_PUTIH),
         Lexer::TipeToken::Pola("[ \n\t\r\f]+"),                                      true },
        {Lexer::TipeToken::Nama(ANGKA),           Lexer::TipeToken::Pola("[0-9]+"),   false
        },
        {Lexer::TipeToken::Nama(HURUF),           Lexer::TipeToken::Pola("[a-zA-Z]"),
         false                                                                             },
        {Lexer::TipeToken::Nama(SIMBOL),
         Lexer::TipeToken::Pola(R"([`!@#$%^&\*()_+-={}|\[\]\\:";'<>?,\./'])"),
         false                                                                             },
        {Lexer::TipeToken::Nama(AKHIR_DARI_FILE), Lexer::TipeToken::Pola("\\0"),
         false                                                                             },
        {Lexer::TipeToken::Nama(TIDAK_DIKETAHUI), Lexer::TipeToken::Pola(""),
         false                                                                             }
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
      std::vector<Parser::ParseRule> rules({Parser::ParseRule(
          "nusantara",
          [](Parser::Parser& parser, Parser::ParseRuleTree& rule) {
            while(!parser.getTokenStream().tokenSaatIniAdalah(AKHIR_DARI_FILE)
            ) {
              rule.addChild(std::make_unique<Parser::ParseTokenTree>(
                  parser.getTokenStream().tokenSelanjutNya(true)
              ));
            }
          }
      )});
      Parser::Parser parser(tokenStream, rules);
      std::unique_ptr<Parser::ParseTree> tree(parser.parse());
      std::cout << tree->ubahKeString();
    }
  } catch(const std::exception& error) { std::cout << error.what() << "\n"; }
  return 0;
}
