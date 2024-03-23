#pragma once

#include "lexer/lexer.h"
#include "lexer/tipe_token.h"
#include "lexer/token.h"
#include "parser/node.h"
#include "parser/tipe_node.h"

#include <functional>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace Parser {

  class Parser {
    public:
      Parser();
      void input(const std::string& input);
      void input(const std::string& sumber, const std::string& input);
      void inputFilePath(const std::string& filePath);
      std::unique_ptr<Node> parse();

    private:
      Lexer::Lexer lexer;
      Lexer::Token tokenSaatIni;
      std::set<std::string> muatFile;
      static const std::vector<Lexer::TipeToken>& skipTipeToken();
      bool tokenSaatIniAdalah(const Lexer::TipeToken& tipe);
      bool tokenSaatIniAdalah(const std::vector<Lexer::TipeToken>& tipe);
      void tokenSelanjutNya();
      bool mengharapkanToken(
          const std::unique_ptr<Node>& aturan, const Lexer::TipeToken& tipe,
          const std::function<std::unique_ptr<Node>()>& callback,
          const bool& skip = true,
          const std::string& pesanKesalahan = ""
      );
      bool mengharapkanToken(
          const std::unique_ptr<Node>& aturan,
          const std::vector<Lexer::TipeToken>& tipe,
          const std::function<std::unique_ptr<Node>()>& callback,
          const bool& skip = true
      );

      std::unique_ptr<Node> buatNodeAturan(const TipeNode& tipe);
      std::unique_ptr<Node> buatNodeToken();

      // parse
      void parseSkipToken();
      std::unique_ptr<Node> parsePernyataan();
      std::unique_ptr<Node> parseMuatFile();
      std::unique_ptr<Node> parseNilaiTeks();
      std::unique_ptr<Node> parseNilaiBilangan();
      std::unique_ptr<Node> parseEkspresi();
      std::unique_ptr<Node> parseNilai();
  };

} // namespace Parser
