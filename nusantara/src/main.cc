#include "nusai/interpreter.h"
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
    nusai::interpreter interpreter;
    for(int index = 1; index < argc; ++index) {
      interpreter.input_filepath(args[index]);
    }
  } catch(const std::exception& error) { std::cout << error.what() << "\n"; }
  return 0;
}
