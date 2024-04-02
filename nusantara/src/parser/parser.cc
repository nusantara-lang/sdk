#include "parser/parser.h"

#include "parser/parse_tree.h"

#include <format>
#include <memory>
#include <stdexcept>

Parser::Parser::Parser(
    Lexer::TokenStream& tokenStream,
    std::map<std::string, std::function<void(Parser&, ParseRuleTree&)>>& rules
):
    rules(rules),
    tokenStream(tokenStream) {}

std::unique_ptr<Parser::ParseTree>
Parser::Parser::parse(const std::string& ruleName) {
  if(!this->rules.get().contains(ruleName)) {
    throw std::runtime_error(
        std::format("Aturan parser '{}' tidak ada.", ruleName)
    );
  }
  ParseRuleTree tree(ruleName);
  this->rules.get()[ruleName](*this, tree);
  return std::make_unique<ParseRuleTree>(std::move(tree));
}

const std::map<
    std::string, std::function<void(Parser::Parser&, Parser::ParseRuleTree&)>>&
Parser::Parser::getRules() const {
  return this->rules;
}

Lexer::TokenStream& Parser::Parser::getTokenStream() {
  return this->tokenStream;
}

Parser::KesalahanParse Parser::Parser::kesalahan(const std::string& pesan) {
  return {this->getTokenStream().getTokenSaatIni(), pesan};
}
