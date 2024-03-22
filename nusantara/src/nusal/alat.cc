#include "nusal/alat.h"

#include <format>
#include <fstream>
#include <regex>
#include <sstream>

std::unique_ptr<Nusal::Token> Nusal::buatToken(
    std::string& input, baris& baris, karakter& karakter,
    const std::string& sumber, const std::vector<TipeTokenData>& data
) {
  if(input.empty()) { return nullptr; }
  Token tkn;
  tkn.sumber = sumber;
  tkn.baris = baris;
  size_t karakterTemp = karakter.nilai;
  tkn.karakter.nilai = karakterTemp;
  for(const auto& data : data) {
    std::regex pola("^" + data.pola);
    std::smatch matches;
    if(std::regex_search(
           input, matches, pola, std::regex_constants::match_continuous
       )) {
      tkn.tipe = data.tipe;
      tkn.nilai = matches.str();
      for(const char& character : tkn.nilai) {
        karakter.nilai++;
        if(character == '\n') {
          baris.nilai++;
          karakter.nilai = 0;
        }
      }
      input.replace(0, tkn.nilai.length(), "");
      return std::make_unique<Token>(tkn);
    }
  }
  tkn.nilai = input[0];
  input.replace(0, tkn.nilai.length(), "");
  return std::make_unique<Token>(tkn);
}

std::string Nusal::bacaFile(const std::string& filePath) {
  // Buka file untuk dibaca dalam mode binary
  std::ifstream file(filePath, std::ios::binary);
  // Pastikan file terbuka dengan sukses
  if(!file.is_open()) {
    throw std::runtime_error(
        std::format("Tidak dapat membuka file '{}'.", filePath)
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

std::vector<std::string> Nusal::bacaFilePerLine(const std::string& filePath) {
  std::string konten = Nusal::bacaFile(filePath);
  std::vector<std::string> kKontenPerBaris;
  std::stringstream stream(konten);
  std::string kontenPerbaris;
  while(std::getline(stream, kontenPerbaris, '\n')) {
    kKontenPerBaris.push_back(kontenPerbaris);
  }
  return kKontenPerBaris;
}
