#include "data/semantics_rule_data.h"
#include "data/tipe_token_data.h"
#include "interpreter/interpreter.h"
#include "lexer/lexer.h"
#include "lexer/tipe_token.h"
#include "semantics/instruction.h"

#include <cstring>
#include <exception>
#include <iostream>
#include <span>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
  auto args = std::span(argv, size_t(argc));
  try {
    if(!(argc > 1)) {
      std::cout << "Nusantara Interpreter"
                << "\n\n";
      std::cout << "Penggunaan: interpreter <nusa-file>*"
                << "\n";
      return 0;
    }
    std::vector<Lexer::TipeToken> tipeTokens(tipeTokensData());
    Lexer::Lexer lexer(
        tipeTokens, tipeTokens.size() - 1, tipeTokens.size() - 2
    );
    if(argc == 2) {
      std::vector<Lexer::TipeToken> tipeTokens(tipeTokensData());
      Lexer::Lexer lexer(
          tipeTokens, tipeTokens.size() - 1, tipeTokens.size() - 2
      );
      lexer.inputFilePath(args[1]);
      Lexer::TokenStream tokenStream(lexer);
      std::map<
          std::string,
          std::function<void(Parser::Parser&, Parser::ParseRuleTree&)>>
          rules(parserRulesData());
      Parser::Parser parser(tokenStream, rules);
      std::unique_ptr<Parser::ParseTree> tree(parser.parse(PR_NUSANTARA));
      Semantics::Semantics semantics(tree, semanticRulesData());
      semantics.addFileYangSudahDiMuat(args[1]);
      std::vector<Semantics::Intruction> intructions(semantics.analysis());
      Interpreter::Interpreter interpreter;
      interpreter.interpret(intructions);
    }
  } catch(const std::exception& error) { std::cout << error.what() << "\n"; }
  return 0;
}
