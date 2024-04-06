#pragma once

#include "data/parser_rule_data.h"
#include "interpreter/interpreter.h"
#include "ncpp/tipe_data/bilangan.h"
#include "parser/parse_tree.h"
#include "semantics/instruction.h"
#include "semantics/semantics.h"

#include <any>
#include <filesystem>
#include <format>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

std::any createMuatFileIntruction(
    const std::string& filePath, Interpreter::Interpreter& interpreter
);

inline std::map<
    std::string,
    std::function<std::
                      any(const Parser::ParseRuleTree&, Semantics::Semantics&,
                          std::vector<Semantics::Intruction>&)>>
semanticRulesData() {
  return {
      {PR_NUSANTARA,
       [](const Parser::ParseRuleTree& ruleTree,
       Semantics::Semantics& semantics,
       std::vector<Semantics::Intruction>& intructions) -> std::any {
         for(const auto& child : ruleTree.getChildren()) {
           if(const auto* pernyataan =
                  dynamic_cast<Parser::ParseRuleTree*>(child.get())) {
             std::any result(
                 semantics.analysisRule(*pernyataan, PR_PERNYATAAN, intructions)
             );
             if(const auto* strPtr = std::any_cast<std::string>(&result)) {
               std::string str(*strPtr);
               intructions.emplace_back(
                   "Ekspresi teks",
                   [str]([[maybe_unused]] Interpreter::Interpreter& interpreter
                   ) -> std::any {
                     std::cout << str << "\n";
                     return str;
                   }
               );
             } else if(const auto* bilanganPtr = std::any_cast<Ncpp::Bilangan>(&result)) {
               Ncpp::Bilangan bilangan(*bilanganPtr);
               intructions.emplace_back(
                   "Ekspresi bilangan",
                   [bilangan](
                       [[maybe_unused]] Interpreter::Interpreter& interpreter
                   ) -> std::any {
                     std::cout << bilangan << "\n";
                     return bilangan;
                   }
               );
             }
             semantics.clearTokens();
           }
         }
         return {};
       }},
      {PR_PERNYATAAN,
       [](const Parser::ParseRuleTree& ruleTree,
       Semantics::Semantics& semantics,
       std::vector<Semantics::Intruction>& intructions) -> std::any {
         for(const auto& child : ruleTree.getChildren()) {
           if(const auto* rule =
                  dynamic_cast<Parser::ParseRuleTree*>(child.get())) {
             if(rule->getRule() == PR_MUAT_FILE) {
               semantics.analysisRule(*rule, PR_MUAT_FILE, intructions);
             } else if(rule->getRule() == PR_EKSPRESI) {
               return semantics.analysisRule(*rule, PR_EKSPRESI, intructions);
             }
           }
         }
         return {};
       }},
      {PR_MUAT_FILE,
       [](const Parser::ParseRuleTree& ruleTree,
       Semantics::Semantics& semantics,
       std::vector<Semantics::Intruction>& intructions) -> std::any {
         std::string filePath;
         for(const auto& child : ruleTree.getChildren()) {
           if(const auto* prt =
                  dynamic_cast<Parser::ParseRuleTree*>(child.get())) {
             if(prt->getRule() == PR_TEKS) {
               filePath = std::any_cast<std::string>(
                   semantics.analysisRule(*prt, PR_TEKS, intructions)
               );
             }
           }else if(const auto* ptt = dynamic_cast<Parser::ParseTokenTree*>(child.get())) {
             semantics.addToken(ptt->getToken());
           }
         }
         if(!semantics.addFileYangSudahDiMuat(filePath)) { return {}; }
         if(!std::filesystem::exists(filePath)) {
           throw semantics.kesalahan("File tidak ada.");
         }
         intructions.emplace_back(
             std::format("Memuat file '{}'.", filePath),
             [filePath,
              &semantics](Interpreter::Interpreter& interpreter) -> std::any {
               std::vector<Lexer::TipeToken> tipeTokens(tipeTokensData());
               Lexer::Lexer lexer(
                   tipeTokens, tipeTokens.size() - 1, tipeTokens.size() - 2
               );
               lexer.inputFilePath(filePath);
               Lexer::TokenStream tokenStream(lexer);
               std::map<
                   std::string,
                   std::function<void(Parser::Parser&, Parser::ParseRuleTree&)>>
                   rules(parserRulesData());
               Parser::Parser parser(tokenStream, rules);
               std::unique_ptr<Parser::ParseTree> parseRule =
                   parser.parse(PR_NUSANTARA);
               auto* ruleTree(
                   dynamic_cast<Parser::ParseRuleTree*>(parseRule.get())
               );
               std::vector<Semantics::Intruction> intructions;
               semantics.analysisRule(*ruleTree, PR_NUSANTARA, intructions);
               interpreter.interpret(intructions);
               return {};
             }
         );
         return {};
       }
  },
      {PR_EKSPRESI,
       [](const Parser::ParseRuleTree& ruleTree,
       Semantics::Semantics& semantics,
       std::vector<Semantics::Intruction>& intructions) -> std::any {
         for(const auto& child : ruleTree.getChildren()) {
           if(const auto* rule =
                  dynamic_cast<Parser::ParseRuleTree*>(child.get())) {
             if(rule->getRule() == PR_TEKS) {
               return semantics.analysisRule(*rule, PR_TEKS, intructions);
             } else if(rule->getRule() == PR_BILANGAN) {
               return semantics.analysisRule(*rule, PR_BILANGAN, intructions);
             }
           }
         }
         return {};
       }
  },
      {PR_TEKS,
       [](const Parser::ParseRuleTree& ruleTree,
       Semantics::Semantics& semantics,
       [[maybe_unused]] std::vector<Semantics::Intruction>& intructions
       ) -> std::any {
         std::string teks;
         for(size_t index = 0; index < ruleTree.getChildren().size(); ++index) {
           if(index <= 0 || index > ruleTree.getChildren().size() - 2) {
             continue;
           }
           if(const auto* ptt = dynamic_cast<Parser::ParseTokenTree*>(
                  ruleTree.getChildren()[index].get()
              )) {
             semantics.addToken(ptt->getToken());
             teks += ptt->getToken().getNilai();
           }
         }
         return teks;
       }
  },
      {PR_BILANGAN,
       [](const Parser::ParseRuleTree& ruleTree,
       Semantics::Semantics& semantics,
       [[maybe_unused]] std::vector<Semantics::Intruction>& intructions
       ) -> std::any {
         std::string bilanganStr;
         for(const auto& child : ruleTree.getChildren()) {
           if(const auto* ptt =
                  dynamic_cast<Parser::ParseTokenTree*>(child.get())) {
             semantics.addToken(ptt->getToken());
             bilanganStr += ptt->getToken().getNilai();
           }
         }
         return Ncpp::Bilangan(bilanganStr);
       }
  }
  };
}

inline std::any createMuatFileIntruction(
    const std::string& filePath, Interpreter::Interpreter& interpreter
) {
  std::vector<Lexer::TipeToken> tipeTokens(tipeTokensData());
  Lexer::Lexer lexer(tipeTokens, tipeTokens.size() - 1, tipeTokens.size() - 2);
  lexer.inputFilePath(filePath);
  Lexer::TokenStream tokenStream(lexer);
  std::map<
      std::string, std::function<void(Parser::Parser&, Parser::ParseRuleTree&)>>
      rules(parserRulesData());
  Parser::Parser parser(tokenStream, rules);
  std::unique_ptr<Parser::ParseTree> tree(parser.parse(PR_NUSANTARA));
  Semantics::Semantics semantics(tree, semanticRulesData());
  std::vector<Semantics::Intruction> intructions(semantics.analysis());
  interpreter.interpret(intructions);
  return {};
}
