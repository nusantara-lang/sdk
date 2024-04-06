#include "semantics/instruction.h"

Semantics::Intruction::Intruction(
    std::string name,
    const std::function<std::any(Interpreter::Interpreter&)>& execute
):
    name(std::move(name)),
    execute(execute) {}

const std::string& Semantics::Intruction::getName() const { return this->name; }

const std::function<std::any(Interpreter::Interpreter&)>&
Semantics::Intruction::getExecute() const {
  return this->execute;
}
