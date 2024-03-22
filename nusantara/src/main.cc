#include "nusad/nusad.h"
#include "nusai/interpreter.h"
#include "nusal/lexer.h"
#include "nusal/nusal.h"
#include "nusal/tipe_token.h"
#include "nusal/token.h"
#include "nusap/node.h"
#include "nusap/parser.h"

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
        Nusal::Lexer lexer(Nusal::nusalDataTipeToken());
        for(size_t index = 2; index < static_cast<size_t>(argc); ++index) {
          lexer.inputFilePath(args[index]);
        }
        Nusal::Token token;
        while(true) {
          if(token.tipe == Nusal::TipeToken::akhir_dari_file) { break; }
          token = lexer.ambilToken();
          std::cout << Nusal::ubahKeString(token) << "\n";
        }
      } else if(std::strcmp(args[1], "-p") == 0) {
        Nusap::Parser parser;
        for(size_t index = 2; index < static_cast<size_t>(argc); ++index) {
          parser.inputFilePath(args[index]);
        }
        auto root = parser.parse();
        Nusap::cetakNode(root);
      }
    }
  } catch(const std::exception& error) { std::cout << error.what() << "\n"; }
  return 0;
}
