#pragma once

#include "nusal/tipe_token_data.h"
#include "nusal/token.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace nusal {

  class lexer {
    public:
      explicit lexer(const std::vector<tipe_token_data>& tipe_token_data);

      void input(const std::string& input);

      void input(const std::string& sumber, const std::string& input);

      void input_filepath(const std::string& file_path);

      std::unique_ptr<token> ambil_token();

    private:
      std::vector<tipe_token_data> tipe_token_data;
      baris baris;
      karakter karakter;
      std::map<std::string, std::string> sumber_berserta_input = {};
  };

} // namespace nusal
