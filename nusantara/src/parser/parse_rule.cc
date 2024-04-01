#include "parser/parse_rule.h"

#include "parser/parse_tree.h"
#include "parser/parser.h"

#include <memory>

Parser::ParseRule::ParseRule(
    std::string nama, const std::function<void(Parser&, ParseRuleTree&)>& parse
):
    nama(std::move(nama)),
    parse(parse) {}

const std::string& Parser::ParseRule::getNama() const { return this->nama; }

std::string Parser::ParseRule::ubahKeString() const { return this->nama; }

std::unique_ptr<Parser::ParseTree> Parser::ParseRule::parsed(Parser& parser) {
  ParseRuleTree tree(*this);
  this->parse(parser, tree);
  return std::make_unique<ParseRuleTree>(std::move(tree));
}
