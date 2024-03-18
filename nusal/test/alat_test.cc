#include "nusal/alat.h"
#include "nusal/nusal.h"
#include "nusal/tipe_token.h"
#include "nusal/token.h"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

TEST(ALAT_TEST, FUNGSI_BUAT_TOKEN) {
  std::string input = "teks nama = 'Fern Aerell';";
  std::string sumber = "test";
  nusal::baris baris;
  nusal::karakter karakter;
  size_t urutan = 0;
  while(auto token = nusal::buat_token(
            input, baris, karakter, sumber, nusal::nusal_data_tipe_token()
        )) {
    if(urutan == 0) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 0);
      EXPECT_EQ(token->nilai, "teks");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::TEKS);
    } else if(urutan == 1) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 4);
      EXPECT_EQ(token->nilai, " ");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::SPASI);
    } else if(urutan == 2) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 5);
      EXPECT_EQ(token->nilai, "nama");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::IDENTIFIKASI);
    } else if(urutan == 3) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 9);
      EXPECT_EQ(token->nilai, " ");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::SPASI);
    } else if(urutan == 4) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 10);
      EXPECT_EQ(token->nilai, "=");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::SAMA_DENGAN);
    } else if(urutan == 5) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 11);
      EXPECT_EQ(token->nilai, " ");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::SPASI);
    } else if(urutan == 6) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 12);
      EXPECT_EQ(token->nilai, "'");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::KUTIP_SATU);
    } else if(urutan == 7) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 13);
      EXPECT_EQ(token->nilai, "Fern");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::IDENTIFIKASI);
    } else if(urutan == 8) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 17);
      EXPECT_EQ(token->nilai, " ");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::SPASI);
    } else if(urutan == 9) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 18);
      EXPECT_EQ(token->nilai, "Aerell");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::IDENTIFIKASI);
    } else if(urutan == 10) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 24);
      EXPECT_EQ(token->nilai, "'");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::KUTIP_SATU);
    } else if(urutan == 11) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 25);
      EXPECT_EQ(token->nilai, ";");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::TITIK_KOMA);
    }
    ++urutan;
  }
}

TEST(ALAT_TEST, FUNGSI_BACA_FILE) {
  std::string file_path("tester.txt");
  std::ofstream file(file_path);
  file << "halo dunia!";
  file.close();
  EXPECT_EQ(nusal::baca_file(file_path), "halo dunia!");
  std::filesystem::remove(file_path);
}
