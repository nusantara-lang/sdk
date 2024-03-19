#pragma once

#include "nusal/lexer.h"
#include "nusal/tipe_token.h"
#include "nusal/token.h"
#include "nusap/node.h"
#include "nusap/tipe_node.h"

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
      bool token_saat_ini_atau_adalah(const std::vector<nusal::tipe_token>& tipe
      );
      void lewati_spasi_putih_dan_komentar();
      void token_selanjut_nya();
      std::unique_ptr<node> buat_node_aturan(const tipe_node& tipe);
      std::unique_ptr<node> buat_node_token();

      std::unique_ptr<node> parse_pernyataan();
      std::unique_ptr<node> parse_pernyataan_blok_kode();
      std::unique_ptr<node> parse_ekspresi();
      std::unique_ptr<node> parse_blok_kode();
      std::unique_ptr<node> parse_teks();
      std::unique_ptr<node> parse_bilangan();
      std::unique_ptr<node> parse_buat_variable();
      std::unique_ptr<node> parse_buat_fungsi();
      std::unique_ptr<node> parse_manggil_fungsi();
  };

} // namespace nusap
