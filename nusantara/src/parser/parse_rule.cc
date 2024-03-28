#include "parser/parse_rule.h"
#include "parser/parse_tree.h"
#include "parser/parser.h"

Parser::ParseRule::ParseRule(std::string nama, const std::function<std::unique_ptr<ParseTree>(Parser&)>& parse): nama(std::move(nama)), parse(parse) {}

const std::string& Parser::ParseRule::getNama() const {
  return this->nama;
}

std::string Parser::ParseRule::ubahKeString() const {
  return this->nama;
}

const std::function<std::unique_ptr<Parser::ParseTree>(Parser::Parser&)>& Parser::ParseRule::getParse() const {
  return this->parse;
}
