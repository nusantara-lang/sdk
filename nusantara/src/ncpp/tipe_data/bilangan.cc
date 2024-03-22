#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include "ncpp/tipe_data/bilangan/bilangan.h"
#include "ncpp/tipe_data/bilangan/bilangan_bulat.h"
#include "ncpp/tipe_data/bilangan/bilangan_desimal.h"
#include "ncpp/tipe_data/teks.h"

// Constructors
ncpp::bilangan::bilangan(): nilai(std::make_unique<bilangan_bulat>()) {}
ncpp::bilangan::bilangan(const std::string& nilai) {
	if(std::regex_match(nilai, bilangan_desimal::pattern())) {
		this->nilai = std::make_unique<bilangan_desimal>(nilai);
	}else if(std::regex_match(nilai, bilangan_bulat::pattern())) {
		this->nilai = std::make_unique<bilangan_bulat>(nilai);
	}else{
		throw std::runtime_error(teks("'{}' bukanlah sebuah bilangan.", nilai).ubah_ke_string());
	}
}
// Copy constructor
ncpp::bilangan::bilangan(const bilangan& other) {
    if(other.ini_bulat()) {
        this->nilai = std::make_unique<bilangan_bulat>(other.ambil_nilai_bulat());
    }else if(other.ini_desimal()) {
        this->nilai = std::make_unique<bilangan_desimal>(other.ambil_nilai_desimal());
    }else{
        throw std::runtime_error("Bilangan bukanlah bilangan bulat ataupun desimal.");
    }
}
// Copy assignment operator
ncpp::bilangan& ncpp::bilangan::operator=(const bilangan& other) {
    if(this == &other) {return *this;}
    if(other.ini_bulat()) {
        this->nilai = std::make_unique<bilangan_bulat>(other.ambil_nilai_bulat());
    }else if(other.ini_desimal()) {
        this->nilai = std::make_unique<bilangan_desimal>(other.ambil_nilai_desimal());
    }else{
        throw std::runtime_error("Bilangan bukanlah bilangan bulat ataupun desimal.");
    }
    return *this;
}
// Move constructor
ncpp::bilangan::bilangan(bilangan&& other) noexcept: nilai(std::move(other.nilai)) {}
// Move assignment operator
ncpp::bilangan& ncpp::bilangan::operator=(bilangan&& other) noexcept {
    this->nilai = std::move(other.nilai);
    return *this;
}
bool ncpp::bilangan::ini_bulat() const {
    if(const auto* ptr = dynamic_cast<bilangan_bulat*>(this->nilai.get())) {
        return true;
    }
    return false;
}
bool ncpp::bilangan::ini_desimal() const {
    if(const auto* ptr = dynamic_cast<bilangan_desimal*>(this->nilai.get())) {
        return true;
    }
    return false;
}
std::string ncpp::bilangan::ubah_ke_string() const {
    return this->nilai->ubah_ke_string();
}
ncpp::bilangan_bulat& ncpp::bilangan::ambil_nilai_bulat() const {
    if(auto* ptr = dynamic_cast<bilangan_bulat*>(this->nilai.get())) {
        return *ptr;
    }
    throw std::runtime_error("Mengambil bilangan bulat pada bilangan desimal.");
}
ncpp::bilangan_desimal& ncpp::bilangan::ambil_nilai_desimal() const {
    if(auto* ptr = dynamic_cast<bilangan_desimal*>(this->nilai.get())) {
        return *ptr;
    }
    throw std::runtime_error("Mengambil bilangan desimal pada bilangan bulat.");
}
ncpp::bilangan ncpp::bilangan::operator+(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return bilangan((this->ambil_nilai_bulat() + nilai.ambil_nilai_bulat()).ubah_ke_string());
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        bilangan_desimal hasil = this->ambil_nilai_desimal() + nilai.ambil_nilai_desimal();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        bilangan_desimal hasil = this->ambil_nilai_bulat() + nilai.ambil_nilai_desimal();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        bilangan_desimal hasil = this->ambil_nilai_desimal() + nilai.ambil_nilai_bulat();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    throw std::runtime_error("Operasi penjumlahan '+' bilangan tidak dapat dilakukan.");
}
ncpp::bilangan ncpp::bilangan::operator-(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return bilangan((this->ambil_nilai_bulat() - nilai.ambil_nilai_bulat()).ubah_ke_string());
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        bilangan_desimal hasil = this->ambil_nilai_desimal() - nilai.ambil_nilai_desimal();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        bilangan_desimal hasil = this->ambil_nilai_bulat() - nilai.ambil_nilai_desimal();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        bilangan_desimal hasil = this->ambil_nilai_desimal() - nilai.ambil_nilai_bulat();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    throw std::runtime_error("Operasi pengurangan '-' bilangan tidak dapat dilakukan.");
}
ncpp::bilangan ncpp::bilangan::operator*(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return bilangan((this->ambil_nilai_bulat() * nilai.ambil_nilai_bulat()).ubah_ke_string());
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        bilangan_desimal hasil = this->ambil_nilai_desimal() * nilai.ambil_nilai_desimal();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        bilangan_desimal hasil = this->ambil_nilai_bulat() * nilai.ambil_nilai_desimal();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        bilangan_desimal hasil = this->ambil_nilai_desimal() * nilai.ambil_nilai_bulat();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    throw std::runtime_error("Operasi perkalian '*' bilangan tidak dapat dilakukan.");
}
ncpp::bilangan ncpp::bilangan::operator/(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return bilangan((this->ambil_nilai_bulat() / nilai.ambil_nilai_bulat()).ubah_ke_string());
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        bilangan_desimal hasil = this->ambil_nilai_desimal() / nilai.ambil_nilai_desimal();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        bilangan_desimal hasil = this->ambil_nilai_bulat() / nilai.ambil_nilai_desimal();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        bilangan_desimal hasil = this->ambil_nilai_desimal() / nilai.ambil_nilai_bulat();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    throw std::runtime_error("Operasi pembagian '/' bilangan tidak dapat dilakukan.");
}
ncpp::bilangan ncpp::bilangan::operator%(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return bilangan((this->ambil_nilai_bulat() % nilai.ambil_nilai_bulat()).ubah_ke_string());
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        bilangan_desimal hasil = this->ambil_nilai_desimal() % nilai.ambil_nilai_desimal();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        bilangan_desimal hasil = this->ambil_nilai_bulat() % nilai.ambil_nilai_desimal();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        bilangan_desimal hasil = this->ambil_nilai_desimal() % nilai.ambil_nilai_bulat();
        return bilangan(hasil.ubah_ke_string_presisi(hasil.presisi()));
    }
    throw std::runtime_error("Operasi sisa pembagian '%' bilangan tidak dapat dilakukan.");
}
ncpp::bilangan ncpp::bilangan::operator~() const {
    if(this->ini_bulat()) {
        return bilangan((~this->ambil_nilai_bulat()).ubah_ke_string());
    }else if(this->ini_desimal()) {
        throw std::runtime_error("Operasi bitwise not '~' pada bilangan desimal tidak dapat dilakukan.");
    }
    throw std::runtime_error("Operasi bitwise not '~' bilangan tidak dapat dilakukan.");
}
ncpp::bilangan& ncpp::bilangan::operator++() {
	*this = *this + bilangan("1");
	return *this;
}
ncpp::bilangan ncpp::bilangan::operator++(int) {
	bilangan temp = *this;
	*this = *this + bilangan("1");
	return temp;
}
ncpp::bilangan& ncpp::bilangan::operator--() {
	*this = *this - bilangan("1");
	return *this;
}
ncpp::bilangan ncpp::bilangan::operator--(int) {
	bilangan temp = *this;
	*this = *this - bilangan("1");
	return temp;
}
ncpp::bilangan ncpp::bilangan::operator&(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return bilangan((this->ambil_nilai_bulat() & nilai.ambil_nilai_bulat()).ubah_ke_string());
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        throw std::runtime_error("Operasi bitwise and '&' pada bilangan desimal tidak dapat dilakukan.");
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        throw std::runtime_error("Operasi bitwise and '&' pada bilangan bulat dengan bilangan desimal tidak dapat dilakukan.");
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        throw std::runtime_error("Operasi bitwise and '&' pada bilangan desimal dengan bilangan bulat tidak dapat dilakukan.");
    }
    throw std::runtime_error("Operasi bitwise and '&' bilangan tidak dapat dilakukan.");
}
ncpp::bilangan ncpp::bilangan::operator^(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return bilangan((this->ambil_nilai_bulat() ^ nilai.ambil_nilai_bulat()).ubah_ke_string());
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        throw std::runtime_error("Operasi bitwise xor '^' pada bilangan desimal tidak dapat dilakukan.");
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        throw std::runtime_error("Operasi bitwise xor '^' pada bilangan bulat dengan bilangan desimal tidak dapat dilakukan.");
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        throw std::runtime_error("Operasi bitwise xor '^' pada bilangan desimal dengan bilangan bulat tidak dapat dilakukan.");
    }
    throw std::runtime_error("Operasi bitwise xor '^' bilangan tidak dapat dilakukan.");
}
ncpp::bilangan ncpp::bilangan::operator|(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return bilangan((this->ambil_nilai_bulat() | nilai.ambil_nilai_bulat()).ubah_ke_string());
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        throw std::runtime_error("Operasi bitwise or '|' pada bilangan desimal tidak dapat dilakukan.");
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        throw std::runtime_error("Operasi bitwise or '|' pada bilangan bulat dengan bilangan desimal tidak dapat dilakukan.");
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        throw std::runtime_error("Operasi bitwise or '|' pada bilangan desimal dengan bilangan bulat tidak dapat dilakukan.");
    }
    throw std::runtime_error("Operasi bitwise or '|' bilangan tidak dapat dilakukan.");
}
ncpp::bilangan ncpp::bilangan::operator<<(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return bilangan((this->ambil_nilai_bulat() << nilai.ambil_nilai_bulat()).ubah_ke_string());
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        throw std::runtime_error("Operasi bitwise left shift '<<' pada bilangan desimal tidak dapat dilakukan.");
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        throw std::runtime_error("Operasi bitwise left shift '<<' pada bilangan bulat dengan bilangan desimal tidak dapat dilakukan.");
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        throw std::runtime_error("Operasi bitwise left shift '<<' pada bilangan desimal dengan bilangan bulat tidak dapat dilakukan.");
    }
    throw std::runtime_error("Operasi bitwise left shift '<<' bilangan tidak dapat dilakukan.");
}
ncpp::bilangan ncpp::bilangan::operator>>(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return bilangan((this->ambil_nilai_bulat() >> nilai.ambil_nilai_bulat()).ubah_ke_string());
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        throw std::runtime_error("Operasi bitwise right shift '>>' pada bilangan desimal tidak dapat dilakukan.");
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        throw std::runtime_error("Operasi bitwise right shift '>>' pada bilangan bulat dengan bilangan desimal tidak dapat dilakukan.");
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        throw std::runtime_error("Operasi bitwise right shift '>>' pada bilangan desimal dengan bilangan bulat tidak dapat dilakukan.");
    }
    throw std::runtime_error("Operasi bitwise right shift '>>' bilangan tidak dapat dilakukan.");
}
bool ncpp::bilangan::operator<(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return this->ambil_nilai_bulat() < nilai.ambil_nilai_bulat();
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        return this->ambil_nilai_desimal() < nilai.ambil_nilai_desimal();
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        return this->ambil_nilai_bulat() < nilai.ambil_nilai_desimal();
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        return this->ambil_nilai_desimal() < nilai.ambil_nilai_bulat();
    }
    throw std::runtime_error("Operasi lebih kecil '<' bilangan tidak dapat dilakukan.");
}
bool ncpp::bilangan::operator<=(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return this->ambil_nilai_bulat() <= nilai.ambil_nilai_bulat();
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        return this->ambil_nilai_desimal() <= nilai.ambil_nilai_desimal();
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        return this->ambil_nilai_bulat() <= nilai.ambil_nilai_desimal();
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        return this->ambil_nilai_desimal() <= nilai.ambil_nilai_bulat();
    }
    throw std::runtime_error("Operasi lebih kecil atau sama dengan '<=' bilangan tidak dapat dilakukan.");
}
bool ncpp::bilangan::operator>(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return this->ambil_nilai_bulat() > nilai.ambil_nilai_bulat();
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        return this->ambil_nilai_desimal() > nilai.ambil_nilai_desimal();
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        return this->ambil_nilai_bulat() > nilai.ambil_nilai_desimal();
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        return this->ambil_nilai_desimal() > nilai.ambil_nilai_bulat();
    }
    throw std::runtime_error("Operasi lebih besar '>' bilangan tidak dapat dilakukan.");
}
bool ncpp::bilangan::operator>=(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return this->ambil_nilai_bulat() >= nilai.ambil_nilai_bulat();
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        return this->ambil_nilai_desimal() >= nilai.ambil_nilai_desimal();
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        return this->ambil_nilai_bulat() >= nilai.ambil_nilai_desimal();
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        return this->ambil_nilai_desimal() >= nilai.ambil_nilai_bulat();
    }
    throw std::runtime_error("Operasi lebih besar atau sama dengan '>=' bilangan tidak dapat dilakukan.");
}
bool ncpp::bilangan::operator==(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return this->ambil_nilai_bulat() == nilai.ambil_nilai_bulat();
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        return this->ambil_nilai_desimal() == nilai.ambil_nilai_desimal();
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        return this->ambil_nilai_bulat() == nilai.ambil_nilai_desimal();
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        return this->ambil_nilai_desimal() == nilai.ambil_nilai_bulat();
    }
    throw std::runtime_error("Operasi persamaan '==' bilangan tidak dapat dilakukan.");
}
bool ncpp::bilangan::operator!=(const bilangan& nilai) const {
    if(this->ini_bulat() && nilai.ini_bulat()) {
        return this->ambil_nilai_bulat() != nilai.ambil_nilai_bulat();
    }
    if(this->ini_desimal() && nilai.ini_desimal()) {
        return this->ambil_nilai_desimal() != nilai.ambil_nilai_desimal();
    }
    if(this->ini_bulat() && nilai.ini_desimal()) {
        return this->ambil_nilai_bulat() != nilai.ambil_nilai_desimal();
    }
    if(this->ini_desimal() && nilai.ini_bulat()) {
        return this->ambil_nilai_desimal() != nilai.ambil_nilai_bulat();
    }
    throw std::runtime_error("Operasi pertidaksamaan '!=' bilangan tidak dapat dilakukan.");
}
ncpp::bilangan& ncpp::bilangan::operator+=(const bilangan& nilai) {
    *this = *this + nilai;
    return *this;
}
ncpp::bilangan& ncpp::bilangan::operator-=(const bilangan& nilai) {
    *this = *this - nilai;
    return *this;
}
ncpp::bilangan& ncpp::bilangan::operator*=(const bilangan& nilai) {
    *this = *this * nilai;
    return *this;
}
ncpp::bilangan& ncpp::bilangan::operator/=(const bilangan& nilai) {
    *this = *this / nilai;
    return *this;
}
ncpp::bilangan& ncpp::bilangan::operator%=(const bilangan& nilai) {
    *this = *this % nilai;
    return *this;
}
ncpp::bilangan& ncpp::bilangan::operator&=(const bilangan& nilai) {
    *this = *this & nilai;
    return *this;
}
ncpp::bilangan& ncpp::bilangan::operator^=(const bilangan& nilai) {
    *this = *this ^ nilai;
    return *this;
}
ncpp::bilangan& ncpp::bilangan::operator|=(const bilangan& nilai) {
    *this = *this | nilai;
    return *this;
}
ncpp::bilangan& ncpp::bilangan::operator<<=(const bilangan& nilai) {
    *this = *this << nilai;
    return *this;
}
ncpp::bilangan& ncpp::bilangan::operator>>=(const bilangan& nilai) {
    *this = *this >> nilai;
    return *this;
}
