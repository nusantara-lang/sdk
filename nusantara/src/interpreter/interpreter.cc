#include "interpreter/interpreter.h"
#include "semantics/instruction.h"
#include <iostream>

void Interpreter::Interpreter::interpret(const std::vector<Semantics::Intruction>& intructions) {
    for(const auto& intruction : intructions) {
        std::cout << intruction.getName() << "\n";
        intruction.getExecute()(*this);
    }
}