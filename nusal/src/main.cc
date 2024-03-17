#include "nusal/lexer.h"
#include "nusal/nusal.h"
#include "nusal/tipe_token.h"

#include <exception>
#include <format>
#include <iostream>
#include <span>
#include <stdexcept>

int main(int argc, char* argv[]) {
  auto args = std::span(argv, size_t(argc));
  try {
    if(!(argc > 1)) {
      std::cout << "Nusantara Lexer"
                << "\n\n";
      std::cout << "Penggunaan: nusal <nusa-file>*"
                << "\n";
      return 0;
    }
    nusal::lexer lexer(nusal::nusal_data_tipe_token());
    for(int index = 1; index < argc; ++index) {
      lexer.input_filepath(args[index]);
    }
    while(auto token = lexer.ambil_token()) {
      if(token->tipe == nusal::tipe_token::TIDAK_DIKETAHUI) {
        throw std::runtime_error(std::format(
            "Nusantara tidak dapat mengenali karakter '{}'.", token->nilai
        ));
      }
      std::cout << nusal::ubah_ke_string(*token) << "\n";
    }
  } catch(const std::exception& error) { std::cout << error.what() << "\n"; }
  return 0;
}
