#pragma once

#include "nusal/token.h"
#include "nusap/node.h"
#include <nusal/lexer.h>
#include <nusap/parser.h>
#include <vector>

namespace nusai {

    class interpreter {
        public:
            interpreter();
            void input(const std::string& input);
            void input(const std::string& sumber, const std::string& input);
            void input_filepath(const std::string& file_path);
        private:
            nusap::parser parser;
            std::vector<nusal::token> tokens;
            void interpret();
            void interpret(const nusap::node& root);
    };

}