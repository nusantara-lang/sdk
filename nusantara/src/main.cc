#include "nusai/interpreter.h"
#include "nusal/lexer.h"
#include "nusal/nusal.h"
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
	    nusai::interpreter interpreter;
  	  interpreter.input_filepath(args[1]);
		}else if(argc == 3) {
			if(std::strcmp(args[1], "-l") == 0) {
				nusal::lexer lexer(nusal::nusal_data_tipe_token());
				lexer.input_filepath(args[2]);
				while (auto token = lexer.ambil_token()) {
					std::cout << nusal::ubah_ke_string(*token) << "\n";
				}
			} else if(std::strcmp(args[1], "-p") == 0) {
				nusap::parser parser;
				parser.input_filepath(args[2]);
				auto root = parser.parse();
				nusap::cetak_node(root);
			}
		}
  } catch(const std::exception& error) { std::cout << error.what() << "\n"; }
  return 0;
}
