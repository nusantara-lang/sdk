#include "nusal/lexer.h"
#include <exception>
#include <iostream>

int main(int argv, char* args[]) {
  try {
		if(!(argv > 1)) {
			std::cout << "Nusantara Lexer" << "\n\n";
			std::cout << "Penggunaan: nusal <nusantara-file>*" << "\n";
			return 0;
		}
   	nusal::lexer lexer;
		for(int index = 1; index < argv; ++index) {
			lexer.input_filepath(args[index]);
		} 
    while(auto token = lexer.ambil_token()) {
        std::cout << nusal::ubah_ke_string(*token) << "\n";
    }
	} catch(const std::exception& error) {
		 std::cout << error.what() << "\n";
  } 
  return 0;
}
