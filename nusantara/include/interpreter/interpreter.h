#pragma once

#include <any>
#include <functional>
#include <vector>

namespace Interpreter {
    
    class Interpreter {
        public:
            void interpret(const std::vector<std::function<std::any(Interpreter&)>>& intructions);
        private:
        protected:
    };

}