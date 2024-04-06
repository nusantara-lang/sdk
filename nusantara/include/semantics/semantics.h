#pragma once

#include "lexer/token.h"
#include "parser/parse_tree.h"
#include "semantics/instruction.h"
#include "semantics/kesalahan_semantics.h"

#include <any>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace Semantics {

  class Semantics {
    public:
      explicit Semantics(
          std::unique_ptr<Parser::ParseTree>& tree,
          const std::map<
              std::string,
              std::function<std::
                                any(const Parser::ParseRuleTree&, Semantics&,
                                    std::vector<Intruction>&)>>& rules
      );
      std::vector<Intruction> analysis();
      std::any analysisRule(
          const Parser::ParseRuleTree& ruleTree, const std::string& ruleName,
          std::vector<Intruction>& intructions
      );
      KesalahanSemantics kesalahan(const std::string& pesan);
      void addToken(const Lexer::Token& token);
      void clearTokens();
      bool addFileYangSudahDiMuat(const std::string& filePath);
      bool fileSudahDiMuat(const std::string& filePath);

    private:
      std::reference_wrapper<std::unique_ptr<Parser::ParseTree>> tree;
      std::map<
          std::string,
          std::function<std::
                            any(const Parser::ParseRuleTree&, Semantics&,
                                std::vector<Intruction>&)>>
          rules;
      std::vector<Lexer::Token> kToken;
      std::unordered_set<std::string> kFileYangSudahDiMuat;

    protected:
  };

} // namespace Semantics
