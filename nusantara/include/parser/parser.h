#pragma once

#include "lexer/token_stream.h"
#include "parser/parse_tree.h"

#include <functional>
#include <memory>
#include <vector>

namespace Parser {

  class Parser {
    public:
      explicit Parser(Lexer::TokenStream& tokenStream, std::vector<ParseRule>& rules);
      std::unique_ptr<ParseTree> parse();
      [[nodiscard]] const std::vector<ParseRule>& getRules() const;
      Lexer::TokenStream& getTokenStream();
    private:
      std::reference_wrapper<std::vector<ParseRule>> rules;
      std::reference_wrapper<Lexer::TokenStream> tokenStream;
    protected:
  };

} // namespace Parser
