#include "semantics/semantics.h"
#include "parser/parse_tree.h"
#include "semantics/kesalahan_semantics.h"
#include <any>
#include <string>
#include <vector>

Semantics::Semantics::Semantics(std::unique_ptr<Parser::ParseTree>& tree, const std::map<std::string, std::function<std::any(const Parser::ParseRuleTree&, Semantics&, std::vector<std::function<std::any(Interpreter::Interpreter&)>>&)>>& rules): tree(tree), rules(rules) {}

std::vector<std::function<std::any(Interpreter::Interpreter&)>> Semantics::Semantics::analysis() {
    std::vector<std::function<std::any(Interpreter::Interpreter&)>> result;
    if(const auto* root = dynamic_cast<Parser::ParseRuleTree*>(this->tree.get().get())) {
        this->analysis(*root, root->getRule(), result);
    }
    return result;
}

std::vector<Lexer::Token>& Semantics::Semantics::getKToken() {
    return this->kToken;
}

std::any Semantics::Semantics::analysis(const Parser::ParseRuleTree& ruleTree, const std::string& ruleName, std::vector<std::function<std::any(Interpreter::Interpreter&)>>& intructions) {
    return this->rules[ruleName](ruleTree, *this, intructions);
}

Semantics::KesalahanSemantics Semantics::Semantics::kesalahan(const std::string& pesan) {
    return {this->kToken, pesan};
}