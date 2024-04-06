#pragma once

#include "semantics/instruction.h"

#include <vector>

namespace Interpreter {

  class Interpreter {
    public:
      void interpret(const std::vector<Semantics::Intruction>& intructions);

    private:

    protected:
  };

} // namespace Interpreter
