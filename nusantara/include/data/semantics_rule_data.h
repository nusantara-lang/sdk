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
               const auto* ruleTree(
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
         bool garisMiringTerbalik = false;
         bool interpolasi = false;
         for(size_t index = 0; index < ruleTree.getChildren().size(); ++index) {
           if(index <= 0 || index > ruleTree.getChildren().size() - 2) {
             continue;
           }
           if(const auto* ptt = dynamic_cast<Parser::ParseTokenTree*>(
                  ruleTree.getChildren()[index].get()
              )) {
             semantics.addToken(ptt->getToken());
             std::string nilai = ptt->getToken().getNilai();
             if(!garisMiringTerbalik && nilai == "\\") {
               garisMiringTerbalik = true;
               continue;
             }
             if(garisMiringTerbalik) {
               garisMiringTerbalik = false;
               if(nilai[0] == 'n') {
                 nilai[0] = '\n';
               } else if(nilai[0] == 't') {
                 nilai[0] = '\t';
               } else if(nilai[0] == 'r') {
                 nilai[0] = '\r';
               }
               teks += nilai;
               continue;
             }
             if(!interpolasi && nilai == "$") {
               interpolasi = true;
               continue;
             }
             if(interpolasi) {
               interpolasi = false;
               if(nilai == "{") {
                 ++index;
                 if(const auto* prt = dynamic_cast<Parser::ParseRuleTree*>(
                        ruleTree.getChildren()[index].get()
                    )) {
                   std::any result(
                       semantics.analysisRule(*prt, PR_EKSPRESI, intructions)
                   );
                   if(const auto* strPtr =
                          std::any_cast<std::string>(&result)) {
                     nilai = *strPtr;
                   } else if(const auto* bilanganPtr = std::any_cast<Ncpp::Bilangan>(&result)) {
                     nilai = bilanganPtr->ubahKeString();
                   }
                 }
                 ++index;
               } else {
                 nilai = std::format("[id:{}]", nilai);
               }
               teks += nilai;
               continue;
             }
             teks += nilai;
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
         if(bilanganStr[0] == '0') {
           throw semantics.kesalahan("Bilangan tidak boleh di awali nol '0'.");
         }
         return Ncpp::Bilangan(bilanganStr);
       }
  }
  };
}
