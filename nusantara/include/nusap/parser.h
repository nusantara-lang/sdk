#pragma once

#include "nusal/lexer.h"
#include "nusal/tipe_token.h"
#include "nusal/token.h"
#include "nusap/node.h"
#include "nusap/tipe_node.h"

#include <functional>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace Nusap {

  class Parser {
    public:
      Parser();
      void input(const std::string& input);
      void input(const std::string& sumber, const std::string& input);
      void inputFilePath(const std::string& filePath);
      std::unique_ptr<Node> parse();

    private:
      Nusal::Lexer lexer;
      Nusal::Token tokenSaatIni;
      std::set<std::string> muatFile;
      static const std::vector<Nusal::TipeToken>& skipTipeToken();
      bool tokenSaatIniAdalah(const Nusal::TipeToken& tipe);
      bool tokenSaatIniAdalah(const std::vector<Nusal::TipeToken>& tipe);
      void tokenSelanjutNya();
      bool mengharapkanToken(
          const std::unique_ptr<Node>& aturan, const Nusal::TipeToken& tipe,
          const std::function<std::unique_ptr<Node>()>& callback,
          const bool& skip = true
      );
      bool mengharapkanToken(
          const std::unique_ptr<Node>& aturan,
          const std::vector<Nusal::TipeToken>& tipe,
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

} // namespace Nusap
