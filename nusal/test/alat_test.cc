#include "nusal/alat.h"
#include "nusal/tipe_token_data.h"
#include "nusal/token.h"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <vector>

enum class test_tipe_token { huruf, angka, baris_baru, kutip, TIDAK_DIKETAHUI };

std::string ubah_ke_string(const test_tipe_token& test) {
  switch(test) {
    case test_tipe_token::huruf:
      return "huruf";
    case test_tipe_token::angka:
      return "angka";
    case test_tipe_token::baris_baru:
      return "baris_baru";
    case test_tipe_token::kutip:
      return "kutip";
    case test_tipe_token::TIDAK_DIKETAHUI:
      return "tidak_diketahui";
  }
}

TEST(ALAT_TEST, FUNGSI_BUAT_TOKEN) {
  std::vector<nusal::tipe_token_data<test_tipe_token>> test_tipe_token_data = {
      {test_tipe_token::huruf,      ubah_ke_string(test_tipe_token::huruf),
       "[a-zA-Z]"                                                                       },
      {test_tipe_token::angka,      ubah_ke_string(test_tipe_token::angka),      "[0-9]"},
      {test_tipe_token::baris_baru, ubah_ke_string(test_tipe_token::baris_baru),
       "[\n]"                                                                           },
      {test_tipe_token::kutip,      ubah_ke_string(test_tipe_token::kutip),      "'"    }
  };
  std::string input = "f2\n'>";
  std::string sumber = "test";
  nusal::baris baris;
  nusal::karakter karakter;
  size_t urutan = 0;
  while(auto token = nusal::buat_token(
            input, baris, karakter, sumber, test_tipe_token_data
        )) {
    if(urutan == 0) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 0);
      EXPECT_EQ(token->nama, "huruf");
      EXPECT_EQ(token->nilai, "f");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, test_tipe_token::huruf);
    } else if(urutan == 1) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 1);
      EXPECT_EQ(token->nama, "angka");
      EXPECT_EQ(token->nilai, "2");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, test_tipe_token::angka);
    } else if(urutan == 2) {
      EXPECT_EQ(token->baris.nilai, 0);
      EXPECT_EQ(token->karakter.nilai, 2);
      EXPECT_EQ(token->nama, "baris_baru");
      EXPECT_EQ(token->nilai, "\n");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, test_tipe_token::baris_baru);
    } else if(urutan == 3) {
      EXPECT_EQ(token->baris.nilai, 1);
      EXPECT_EQ(token->karakter.nilai, 0);
      EXPECT_EQ(token->nama, "kutip");
      EXPECT_EQ(token->nilai, "'");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, test_tipe_token::kutip);
    } else if(urutan == 4) {
      EXPECT_EQ(token->baris.nilai, 1);
      EXPECT_EQ(token->karakter.nilai, 1);
      EXPECT_EQ(token->nama, "tidak_diketahui");
      EXPECT_EQ(token->nilai, ">");
      EXPECT_EQ(token->sumber, "test");
      EXPECT_EQ(token->tipe, test_tipe_token::TIDAK_DIKETAHUI);
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
