#include "nusal/lexer.h"
#include "nusal/nusal.h"

#include <exception>
#include <iostream>
#include <span>

int main(int argc, char* argv[]) {
  auto args = std::span(argv, size_t(argc));
  try {
    if(!(argc > 1)) {
      std::cout << "Nusantara Lexer"
                << "\n\n";
      std::cout << "Penggunaan: nusal <nusantara-file>*"
                << "\n";
      return 0;
    }
    nusal::lexer lexer(nusal::nusa_data_tipe_token());
    for(int index = 1; index < argc; ++index) {
      lexer.input_filepath(args[index]);
    }
    while(auto token = lexer.ambil_token()) {
      std::cout << nusal::ubah_ke_string(*token) << "\n";
    }
  } catch(const std::exception& error) { std::cout << error.what() << "\n"; }
  return 0;
}
