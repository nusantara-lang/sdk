#include "parser/parse_tree.h"

#include "lexer/token.h"

#include <memory>
#include <sstream>

Parser::ParseRuleTree::ParseRuleTree(ParseRuleTree&& other) noexcept:
    rule(std::move(other.rule)), children(std::move(other.children)) {}

Parser::ParseRuleTree::ParseRuleTree(const ParseRule& rule):
    rule(rule.getNama()) {}

void Parser::ParseRuleTree::addChild(std::unique_ptr<ParseTree>&& child) {
  this->children.push_back(std::move(child));
}

const std::string& Parser::ParseRuleTree::getRule() const { return this->rule; }

const std::vector<std::unique_ptr<Parser::ParseTree>>&
Parser::ParseRuleTree::getChildren() const {
  return this->children;
}

std::string Parser::ParseRuleTree::ubahKeString() const {
  return this->ubahKeString(0);
}

std::string Parser::ParseRuleTree::ubahKeString(const int& level) const {
  std::ostringstream stream;
  for(int i = 0; i < level; ++i) { stream << "  "; }
  stream << this->rule << "\n";
  for(const auto& child : this->children) {
    stream << child->ubahKeString(level + 1);
  }
  return stream.str();
}

Parser::ParseTokenTree::ParseTokenTree(const Lexer::Token& token):
    token(token) {}

const Lexer::Token& Parser::ParseTokenTree::getToken() const {
  return this->token;
}

std::string Parser::ParseTokenTree::ubahKeString() const {
  return this->ubahKeString(0);
}

std::string Parser::ParseTokenTree::ubahKeString(const int& level) const {
  std::ostringstream stream;
  for(int i = 0; i < level; ++i) { stream << "  "; }
  stream << this->token.getNilai() << "\n";
  return stream.str();
}
