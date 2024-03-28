#include "parser/parser.h"

Parser::Parser::Parser(Lexer::TokenStream& tokenStream, std::vector<ParseRule>& rules): rules(rules), tokenStream(tokenStream){}

std::unique_ptr<Parser::ParseTree> Parser::Parser::parse() {
  return this->rules.get()[0].getParse()(*this);
}

const std::vector<Parser::ParseRule>& Parser::Parser::getRules() const {
    return this->rules;
}

const Lexer::TokenStream& Parser::Parser::getTokenStream() const {
    return this->tokenStream;
}