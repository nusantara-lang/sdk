#include <format>
#include <mpfr.h>
#include <algorithm>
#include <regex>
#include <string>
#include "ncpp/alat/mpfr.h"
#include "ncpp/alat/string.h"
#include "ncpp/tipe_data/bilangan_desimal.h"
#include "ncpp/tipe_data/bilangan_bulat.h"
#include "ncpp/tipe_data/i_tipe_data.h"

// Constructors
Ncpp::BilanganDesimal::BilanganDesimal() {
	mpfr_init_set_str(this->nilai, "0.0", BilanganDesimal::basis, BilanganDesimal::pembulatan);
}
// Destructor
Ncpp::BilanganDesimal::~BilanganDesimal() {
	mpfr_clear(this->nilai);
}
// Copy constructor
Ncpp::BilanganDesimal::BilanganDesimal(const BilanganDesimal& other) {
	mpfr_init_set(this->nilai, other.nilai, BilanganDesimal::pembulatan);
}
// Copy assignment operator
Ncpp::BilanganDesimal& Ncpp::BilanganDesimal::operator=(const BilanganDesimal& other) {
	if (this != &other) {
    mpfr_set(this->nilai, other.nilai, BilanganDesimal::pembulatan);
  }
  return *this;
} 
// Move constructor
Ncpp::BilanganDesimal::BilanganDesimal(BilanganDesimal&& other) noexcept {
  mpfr_init_set_str(this->nilai, "0.0", BilanganDesimal::basis, BilanganDesimal::pembulatan);
  mpfr_swap(this->nilai, other.nilai);
  
}
// Move assignment operator
Ncpp::BilanganDesimal& Ncpp::BilanganDesimal::operator=(BilanganDesimal&& other) noexcept {
	if (this != &other) {
    mpfr_swap(this->nilai, other.nilai);
  }
  return *this;
}

Ncpp::BilanganDesimal::BilanganDesimal(const std::string& nilai) {
	std::string nilai_dengan_titik(nilai);
	std::replace(nilai_dengan_titik.begin(), nilai_dengan_titik.end(), ',', '.');	
	mpfr_init_set_str(this->nilai, nilai_dengan_titik.c_str(), BilanganDesimal::basis, BilanganDesimal::pembulatan);
}

const short Ncpp::BilanganDesimal::basis = 10;
const short Ncpp::BilanganDesimal::presisiStringBawaan = 15;
const mpfr_rnd_t Ncpp::BilanganDesimal::pembulatan = MPFR_RNDN;
const double Ncpp::BilanganDesimal::toleransi = 1e-9;

std::regex Ncpp::BilanganDesimal::pattern() {
    return std::regex("^-?[0-9]+([,.][0-9]+|([,.][0-9]*)?[eE][+-]?[0-9]+)$");
}
std::string Ncpp::BilanganDesimal::ubahKeString() const {
	return Ncpp::ubahKeStringPresisi(this->ambil(), BilanganDesimal::presisiStringBawaan, true);
}
std::string Ncpp::BilanganDesimal::ubahKeStringTetap(const long& presisi) const {
	return Ncpp::ubahKeStringTetap(this->ambil(), presisi, true);
}
std::string Ncpp::BilanganDesimal::ubahKeStringPresisi(const long& presisi) const {
	return Ncpp::ubahKeStringPresisi(this->ambil(), presisi, true);
}
const mpfr_t& Ncpp::BilanganDesimal::ambil() const {
    return this->nilai;
}

Ncpp::BilanganDesimal Ncpp::BilanganDesimal::ubah(const BilanganBulat& nilai) {
  return BilanganDesimal(std::format("{},0", nilai.ubahKeString()));
}
Ncpp::BilanganDesimal Ncpp::BilanganDesimal::operator+(const BilanganBulat& nilai) const {
	return *this + BilanganDesimal::ubah(nilai);
}
Ncpp::BilanganDesimal Ncpp::BilanganDesimal::operator+(const BilanganDesimal& nilai) const {
	mpfr_t hasil;
	mpfr_init(hasil);
	mpfr_add(hasil, this->ambil(), nilai.ambil(), BilanganDesimal::pembulatan);
	std::string hasil_str = Ncpp::ubahKeStringPresisi(hasil, mpfr_get_prec(hasil), true);
	mpfr_clear(hasil);
	return BilanganDesimal(hasil_str);
}
Ncpp::BilanganDesimal Ncpp::BilanganDesimal::operator-(const BilanganBulat& nilai) const {
	return *this - BilanganDesimal::ubah(nilai);
}
Ncpp::BilanganDesimal Ncpp::BilanganDesimal::operator-(const BilanganDesimal& nilai) const {
	mpfr_t hasil;
	mpfr_init(hasil);
	mpfr_sub(hasil, this->ambil(), nilai.ambil(), BilanganDesimal::pembulatan);
	std::string hasil_str = Ncpp::ubahKeStringPresisi(hasil, mpfr_get_prec(hasil), true);
	mpfr_clear(hasil);
	return BilanganDesimal(hasil_str);
}
Ncpp::BilanganDesimal Ncpp::BilanganDesimal::operator*(const BilanganBulat& nilai) const {
	return *this * BilanganDesimal::ubah(nilai);
}
Ncpp::BilanganDesimal Ncpp::BilanganDesimal::operator*(const BilanganDesimal& nilai) const {
	mpfr_t hasil;
	mpfr_init(hasil);
	mpfr_mul(hasil, this->ambil(), nilai.ambil(), BilanganDesimal::pembulatan);
	std::string hasil_str = Ncpp::ubahKeStringPresisi(hasil, mpfr_get_prec(hasil), true);
	mpfr_clear(hasil);
	return BilanganDesimal(hasil_str);
}
Ncpp::BilanganDesimal Ncpp::BilanganDesimal::operator/(const BilanganBulat& nilai) const {
	return *this / BilanganDesimal::ubah(nilai);
}
Ncpp::BilanganDesimal Ncpp::BilanganDesimal::operator/(const BilanganDesimal& nilai) const {
	mpfr_t hasil;
	mpfr_init(hasil);
	mpfr_div(hasil, this->ambil(), nilai.ambil(), BilanganDesimal::pembulatan);
	std::string hasil_str = Ncpp::ubahKeStringPresisi(hasil, mpfr_get_prec(hasil), true);
	mpfr_clear(hasil);
	return BilanganDesimal(hasil_str);
}
Ncpp::BilanganDesimal Ncpp::BilanganDesimal::operator%(const BilanganBulat& nilai) const {
	return *this % BilanganDesimal::ubah(nilai);
}
Ncpp::BilanganDesimal Ncpp::BilanganDesimal::operator%(const BilanganDesimal& nilai) const {
	mpfr_t hasil;
	mpfr_init(hasil);
	mpfr_fmod(hasil, this->ambil(), nilai.ambil(), BilanganDesimal::pembulatan);
	std::string hasil_str = Ncpp::ubahKeStringPresisi(hasil, mpfr_get_prec(hasil));
	mpfr_clear(hasil);
	return BilanganDesimal(hasil_str);
}
long Ncpp::BilanganDesimal::presisi() const {
	return mpfr_get_prec(this->ambil());
}
Ncpp::BilanganDesimal& Ncpp::BilanganDesimal::operator++() {
	*this = *this + BilanganDesimal("1,0");
	return *this;
}
Ncpp::BilanganDesimal const Ncpp::BilanganDesimal::operator++(int) {
	BilanganDesimal temp = *this;
	*this = *this + BilanganDesimal("1,0");
	return temp;
}
Ncpp::BilanganDesimal& Ncpp::BilanganDesimal::operator--() {
	*this = *this - BilanganDesimal("1,0");
	return *this;
}
Ncpp::BilanganDesimal const Ncpp::BilanganDesimal::operator--(int) {
	BilanganDesimal temp = *this;
	*this = *this - BilanganDesimal("1,0");
	return temp;
}
bool Ncpp::BilanganDesimal::operator<(const BilanganDesimal& nilai) const {
	return mpfrCmpDenganToleransi(this->ambil(), nilai.ambil(), BilanganDesimal::toleransi) < 0;
}
bool Ncpp::BilanganDesimal::operator<(const BilanganBulat& nilai) const {
	return mpfrCmpDenganToleransi(this->ambil(), BilanganDesimal::ubah(nilai).ambil(), BilanganDesimal::toleransi) < 0;
}
bool Ncpp::BilanganDesimal::operator<=(const BilanganDesimal& nilai) const {
	return mpfrCmpDenganToleransi(this->ambil(), nilai.ambil(), BilanganDesimal::toleransi) <= 0;
}
bool Ncpp::BilanganDesimal::operator<=(const BilanganBulat& nilai) const {
	return mpfrCmpDenganToleransi(this->ambil(), BilanganDesimal::ubah(nilai).ambil(), BilanganDesimal::toleransi) <= 0;
}
bool Ncpp::BilanganDesimal::operator>(const BilanganDesimal& nilai) const {
	return mpfrCmpDenganToleransi(this->ambil(), nilai.ambil(), BilanganDesimal::toleransi) > 0;
}
bool Ncpp::BilanganDesimal::operator>(const BilanganBulat& nilai) const {
	return mpfrCmpDenganToleransi(this->ambil(), BilanganDesimal::ubah(nilai).ambil(), BilanganDesimal::toleransi) > 0;
}
bool Ncpp::BilanganDesimal::operator>=(const BilanganDesimal& nilai) const {
	return mpfrCmpDenganToleransi(this->ambil(), nilai.ambil(), BilanganDesimal::toleransi) >= 0;
}
bool Ncpp::BilanganDesimal::operator>=(const BilanganBulat& nilai) const {
	return mpfrCmpDenganToleransi(this->ambil(), BilanganDesimal::ubah(nilai).ambil(), BilanganDesimal::toleransi) >= 0;
}
bool Ncpp::BilanganDesimal::operator==(const BilanganDesimal& nilai) const {
	return mpfrCmpDenganToleransi(this->ambil(), nilai.ambil(), BilanganDesimal::toleransi) == 0;
}
bool Ncpp::BilanganDesimal::operator==(const BilanganBulat& nilai) const {
	return *this == BilanganDesimal::ubah(nilai);
}
bool Ncpp::BilanganDesimal::operator!=(const BilanganDesimal& nilai) const {
	return mpfrCmpDenganToleransi(this->ambil(), nilai.ambil(), BilanganDesimal::toleransi) != 0;
}
bool Ncpp::BilanganDesimal::operator!=(const BilanganBulat& nilai) const {
	return mpfrCmpDenganToleransi(this->ambil(), BilanganDesimal::ubah(nilai).ambil(), BilanganDesimal::toleransi) != 0;
}
Ncpp::BilanganDesimal& Ncpp::BilanganDesimal::operator+=(const BilanganBulat& nilai) {
	*this = *this + nilai;
	return *this;
}
Ncpp::BilanganDesimal& Ncpp::BilanganDesimal::operator+=(const BilanganDesimal& nilai) {
	*this = *this + nilai;
	return *this;
}
Ncpp::BilanganDesimal& Ncpp::BilanganDesimal::operator-=(const BilanganBulat& nilai) {
	*this = *this - nilai;
	return *this;
}
Ncpp::BilanganDesimal& Ncpp::BilanganDesimal::operator-=(const BilanganDesimal& nilai) {
	*this = *this - nilai;
	return *this;
}
Ncpp::BilanganDesimal& Ncpp::BilanganDesimal::operator*=(const BilanganBulat& nilai) {
	*this = *this * nilai;
	return *this;
}
Ncpp::BilanganDesimal& Ncpp::BilanganDesimal::operator*=(const BilanganDesimal& nilai) {
	*this = *this * nilai;
	return *this;
}
Ncpp::BilanganDesimal& Ncpp::BilanganDesimal::operator/=(const BilanganBulat& nilai) {
	*this = *this / nilai;
	return *this;
}
Ncpp::BilanganDesimal& Ncpp::BilanganDesimal::operator/=(const BilanganDesimal& nilai) {
	*this = *this / nilai;
	return *this;
}
Ncpp::BilanganDesimal& Ncpp::BilanganDesimal::operator%=(const BilanganBulat& nilai) {
	*this = *this % nilai;
	return *this;
}
Ncpp::BilanganDesimal& Ncpp::BilanganDesimal::operator%=(const BilanganDesimal& nilai) {
	*this = *this % nilai;
	return *this;
}
