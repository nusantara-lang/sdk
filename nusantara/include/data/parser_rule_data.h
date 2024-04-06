#pragma once

#include "data/tipe_token_data.h"
#include "parser/parse_tree.h"
#include "parser/parser.h"

#include <functional>
#include <map>
#include <memory>

// Root Rule
#define PR_NUSANTARA "nusantara"

// Pernyataan Rule
#define PR_PERNYATAAN "pernyataan"
#define PR_MUAT_FILE "muat file"

// Ekspresi Rule
#define PR_EKSPRESI "ekspresi"
#define PR_TEKS "teks"
#define PR_BILANGAN "bilangan"

inline std::map<
    std::string, std::function<void(Parser::Parser&, Parser::ParseRuleTree&)>>
parserRulesData() {
  return {
      {PR_NUSANTARA,
       [](Parser::Parser& parser, Parser::ParseRuleTree& rule) {
         parser.getTokenStream().tokenSelanjutNya(true);
         while(!parser.getTokenStream().tokenSaatIniAdalah(TT_AKHIR_DARI_FILE)
         ) {
           rule.addChild(parser.parse(PR_PERNYATAAN));
         }
       }},
      {PR_PERNYATAAN,
       [](Parser::Parser& parser, Parser::ParseRuleTree& rule) {
         if(parser.getTokenStream().tokenSaatIniAdalah(TT_MUAT)) {
           rule.addChild(parser.parse(PR_MUAT_FILE));
           if(!parser.getTokenStream().tokenSaatIniAdalah(TT_TITIK_KOMA)) {
             throw parser.kesalahan("Jangan lupa titik koma.");
           }
           rule.addChild(std::make_unique<Parser::ParseTokenTree>(
               parser.getTokenStream().getTokenSaatIni()
           ));
           parser.getTokenStream().tokenSelanjutNya(true);
         } else if(parser.getTokenStream().tokenSaatIniAtauAdalah(
                       {TT_KUTIP_SATU, TT_TANDA_HUBUNG, TT_ANGKA}
                   )) {
           rule.addChild(parser.parse(PR_EKSPRESI));
           if(!parser.getTokenStream().tokenSaatIniAdalah(TT_TITIK_KOMA)) {
             throw parser.kesalahan("Jangan lupa titik koma.");
           }
           rule.addChild(std::make_unique<Parser::ParseTokenTree>(
               parser.getTokenStream().getTokenSaatIni()
           ));
           parser.getTokenStream().tokenSelanjutNya(true);
         } else {
           throw parser.kesalahan("Pernyataan tidak valid.");
         }
       }},
      {PR_MUAT_FILE,
       [](Parser::Parser& parser, Parser::ParseRuleTree& rule) {
         if(!parser.getTokenStream().tokenSaatIniAdalah(TT_MUAT)) {
           throw parser.kesalahan(
               "Untuk memuat file harus diawali kata kunci 'muat'."
           );
         }
         rule.addChild(std::make_unique<Parser::ParseTokenTree>(
             parser.getTokenStream().getTokenSaatIni()
         ));
         parser.getTokenStream().tokenSelanjutNya(true);
         rule.addChild(parser.parse(PR_TEKS));
       }},
      {PR_EKSPRESI,
       [](Parser::Parser& parser, Parser::ParseRuleTree& rule) {
         if(parser.getTokenStream().tokenSaatIniAdalah(TT_KUTIP_SATU)) {
           rule.addChild(parser.parse(PR_TEKS));
         } else if(parser.getTokenStream().tokenSaatIniAtauAdalah(
                       {TT_TANDA_HUBUNG, TT_ANGKA}
                   )) {
           rule.addChild(parser.parse(PR_BILANGAN));
         } else {
           throw parser.kesalahan("Ekspresi tidak valid.");
         }
       }},
      {PR_TEKS,
       [](Parser::Parser& parser, Parser::ParseRuleTree& rule) {
         // KUTIP AWAL
         if(!parser.getTokenStream().tokenSaatIniAdalah(TT_KUTIP_SATU)) {
           throw parser.kesalahan("Teks harus di awali dengan kutip satu.");
         }
         rule.addChild(std::make_unique<Parser::ParseTokenTree>(
             parser.getTokenStream().getTokenSaatIni()
         ));
         parser.getTokenStream().tokenSelanjutNya(false);
         // ISI TEKS
         while(!parser.getTokenStream().tokenSaatIniAtauAdalah(
             {TT_KUTIP_SATU, TT_AKHIR_DARI_FILE}
         )) {
           // GARIS MIRING TERBALIK
           if(parser.getTokenStream().tokenSaatIniAdalah(
                  TT_GARIS_MIRING_TERBALIK
              )) {
             for(unsigned short ulang = 0; ulang < 2; ++ulang) {
               rule.addChild(std::make_unique<Parser::ParseTokenTree>(
                   parser.getTokenStream().getTokenSaatIni()
               ));
               parser.getTokenStream().tokenSelanjutNya(false);
             }
             continue;
           } else if(parser.getTokenStream().tokenSaatIniAdalah(TT_DOLAR)) {
             rule.addChild(std::make_unique<Parser::ParseTokenTree>(
                 parser.getTokenStream().getTokenSaatIni()
             ));
             parser.getTokenStream().tokenSelanjutNya(false);
             if(parser.getTokenStream().tokenSaatIniAdalah(TT_IDENTIFIKASI)) {
               rule.addChild(std::make_unique<Parser::ParseTokenTree>(
                   parser.getTokenStream().getTokenSaatIni()
               ));
               parser.getTokenStream().tokenSelanjutNya(false);
             } else if(parser.getTokenStream().tokenSaatIniAdalah(
                           TT_KURUNG_KURAWAL_BUKA
                       )) {
               rule.addChild(std::make_unique<Parser::ParseTokenTree>(
                   parser.getTokenStream().getTokenSaatIni()
               ));
               parser.getTokenStream().tokenSelanjutNya(false);
               rule.addChild(parser.parse(PR_EKSPRESI));
               if(parser.getTokenStream().tokenSaatIniAdalah(
                      TT_KURUNG_KURAWAL_TUTUP
                  )) {
                 rule.addChild(std::make_unique<Parser::ParseTokenTree>(
                     parser.getTokenStream().getTokenSaatIni()
                 ));
                 parser.getTokenStream().tokenSelanjutNya(false);
               } else {
                 throw parser.kesalahan("Teks interpolasi harus diakhiri "
                                        "dengan kurung kurawal tutup.");
               }
             } else {
               throw parser.kesalahan(
                   "Teks interpolasi harus berisi blok kode atau identifikasi."
               );
             }
             continue;
           }
           rule.addChild(std::make_unique<Parser::ParseTokenTree>(
               parser.getTokenStream().getTokenSaatIni()
           ));
           parser.getTokenStream().tokenSelanjutNya(false);
         }
         // KUTIP AKHIR
         if(!parser.getTokenStream().tokenSaatIniAdalah(TT_KUTIP_SATU)) {
           throw parser.kesalahan("Teks harus di akhiri dengan kutip satu.");
         }
         rule.addChild(std::make_unique<Parser::ParseTokenTree>(
             parser.getTokenStream().getTokenSaatIni()
         ));
         parser.getTokenStream().tokenSelanjutNya(true);
       }},
      {PR_BILANGAN,
       [](Parser::Parser& parser, Parser::ParseRuleTree& rule) {
         // TANDA HUBUNG
         if(parser.getTokenStream().tokenSaatIniAdalah(TT_TANDA_HUBUNG)) {
           rule.addChild(std::make_unique<Parser::ParseTokenTree>(
               parser.getTokenStream().getTokenSaatIni()
           ));
           parser.getTokenStream().tokenSelanjutNya(false);
         }
         // ANGKA
         while(parser.getTokenStream().tokenSaatIniAdalah(TT_ANGKA)) {
           rule.addChild(std::make_unique<Parser::ParseTokenTree>(
               parser.getTokenStream().getTokenSaatIni()
           ));
           parser.getTokenStream().tokenSelanjutNya(false);
         }
         // KOMA
         if(!parser.getTokenStream().tokenSaatIniAdalah(TT_KOMA)) {
           return;
         } else {
           rule.addChild(std::make_unique<Parser::ParseTokenTree>(
               parser.getTokenStream().getTokenSaatIni()
           ));
           parser.getTokenStream().tokenSelanjutNya(false);
         }
         // ANGKA
         if(!parser.getTokenStream().tokenSaatIniAdalah(TT_ANGKA)) {
           throw parser.kesalahan("Bilangan desimal tidak valid.");
         } else {
           rule.addChild(std::make_unique<Parser::ParseTokenTree>(
               parser.getTokenStream().getTokenSaatIni()
           ));
           parser.getTokenStream().tokenSelanjutNya(false);
         }
         while(parser.getTokenStream().tokenSaatIniAdalah(TT_ANGKA)) {
           rule.addChild(std::make_unique<Parser::ParseTokenTree>(
               parser.getTokenStream().getTokenSaatIni()
           ));
           parser.getTokenStream().tokenSelanjutNya(false);
         }
       }}
  };
}
