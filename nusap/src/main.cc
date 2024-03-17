#include "nusap/node.h"
#include "nusap/parser.h"

#include <exception>
#include <iostream>
#include <memory>
#include <span>

int main(int argc, char* argv[]) {
  auto args = std::span(argv, size_t(argc));
  try {
    if(!(argc > 1)) {
      std::cout << "Nusantara Parser"
                << "\n\n";
      std::cout << "Penggunaan: nusap <nusa-file>*"
                << "\n";
      return 0;
    }
    nusap::parser parser;
    for(int index = 1; index < argc; ++index) {
      parser.input_filepath(args[index]);
    }
    std::unique_ptr<nusap::node> root = parser.parse();
    nusap::cetak_node(root);
  } catch(const std::exception& error) { std::cout << error.what() << "\n"; }
  return 0;
}
