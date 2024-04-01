#pragma once

#include "ncpp/stream/i_streamable.h"
#include <functional>
#include <memory>
#include <string>

namespace Parser {
  class Parser;
  class ParseTree;
  class ParseRuleTree;
  class ParseRule: Ncpp::IStreamable {
    public:
      explicit ParseRule(std::string nama, const std::function<void(Parser&, ParseRuleTree&)>& parse);
      [[nodiscard]] const std::string& getNama() const;
      [[nodiscard]] std::string ubahKeString() const override;
      std::unique_ptr<ParseTree> parsed(Parser& parser);
    private:
      std::string nama;
      std::function<void(Parser&, ParseRuleTree&)> parse;
    protected:
  };

} // namespace Parser
