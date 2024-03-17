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
  std::string input = "f2\n'>";
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
      EXPECT_EQ(token->nama, "huruf");
      EXPECT_EQ(token->nilai, "f");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::HURUF);
    } else if(urutan == 1) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 1);
      EXPECT_EQ(token->nama, "angka");
      EXPECT_EQ(token->nilai, "2");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::ANGKA);
    } else if(urutan == 2) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 2);
      EXPECT_EQ(token->nama, "baris baru");
      EXPECT_EQ(token->nilai, "\n");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::BARIS_BARU);
    } else if(urutan == 3) {
      EXPECT_EQ(token->baris.nilai, 1);
      EXPECT_EQ(token->karakter.nilai, 0);
      EXPECT_EQ(token->nama, "kutip satu");
      EXPECT_EQ(token->nilai, "'");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::KUTIP_SATU);
    } else if(urutan == 4) {
      EXPECT_EQ(token->baris.nilai, 1);
      EXPECT_EQ(token->karakter.nilai, 1);
      EXPECT_EQ(token->nama, "tidak diketahui");
      EXPECT_EQ(token->nilai, ">");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, nusal::tipe_token::TIDAK_DIKETAHUI);
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
