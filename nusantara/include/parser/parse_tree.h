#pragma once

#include "lexer/token.h"
#include "ncpp/stream/i_streamable.h"
#include "parser/parse_rule.h"

#include <memory>
#include <string>
#include <vector>

namespace Parser {

  class ParseTree: public virtual Ncpp::IStreamable {
    public:
      ParseTree() = default;
      ParseTree(const ParseTree&) = default;
      ParseTree(ParseTree&&) noexcept = default;
      ParseTree& operator=(const ParseTree&) = default;
      ParseTree& operator=(ParseTree&&) noexcept = default;
      ~ParseTree() override = default;
      [[nodiscard]] std::string ubahKeString() const override = 0;
      [[nodiscard]] virtual std::string ubahKeString(const int& level) const = 0;
    private:
    protected:
  };

  class ParseRuleTree: public ParseTree {
    public:
      ParseRuleTree(const ParseRuleTree&) = default;
      ParseRuleTree& operator=(const ParseRuleTree&) = default;
      ParseRuleTree& operator=(ParseRuleTree&&) noexcept = default;
      ParseRuleTree(ParseRuleTree&& other) noexcept;
      ~ParseRuleTree() override = default;
      explicit ParseRuleTree(const ParseRule& rule);
      void addChild(std::unique_ptr<ParseTree>&& child);
      [[nodiscard]] const std::string& getRule() const;
      [[nodiscard]] const std::vector<std::unique_ptr<ParseTree>>& getChildren() const;
      [[nodiscard]] std::string ubahKeString() const override;
      [[nodiscard]] std::string ubahKeString(const int& level) const override;
    private:
      std::string rule;
      std::vector<std::unique_ptr<ParseTree>> children;
    protected:
  };

  class ParseTokenTree: public ParseTree {
    public:
      explicit ParseTokenTree(const Lexer::Token& token);
      [[nodiscard]] const Lexer::Token& getToken() const;
      [[nodiscard]] std::string ubahKeString() const override;
      [[nodiscard]] std::string ubahKeString(const int& level) const override;
    private:
      Lexer::Token token;
    protected:
  };

} // namespace Parser
