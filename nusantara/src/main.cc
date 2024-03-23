#include "nusai/interpreter.h"
#include "lexer/lexer.h"
#include "lexer/tipe_token.h"
#include "lexer/token.h"
#include "parser/node.h"
#include "parser/parser.h"

#include <cstring>
#include <exception>
#include <iostream>
#include <span>

int main(int argc, char* argv[]) {
  auto args = std::span(argv, size_t(argc));
  try {
    if(!(argc > 1)) {
      std::cout << "Nusantara Interpreter"
                << "\n\n";
      std::cout << "Penggunaan: nusai <nusa-file>*"
                << "\n";
      return 0;
    }
    if(argc == 2) {
      Nusai::Interpreter interpreter;
      interpreter.inputFilePath(args[1]);
    } else if(argc >= 3) {
      if(std::strcmp(args[1], "-l") == 0) {
        Lexer::Lexer lexer(Lexer::nusantaraDataTipeToken());
        for(size_t index = 2; index < static_cast<size_t>(argc); ++index) {
          lexer.inputFilePath(args[index]);
        }
        Lexer::Token token;
        while(true) {
          if(token.tipe == Lexer::TipeToken::akhir_dari_file) { break; }
          token = lexer.ambilToken();
          std::cout << Lexer::ubahKeString(token) << "\n";
        }
      } else if(std::strcmp(args[1], "-p") == 0) {
        Parser::Parser parser;
        for(size_t index = 2; index < static_cast<size_t>(argc); ++index) {
          parser.inputFilePath(args[index]);
        }
        auto root = parser.parse();
        Parser::cetakNode(root);
      }
    }
  } catch(const std::exception& error) { std::cout << error.what() << "\n"; }
  return 0;
}
