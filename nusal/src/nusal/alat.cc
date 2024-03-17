#include "nusal/alat.h"

#include "nusal/token.h"

#include <format>
#include <fstream>
#include <regex>
#include <sstream>

std::unique_ptr<nusal::token> nusal::buat_token(
    std::string& input, baris& baris, karakter& karakter,
    const std::string& sumber, const std::vector<tipe_token_data>& datas
) {
  if(input.empty()) { return nullptr; }
  token tkn;
  tkn.sumber = sumber;
  tkn.baris = baris;
  size_t karakter_temp = karakter.nilai;
  tkn.karakter.nilai = karakter_temp;
  for(const auto& data : datas) {
    std::regex pola("^" + data.pola);
    std::smatch matches;
    if(std::regex_search(
           input, matches, pola, std::regex_constants::match_continuous
       )) {
      tkn.tipe = data.tipe;
      tkn.nama = data.nama;
      tkn.nilai = matches.str();
      for(const char& character : tkn.nilai) {
        karakter.nilai++;
        if(character == '\n') {
          baris.nilai++;
          karakter.nilai = 0;
        }
      }
      input.replace(0, tkn.nilai.length(), "");
      return std::make_unique<token>(tkn);
    }
  }
  tkn.nilai = input[0];
  input.replace(0, tkn.nilai.length(), "");
  return std::make_unique<token>(tkn);
}

std::string nusal::baca_file(const std::string& file_path) {
  // Buka file untuk dibaca dalam mode binary
  std::ifstream file(file_path, std::ios::binary);
  // Pastikan file terbuka dengan sukses
  if(!file.is_open()) {
    throw std::runtime_error(
        std::format("Tidak dapat membuka file '{}'.", file_path)
    );
  }
  // Tentukan ukuran buffer berdasarkan ukuran file
  file.seekg(0, std::ios::end);           // Pindahkan posisi ke akhir file
  std::streampos fileSize = file.tellg(); // Dapatkan ukuran file
  file.seekg(0, std::ios::beg);           // Kembalikan posisi ke awal file
  // Jika file size 1 atau lebih kecil dari 0, maka return string kosong
  if(fileSize <= 1) { return ""; }
  // Menggunakan vector untuk buffer
  std::vector<char> buffer(fileSize);
  // String untuk menyimpan isi file
  std::ostringstream content;
  // Loop membaca file hingga EOF
  while(file.read(buffer.data(), static_cast<long long>(buffer.size()))) {
    if(file.gcount() > 0) {
      // Tambahkan data dari buffer ke dalam string
      content.write(buffer.data(), file.gcount());
    }
  }
  // Kembalikan string yang berisi isi file
  return content.str();
}
