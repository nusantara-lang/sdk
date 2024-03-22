#pragma once

#include "nusal/token.h"

#include <any>
#include <functional>
#include <map>
#include <nusal/lexer.h>
#include <nusal/tipe_token.h>
#include <nusap/parser.h>
#include <nusap/visitor.h>
#include <optional>
#include <string>
#include <vector>

namespace Nusai {

  class Interpreter: private Nusap::Visitor {
    public:
      Interpreter();
      void input(const std::string& input);
      void input(const std::string& sumber, const std::string& input);
      void inputFilePath(const std::string& filePath);

      struct Variabel {
          Nusal::TipeToken tipe;
          std::any nilai;
      };

      struct Fungsi {
          std::optional<Nusal::TipeToken> tipe;
          std::function<std::any(std::map<std::string, Variabel>&)> definisi;
      };

      struct Kawasan {
          std::map<std::string, Variabel> kVariabel;
          std::map<std::string, Fungsi> kFungsi;
      };

    private:
      std::map<std::string, Nusap::Parser> kParser;
      std::vector<Kawasan> kKawasan;
      std::vector<Nusal::Token> kToken;

      void awal();

      Kawasan& ambilKawasanTerakhir();

      Variabel& buatVariabel(
          const Nusal::TipeToken& tipe, const std::string& nama,
          const std::any& nilai
      );
      Variabel& ambilVariabel(const std::string& nama);

      Fungsi& buatFungsi(
          const Nusal::TipeToken& tipe, const std::string& nama,
          const std::function<std::any(std::map<std::string, Variabel>&)>&
              definisi
      );
      Fungsi& ambilFungsi(const std::string& nama);

      std::any visitToken(const Nusap::TokenCtx& ctx) override;
      std::any visitNilaiTeks(const Nusap::NilaiTeksCtx& ctx) override;
      std::any visitMuatFile(const Nusap::MuatFileCtx& ctx) override;
      std::any visitPernyataan(const Nusap::PernyataanCtx& ctx) override;
      std::any visitNusantara(const Nusap::NusantaraCtx& ctx) override;
      std::any visitNilaiBilangan(const Nusap::NilaiBilanganCtx& ctx) override;
      std::any visitEkspresi(const Nusap::EkspresiCtx& ctx) override;
      std::any visitNilai(const Nusap::NilaiCtx& ctx) override;
  };

} // namespace Nusai
