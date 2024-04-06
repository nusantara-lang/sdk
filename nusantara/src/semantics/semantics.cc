#include "semantics/semantics.h"

#include "parser/parse_tree.h"
#include "semantics/kesalahan_semantics.h"

#include <any>
#include <string>
#include <vector>

Semantics::Semantics::Semantics(
    std::unique_ptr<Parser::ParseTree>& tree,
    const std::map<
        std::string,
        std::function<std::
                          any(const Parser::ParseRuleTree&, Semantics&,
                              std::vector<Intruction>&)>>& rules
):
    tree(tree),
    rules(rules) {}

std::vector<Semantics::Intruction> Semantics::Semantics::analysis() {
  std::vector<Intruction> result;
  if(const auto* root =
         dynamic_cast<Parser::ParseRuleTree*>(this->tree.get().get())) {
    this->analysisRule(*root, root->getRule(), result);
  }
  return result;
}

std::any Semantics::Semantics::analysisRule(
    const Parser::ParseRuleTree& ruleTree, const std::string& ruleName,
    std::vector<Intruction>& intructions
) {
  return this->rules[ruleName](ruleTree, *this, intructions);
}

Semantics::KesalahanSemantics
Semantics::Semantics::kesalahan(const std::string& pesan) {
  return {this->kToken, pesan};
}

void Semantics::Semantics::addToken(const Lexer::Token& token) {
  this->kToken.push_back(token);
}

void Semantics::Semantics::clearTokens() { this->kToken.clear(); }

bool Semantics::Semantics::addFileYangSudahDiMuat(const std::string& filePath) {
  if(this->fileSudahDiMuat(filePath)) { return false; }
  this->kFileYangSudahDiMuat.insert(filePath);
  return true;
}

bool Semantics::Semantics::fileSudahDiMuat(const std::string& filePath) {
  return this->kFileYangSudahDiMuat.contains(filePath);
}
