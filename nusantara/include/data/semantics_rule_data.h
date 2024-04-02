#pragma once

#include "data/parser_rule_data.h"
#include "interpreter/interpreter.h"
#include "parser/parse_tree.h"
#include "semantics/instruction.h"
#include "semantics/semantics.h"
#include <any>
#include <format>
#include <functional>
#include <map>
#include <string>
#include <vector>

inline std::map<std::string, std::function<std::any(const Parser::ParseRuleTree&, Semantics::Semantics&, std::vector<Semantics::Intruction>&)>> semanticRulesData() {
    return {
        {
            PR_NUSANTARA,
            [](const Parser::ParseRuleTree& ruleTree, Semantics::Semantics& semantics, std::vector<Semantics::Intruction>& intructions) -> std::any {
                for(const auto& child : ruleTree.getChildren()) {
                    if(const auto* pernyataan = dynamic_cast<Parser::ParseRuleTree*>(child.get())) {
                        semantics.analysis(*pernyataan, PR_PERNYATAAN, intructions);
                        semantics.getKToken().clear();
                    }
                }
                return {};
            }
        },
        {
            PR_PERNYATAAN,
            [](const Parser::ParseRuleTree& ruleTree, Semantics::Semantics& semantics, std::vector<Semantics::Intruction>& intructions) -> std::any {
                for(const auto& child : ruleTree.getChildren()) {
                    if(const auto* rule = dynamic_cast<Parser::ParseRuleTree*>(child.get())) {
                        if(rule->getRule() == PR_MUAT_FILE) {
                            semantics.analysis(*rule, PR_MUAT_FILE, intructions);
                        }
                    }
                }
                return {};
            }
        },
        {
            PR_MUAT_FILE,
            [](const Parser::ParseRuleTree& ruleTree, Semantics::Semantics& semantics, std::vector<Semantics::Intruction>& intructions) -> std::any {
                std::string filePath;
                for(const auto& child : ruleTree.getChildren()) {
                    if(const auto* prt = dynamic_cast<Parser::ParseRuleTree*>(child.get())) {
                        if(prt->getRule() == PR_TEKS) {
                            filePath = std::any_cast<std::string>(semantics.analysis(*prt, PR_TEKS, intructions));
                        }
                    }else if(const auto* ptt = dynamic_cast<Parser::ParseTokenTree*>(child.get())) {
                        semantics.getKToken().push_back(ptt->getToken());
                    }
                }
                intructions.emplace_back(
                    std::format("Memuat file '{}'.", filePath),
                    [filePath](Interpreter::Interpreter& interpreter) -> std::any {
                        std::vector<Lexer::TipeToken> tipeTokens(tipeTokensData());
                        Lexer::Lexer lexer(
                            tipeTokens, tipeTokens.size() - 1, tipeTokens.size() - 2
                        );
                        lexer.inputFilePath(filePath);
                        Lexer::TokenStream tokenStream(lexer);
                        std::map<std::string,
                            std::function<void(Parser::Parser&, Parser::ParseRuleTree&)>>
                            rules(parserRulesData());
                        Parser::Parser parser(tokenStream, rules);
                        std::unique_ptr<Parser::ParseTree> tree(parser.parse(PR_NUSANTARA));
                        Semantics::Semantics semantics(tree, semanticRulesData());
                        std::vector<Semantics::Intruction> intructions(semantics.analysis());
                        interpreter.interpret(intructions);
                        return {};
                    }
                );
                return {};
            }
        },
        {
            PR_EKSPRESI,
            [](const Parser::ParseRuleTree& ruleTree, Semantics::Semantics& semantics, std::vector<Semantics::Intruction>& intructions) -> std::any {
                for(const auto& child : ruleTree.getChildren()) {
                    if(const auto* rule = dynamic_cast<Parser::ParseRuleTree*>(child.get())) {
                        if(rule->getRule() == PR_TEKS) {
                            return semantics.analysis(*rule, PR_TEKS, intructions);
                        }
                    }
                }
                return {};
            }
        },
        {
            PR_TEKS,
            [](const Parser::ParseRuleTree& ruleTree, Semantics::Semantics& semantics, [[maybe_unused]] std::vector<Semantics::Intruction>& intructions) -> std::any {
                std::string teks;
                for(size_t index = 0; index < ruleTree.getChildren().size(); ++index) {
                    if(index <= 0 || index > ruleTree.getChildren().size() - 2) {
                        continue;
                    }
                    if(const auto* ptt = dynamic_cast<Parser::ParseTokenTree*>(ruleTree.getChildren()[index].get())) {
                        semantics.getKToken().push_back(ptt->getToken());
                        teks += ptt->getToken().getNilai();
                    }
                }
                return teks;
            }
        }
    };
}