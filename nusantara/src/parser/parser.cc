#include "parser/parser.h"
#include "parser/parse_rule.h"
#include <memory>

Parser::Parser::Parser(Lexer::TokenStream& tokenStream, std::vector<ParseRule>& rules): rules(rules), tokenStream(tokenStream){}

std::unique_ptr<Parser::ParseTree> Parser::Parser::parse() {
  return this->rules.get()[0].parsed(*this);
}

const std::vector<Parser::ParseRule>& Parser::Parser::getRules() const {
    return this->rules;
}

Lexer::TokenStream& Parser::Parser::getTokenStream() {
    return this->tokenStream;
}