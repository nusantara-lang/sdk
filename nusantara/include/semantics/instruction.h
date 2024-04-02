#pragma once

#include <any>
#include <functional>
#include <string>

namespace Interpreter {
    class Interpreter;
}

namespace Semantics {

    class Intruction {
        public:
            Intruction(std::string name, const std::function<std::any(Interpreter::Interpreter&)>& execute);
            [[nodiscard]] const std::string& getName() const;
            [[nodiscard]] const std::function<std::any(Interpreter::Interpreter&)>& getExecute() const;
        private:
            std::string name;
            std::function<std::any(Interpreter::Interpreter&)> execute;
        protected:
    };

}