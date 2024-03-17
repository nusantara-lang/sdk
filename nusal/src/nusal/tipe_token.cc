#include "nusal/tipe_token.h"

std::string nusal::ubah_ke_string(const tipe_token& tipe_token) {
  switch(tipe_token) {
    case tipe_token::spasi:
      return "spasi";
    case tipe_token::baris_baru:
      return "baris_baru";
    case tipe_token::tab:
      return "tab";
    case tipe_token::angka:
      return "angka";
    case tipe_token::simbol:
      return "simbol";
    case tipe_token::huruf:
      return "huruf";
    case tipe_token::tidak_diketahui:
      return "tidak_diketahui";
  }
}
