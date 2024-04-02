#include "interpreter/interpreter.h"

void Interpreter::Interpreter::interpret(const std::vector<std::function<std::any(Interpreter&)>>& intructions) {
    for(const auto& intruction : intructions) {
        intruction(*this);
    }
}