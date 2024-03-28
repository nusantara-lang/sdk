#pragma once

#include "ncpp/stream/i_streamable.h"
#include <functional>
#include <memory>
#include <string>

namespace Parser {
  class Parser;
  class ParseTree;
  class ParseRule: Ncpp::IStreamable {
    public:
      explicit ParseRule(std::string nama, const std::function<std::unique_ptr<ParseTree>(Parser&)>& parse);
      [[nodiscard]] const std::string& getNama() const;
      [[nodiscard]] std::string ubahKeString() const override;
      [[nodiscard]] const std::function<std::unique_ptr<ParseTree>(Parser&)>& getParse() const;
    private:
      std::string nama;
      std::function<std::unique_ptr<ParseTree>(Parser&)> parse;
    protected:
  };

} // namespace Parser
