#include <gmp.h>
#include <mpfr.h>
#include <regex>
#include <string>
#include "ncpp/tipe_data/bilangan_bulat.h"
#include "ncpp/tipe_data/bilangan_desimal.h"
#include "ncpp/alat/string.h"
#include "ncpp/tipe_data/i_tipe_data.h"

// Constructors
Ncpp::BilanganBulat::BilanganBulat(): ITipeData<mpz_t>() {
	mpz_init(this->nilai);
}
Ncpp::BilanganBulat::BilanganBulat(const std::string& nilai) {	
	mpz_init_set_str(this->nilai, nilai.c_str(), BilanganBulat::basis);
}
// Destructor
Ncpp::BilanganBulat::~BilanganBulat() {
 mpz_clear(this->nilai);
}
// Copy constructor
Ncpp::BilanganBulat::BilanganBulat(const BilanganBulat& other) {
	mpz_init_set(this->nilai, other.nilai);
}
// Copy assignment operator
Ncpp::BilanganBulat& Ncpp::BilanganBulat::operator=(const BilanganBulat& other) {
	if(this != &other) {
		mpz_set(this->nilai, other.nilai);
	}
	return *this;
}
// Move constructor
Ncpp::BilanganBulat::BilanganBulat(BilanganBulat&& other) noexcept {
	mpz_init(this->nilai);
	mpz_swap(this->nilai, other.nilai);
}
// Move assignment operator
Ncpp::BilanganBulat& Ncpp::BilanganBulat::operator=(BilanganBulat&& other) noexcept {
	if(this != &other) {
		mpz_swap(this->nilai, other.nilai);
	}
	return *this;
}

const int Ncpp::BilanganBulat::basis = 10;

std::regex Ncpp::BilanganBulat::pattern() {
    return std::regex("^-?[0-9]+$");
}

std::string Ncpp::BilanganBulat::ubahKeString() const {
	return Ncpp::ubahKeString(this->ambil(), BilanganBulat::basis);
}

const mpz_t& Ncpp::BilanganBulat::ambil() const {
    return this->nilai;
}

Ncpp::BilanganBulat Ncpp::BilanganBulat::ubah(const BilanganDesimal &nilai) {
	mpz_t nilai_bulat;
  	mpz_init(nilai_bulat);
  	mpfr_get_z(nilai_bulat, nilai.ambil(), BilanganDesimal::pembulatan);
	std::string nilai_bulat_str = Ncpp::ubahKeString(nilai_bulat, BilanganBulat::basis);
	mpz_clear(nilai_bulat);
	return BilanganBulat(nilai_bulat_str);
}
Ncpp::BilanganBulat Ncpp::BilanganBulat::operator+(const BilanganBulat& nilai) const {
	mpz_t hasil;
	mpz_init(hasil);
	mpz_add(hasil, this->ambil(), nilai.ambil());
	std::string hasil_str = Ncpp::ubahKeString(hasil, BilanganBulat::basis);
	mpz_clear(hasil);
	return BilanganBulat(hasil_str);
}
Ncpp::BilanganDesimal Ncpp::BilanganBulat::operator+(const BilanganDesimal& nilai) const {
	return BilanganDesimal::ubah(*this) + nilai;
}
Ncpp::BilanganBulat Ncpp::BilanganBulat::operator-(const BilanganBulat& nilai) const {
	mpz_t hasil;
	mpz_init(hasil);
	mpz_sub(hasil, this->ambil(), nilai.ambil());
	std::string hasil_str = Ncpp::ubahKeString(hasil, BilanganBulat::basis);
	mpz_clear(hasil);
	return BilanganBulat(hasil_str);
}
Ncpp::BilanganDesimal Ncpp::BilanganBulat::operator-(const BilanganDesimal& nilai) const {
	return BilanganDesimal::ubah(*this) - nilai;
}
Ncpp::BilanganBulat Ncpp::BilanganBulat::operator*(const BilanganBulat& nilai) const {
	mpz_t hasil;
	mpz_init(hasil);
	mpz_mul(hasil, this->ambil(), nilai.ambil());
	std::string hasil_str = Ncpp::ubahKeString(hasil, BilanganBulat::basis);
	mpz_clear(hasil);
	return BilanganBulat(hasil_str);
}
Ncpp::BilanganDesimal Ncpp::BilanganBulat::operator*(const BilanganDesimal& nilai) const {
	return BilanganDesimal::ubah(*this) * nilai;
}
Ncpp::BilanganDesimal Ncpp::BilanganBulat::operator/(const BilanganBulat& nilai) const {
	return BilanganDesimal::ubah(*this) / BilanganDesimal::ubah(nilai);
}
Ncpp::BilanganDesimal Ncpp::BilanganBulat::operator/(const BilanganDesimal& nilai) const {
	return BilanganDesimal::ubah(*this) / nilai;
}
Ncpp::BilanganBulat Ncpp::BilanganBulat::operator%(const BilanganBulat& nilai) const {
	mpz_t hasil;
	mpz_init(hasil);
	mpz_mod(hasil, this->ambil(), nilai.ambil());
	std::string hasil_str = Ncpp::ubahKeString(hasil, BilanganBulat::basis);
	mpz_clear(hasil);
	return BilanganBulat(hasil_str);
}
Ncpp::BilanganDesimal Ncpp::BilanganBulat::operator%(const BilanganDesimal& nilai) const {
	return BilanganDesimal::ubah(*this) % nilai;
}
Ncpp::BilanganBulat Ncpp::BilanganBulat::operator~() const {
	mpz_t hasil;
	mpz_init(hasil);
	mpz_com(hasil, this->ambil());
	std::string hasil_str = Ncpp::ubahKeString(hasil, BilanganBulat::basis);
	mpz_clear(hasil);
	return BilanganBulat(hasil_str);
}
Ncpp::BilanganBulat& Ncpp::BilanganBulat::operator++() {
	*this = *this + BilanganBulat("1");
	return *this;
}
Ncpp::BilanganBulat const Ncpp::BilanganBulat::operator++(int) {
	BilanganBulat temp = *this;
	*this = *this + BilanganBulat("1");
	return temp;
}
Ncpp::BilanganBulat& Ncpp::BilanganBulat::operator--() {
	*this = *this - BilanganBulat("1");
	return *this;
}
Ncpp::BilanganBulat const Ncpp::BilanganBulat::operator--(int) {
	BilanganBulat temp = *this;
	*this = *this - BilanganBulat("1");
	return temp;
}
Ncpp::BilanganBulat Ncpp::BilanganBulat::operator&(const BilanganBulat& nilai) const {
	mpz_t hasil;
	mpz_init(hasil);
	mpz_and(hasil, this->ambil(), nilai.ambil());
	std::string hasil_str = Ncpp::ubahKeString(hasil, BilanganBulat::basis);
	mpz_clear(hasil);
	return BilanganBulat(hasil_str);
}
Ncpp::BilanganBulat Ncpp::BilanganBulat::operator^(const BilanganBulat& nilai) const {
	mpz_t hasil;
	mpz_init(hasil);
	mpz_xor(hasil, this->ambil(), nilai.ambil());
	std::string hasil_str = Ncpp::ubahKeString(hasil, BilanganBulat::basis);
	mpz_clear(hasil);
	return BilanganBulat(hasil_str);
}
Ncpp::BilanganBulat Ncpp::BilanganBulat::operator|(const BilanganBulat& nilai) const {
	mpz_t hasil;
	mpz_init(hasil);
	mpz_ior(hasil, this->ambil(), nilai.ambil());
	std::string hasil_str = Ncpp::ubahKeString(hasil, BilanganBulat::basis);
	mpz_clear(hasil);
	return BilanganBulat(hasil_str);
}
Ncpp::BilanganBulat Ncpp::BilanganBulat::operator<<(const BilanganBulat& nilai) const {
	mpz_t hasil;
	mpz_init(hasil);
	mpz_mul_2exp(hasil, this->ambil(), mpz_get_ui(nilai.ambil()));
	std::string hasil_str = Ncpp::ubahKeString(hasil, BilanganBulat::basis);
	mpz_clear(hasil);
	return BilanganBulat(hasil_str);
}
Ncpp::BilanganBulat Ncpp::BilanganBulat::operator>>(const BilanganBulat& nilai) const {
	mpz_t hasil;
	mpz_init(hasil);
	mpz_tdiv_q_2exp(hasil, this->ambil(), mpz_get_ui(nilai.ambil()));
	std::string hasil_str = Ncpp::ubahKeString(hasil, BilanganBulat::basis);
	mpz_clear(hasil);
	return BilanganBulat(hasil_str);
}
bool Ncpp::BilanganBulat::operator<(const BilanganBulat& nilai) const {
	return mpz_cmp(this->ambil(), nilai.ambil()) < 0;
}
bool Ncpp::BilanganBulat::operator<(const BilanganDesimal& nilai) const {
	return BilanganDesimal::ubah(*this) < nilai;
}
bool Ncpp::BilanganBulat::operator<=(const BilanganBulat& nilai) const {
	return mpz_cmp(this->ambil(), nilai.ambil()) <= 0;
}
bool Ncpp::BilanganBulat::operator<=(const BilanganDesimal& nilai) const {
	return BilanganDesimal::ubah(*this) <= nilai;
}
bool Ncpp::BilanganBulat::operator>(const BilanganBulat& nilai) const {
	return mpz_cmp(this->ambil(), nilai.ambil()) > 0;
}
bool Ncpp::BilanganBulat::operator>(const BilanganDesimal& nilai) const {
	return BilanganDesimal::ubah(*this) > nilai;
}
bool Ncpp::BilanganBulat::operator>=(const BilanganBulat& nilai) const {
	return mpz_cmp(this->ambil(), nilai.ambil()) >= 0;
}
bool Ncpp::BilanganBulat::operator>=(const BilanganDesimal& nilai) const {
	return BilanganDesimal::ubah(*this) >= nilai;
}
bool Ncpp::BilanganBulat::operator==(const BilanganBulat& nilai) const {
	return mpz_cmp(this->ambil(), nilai.ambil()) == 0;
}
bool Ncpp::BilanganBulat::operator==(const BilanganDesimal& nilai) const {
	return BilanganDesimal::ubah(*this) == nilai;
}
bool Ncpp::BilanganBulat::operator!=(const BilanganBulat& nilai) const {
	return mpz_cmp(this->ambil(), nilai.ambil()) != 0;
}
bool Ncpp::BilanganBulat::operator!=(const BilanganDesimal& nilai) const {
	return BilanganDesimal::ubah(*this) != nilai;
}
Ncpp::BilanganBulat& Ncpp::BilanganBulat::operator+=(const BilanganBulat& nilai) {
	*this = *this + nilai;
	return *this;
}
Ncpp::BilanganBulat& Ncpp::BilanganBulat::operator-=(const BilanganBulat& nilai) {
	*this = *this - nilai;
	return *this;
}
Ncpp::BilanganBulat& Ncpp::BilanganBulat::operator*=(const BilanganBulat& nilai) {
	*this = *this * nilai;
	return *this;
}
Ncpp::BilanganBulat& Ncpp::BilanganBulat::operator/=(const BilanganBulat& nilai) {
	*this = BilanganBulat::ubah(*this / nilai);
	return *this;
}
Ncpp::BilanganBulat& Ncpp::BilanganBulat::operator%=(const BilanganBulat& nilai) {
	*this = *this % nilai;
	return *this;
}
Ncpp::BilanganBulat& Ncpp::BilanganBulat::operator&=(const BilanganBulat& nilai) {
	*this = *this & nilai;
	return *this;
}
Ncpp::BilanganBulat& Ncpp::BilanganBulat::operator^=(const BilanganBulat& nilai) {
	*this = *this ^ nilai;
	return *this;
}
Ncpp::BilanganBulat& Ncpp::BilanganBulat::operator|=(const BilanganBulat& nilai) {
	*this = *this | nilai;
	return *this;
}
Ncpp::BilanganBulat& Ncpp::BilanganBulat::operator<<=(const BilanganBulat& nilai) {
	*this = *this << nilai;
	return *this;
}
Ncpp::BilanganBulat& Ncpp::BilanganBulat::operator>>=(const BilanganBulat& nilai) {
	*this = *this >> nilai;
	return *this;
}
