#pragma once

#include "parser/parse_tree.h"
#include "semantics/kesalahan_semantics.h"
#include "semantics/instruction.h"
#include <any>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Semantics {

    class Semantics {
        public:
            explicit Semantics(std::unique_ptr<Parser::ParseTree>& tree, const std::map<std::string, std::function<std::any(const Parser::ParseRuleTree&, Semantics&, std::vector<Intruction>&)>>& rules);
            std::vector<Intruction> analysis();
            std::vector<Lexer::Token>& getKToken();
            std::any analysis(const Parser::ParseRuleTree& ruleTree, const std::string& ruleName, std::vector<Intruction>& intructions);
            KesalahanSemantics kesalahan(const std::string& pesan);
        private:
            std::reference_wrapper<std::unique_ptr<Parser::ParseTree>> tree;
            std::map<std::string, std::function<std::any(const Parser::ParseRuleTree&, Semantics&, std::vector<Intruction>&)>> rules;
            std::vector<Lexer::Token> kToken;
        protected:
    };

}