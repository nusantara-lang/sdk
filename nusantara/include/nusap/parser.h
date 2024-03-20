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

namespace nusap {

  class parser {
    public:
      parser();
      void input(const std::string& input);
      void input(const std::string& sumber, const std::string& input);
      void input_filepath(const std::string& file_path);
      std::unique_ptr<node> parse();

    private:
      nusal::lexer lexer;
      std::unique_ptr<nusal::token> token_saat_ini;
      std::set<std::string> muatFile;
      static const std::vector<nusal::tipe_token>& skipTipeToken();
      bool tokenSaatIni(const nusal::tipe_token& tipe);
      bool tokenSaatIni(const std::vector<nusal::tipe_token>& tipe);
      void tokenSelanjutNya();
      bool mengharapkanToken(const std::unique_ptr<node>& aturan, const nusal::tipe_token& tipe, const std::function<std::unique_ptr<node>()>& callback);
      bool mengharapkanToken(const std::unique_ptr<node>& aturan, const std::vector<nusal::tipe_token>& tipe, const std::function<std::unique_ptr<node>()>& callback);

      std::unique_ptr<node> buatNodeAturan(const tipe_node& tipe);
      std::unique_ptr<node> buatNodeToken();
      
      // parse
      void parseSkipToken();
      std::unique_ptr<node> parse_pernyataan();
      std::unique_ptr<node> parse_muat_file();
      std::unique_ptr<node> parse_nilai_teks();
  };

} // namespace nusap
