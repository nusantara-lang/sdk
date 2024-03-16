#include "nusal/nusal.h"
#include <iostream>
#include <string>

int main() {
    nusal::lexer lexer;
    lexer.input(
        "kode",
        "10+15=25;"
    );
    lexer.input(
        "kode2",
        "15-2=13;"
    );
    while(auto token = lexer.ambil_token()) {
        std::cout << nusal::ubah_ke_string(*token) << "\n";
    }
    return 0;
}