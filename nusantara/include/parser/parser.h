#pragma once

#include "lexer/token_stream.h"
#include "parser/parse_tree.h"

#include <functional>
#include <map>
#include <memory>
#include <string>

namespace Parser {

  class Parser {
    public:
      explicit Parser(
          Lexer::TokenStream& tokenStream,
          std::map<std::string, std::function<void(Parser&, ParseRuleTree&)>>&
              rules
      );
      std::unique_ptr<ParseTree> parse(const std::string& ruleName);
      [[nodiscard]] const std::map<
          std::string, std::function<void(Parser&, ParseRuleTree&)>>&
      getRules() const;
      Lexer::TokenStream& getTokenStream();

    private:
      std::reference_wrapper<
          std::map<std::string, std::function<void(Parser&, ParseRuleTree&)>>>
          rules;
      std::reference_wrapper<Lexer::TokenStream> tokenStream;

    protected:
  };

} // namespace Parser
