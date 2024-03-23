#pragma once

#include "lexer/token.h"

#include <any>
#include <functional>
#include <lexer/lexer.h>
#include <lexer/tipe_token.h>
#include <map>
#include <optional>
#include <parser/parser.h>
#include <parser/visitor.h>
#include <string>
#include <vector>

namespace Interpreter {

  class Interpreter: private Parser::Visitor {
    public:
      Interpreter();
      void input(const std::string& input);
      void input(const std::string& sumber, const std::string& input);
      void inputFilePath(const std::string& filePath);

      struct Variabel {
          Lexer::TipeToken tipe;
          std::any nilai;
      };

      struct Fungsi {
          std::optional<Lexer::TipeToken> tipe;
          std::function<std::any(std::map<std::string, Variabel>&)> definisi;
      };

      struct Kawasan {
          std::map<std::string, Variabel> kVariabel;
          std::map<std::string, Fungsi> kFungsi;
      };

    private:
      std::map<std::string, Parser::Parser> kParser;
      std::vector<Kawasan> kKawasan;
      std::vector<Lexer::Token> kToken;

      void awal();

      Kawasan& ambilKawasanTerakhir();

      Variabel& buatVariabel(
          const Lexer::TipeToken& tipe, const std::string& nama,
          const std::any& nilai
      );
      Variabel& ambilVariabel(const std::string& nama);

      Fungsi& buatFungsi(
          const Lexer::TipeToken& tipe, const std::string& nama,
          const std::function<std::any(std::map<std::string, Variabel>&)>&
              definisi
      );
      Fungsi& ambilFungsi(const std::string& nama);

      std::any visitToken(const Parser::TokenCtx& ctx) override;
      std::any visitNilaiTeks(const Parser::NilaiTeksCtx& ctx) override;
      std::any visitMuatFile(const Parser::MuatFileCtx& ctx) override;
      std::any visitPernyataan(const Parser::PernyataanCtx& ctx) override;
      std::any visitNusantara(const Parser::NusantaraCtx& ctx) override;
      std::any visitNilaiBilangan(const Parser::NilaiBilanganCtx& ctx) override;
      std::any visitEkspresi(const Parser::EkspresiCtx& ctx) override;
      std::any visitNilai(const Parser::NilaiCtx& ctx) override;
  };

} // namespace Interpreter
