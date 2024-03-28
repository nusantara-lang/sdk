#include "lexer/alat.h"

#include <format>
#include <fstream>
#include <sstream>

std::string Lexer::bacaFile(const std::string& filePath) {
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

std::vector<std::string> Lexer::bacaFilePerLine(const std::string& filePath) {
  std::string konten = Lexer::bacaFile(filePath);
  std::vector<std::string> kKontenPerBaris;
  std::stringstream stream(konten);
  std::string kontenPerbaris;
  while(std::getline(stream, kontenPerbaris, '\n')) {
    kKontenPerBaris.push_back(kontenPerbaris);
  }
  return kKontenPerBaris;
}
