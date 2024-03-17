#pragma once

#include "nusal/lexer.h"
#include "nusal/tipe_token.h"
#include "nusal/token.h"
#include "nusap/node.h"

#include <memory>
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
      bool token_saat_ini_adalah(const nusal::tipe_token& tipe);
      bool token_saat_ini_atau_adalah(const std::vector<nusal::tipe_token>& tipe);
      void lewati_spasi_putih();
      void token_selanjut_nya();

      std::unique_ptr<node> parse_pernyataan();
      std::unique_ptr<node> parse_membuat_kata_kunci();
      std::unique_ptr<node> parse_identifikasi();
  };

} // namespace nusap
