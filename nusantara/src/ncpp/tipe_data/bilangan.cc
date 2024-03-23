#include <format>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include "ncpp/tipe_data/bilangan.h"
#include "ncpp/tipe_data/bilangan_bulat.h"
#include "ncpp/tipe_data/bilangan_desimal.h"

// Constructors
Ncpp::Bilangan::Bilangan() {
    this->nilai = std::make_unique<BilanganBulat>();
}

Ncpp::Bilangan::~Bilangan() = default;

// Copy constructor
Ncpp::Bilangan::Bilangan(const Bilangan& other) {
    if(other.iniBulat()) {
        this->nilai = std::make_unique<BilanganBulat>(other.ambilNilaiBulat());
    }else if(other.iniDesimal()) {
        this->nilai = std::make_unique<BilanganDesimal>(other.ambilNilaiDesimal());
    }else{
        throw std::runtime_error("Bilangan bukanlah Bilangan bulat ataupun desimal.");
    }
}
// Copy assignment operator
Ncpp::Bilangan& Ncpp::Bilangan::operator=(const Bilangan& other) {
    if(this == &other) {return *this;}
    if(other.iniBulat()) {
        this->nilai = std::make_unique<BilanganBulat>(other.ambilNilaiBulat());
    }else if(other.iniDesimal()) {
        this->nilai = std::make_unique<BilanganDesimal>(other.ambilNilaiDesimal());
    }else{
        throw std::runtime_error("Bilangan bukanlah Bilangan bulat ataupun desimal.");
    }
    return *this;
}
// Move constructor
Ncpp::Bilangan::Bilangan(Bilangan&& other) noexcept {
    this->nilai = std::move(other.nilai);
}
// Move assignment operator
Ncpp::Bilangan& Ncpp::Bilangan::operator=(Bilangan&& other) noexcept {
    this->nilai = std::move(other.nilai);
    return *this;
}

Ncpp::Bilangan::Bilangan(const std::string& nilai) {
	if(std::regex_match(nilai, BilanganDesimal::pattern())) {
		this->nilai = std::make_unique<BilanganDesimal>(nilai);
	}else if(std::regex_match(nilai, BilanganBulat::pattern())) {
		this->nilai = std::make_unique<BilanganBulat>(nilai);
	}else{
		throw std::runtime_error(std::format("'{}' bukanlah sebuah Bilangan.", nilai));
	}
}

bool Ncpp::Bilangan::iniBulat() const {
    if(const auto* ptr = dynamic_cast<BilanganBulat*>(this->nilai.get())) {
        return true;
    }
    return false;
}
bool Ncpp::Bilangan::iniDesimal() const {
    if(const auto* ptr = dynamic_cast<BilanganDesimal*>(this->nilai.get())) {
        return true;
    }
    return false;
}
std::string Ncpp::Bilangan::ubahKeString() const {
    if(const auto* nilaiPtr = dynamic_cast<BilanganBulat*>(this->nilai.get())) {
        return nilaiPtr->ubahKeString();
    }
    if(const auto* nilaiPtr = dynamic_cast<BilanganDesimal*>(this->nilai.get())) {
        return nilaiPtr->ubahKeString();
    }
    throw std::runtime_error("Tidak dapat merubah bilangan ke string.");
}
const Ncpp::BilanganBulat& Ncpp::Bilangan::ambilNilaiBulat() const {
    if(const auto* ptr = dynamic_cast<BilanganBulat*>(this->nilai.get())) {
        return *ptr;
    }
    throw std::runtime_error("Mengambil Bilangan bulat pada Bilangan desimal.");
}
const Ncpp::BilanganDesimal& Ncpp::Bilangan::ambilNilaiDesimal() const {
    if(const auto* ptr = dynamic_cast<BilanganDesimal*>(this->nilai.get())) {
        return *ptr;
    }
    throw std::runtime_error("Mengambil Bilangan desimal pada Bilangan bulat.");
}
Ncpp::Bilangan Ncpp::Bilangan::operator+(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return Bilangan((this->ambilNilaiBulat() + nilai.ambilNilaiBulat()).ubahKeString());
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        BilanganDesimal hasil = this->ambilNilaiDesimal() + nilai.ambilNilaiDesimal();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        BilanganDesimal hasil = this->ambilNilaiBulat() + nilai.ambilNilaiDesimal();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        BilanganDesimal hasil = this->ambilNilaiDesimal() + nilai.ambilNilaiBulat();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    throw std::runtime_error("Operasi penjumlahan '+' Bilangan tidak dapat dilakukan.");
}
Ncpp::Bilangan Ncpp::Bilangan::operator-(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return Bilangan((this->ambilNilaiBulat() - nilai.ambilNilaiBulat()).ubahKeString());
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        BilanganDesimal hasil = this->ambilNilaiDesimal() - nilai.ambilNilaiDesimal();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        BilanganDesimal hasil = this->ambilNilaiBulat() - nilai.ambilNilaiDesimal();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        BilanganDesimal hasil = this->ambilNilaiDesimal() - nilai.ambilNilaiBulat();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    throw std::runtime_error("Operasi pengurangan '-' Bilangan tidak dapat dilakukan.");
}
Ncpp::Bilangan Ncpp::Bilangan::operator*(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return Bilangan((this->ambilNilaiBulat() * nilai.ambilNilaiBulat()).ubahKeString());
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        BilanganDesimal hasil = this->ambilNilaiDesimal() * nilai.ambilNilaiDesimal();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        BilanganDesimal hasil = this->ambilNilaiBulat() * nilai.ambilNilaiDesimal();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        BilanganDesimal hasil = this->ambilNilaiDesimal() * nilai.ambilNilaiBulat();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    throw std::runtime_error("Operasi perkalian '*' Bilangan tidak dapat dilakukan.");
}
Ncpp::Bilangan Ncpp::Bilangan::operator/(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return Bilangan((this->ambilNilaiBulat() / nilai.ambilNilaiBulat()).ubahKeString());
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        BilanganDesimal hasil = this->ambilNilaiDesimal() / nilai.ambilNilaiDesimal();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        BilanganDesimal hasil = this->ambilNilaiBulat() / nilai.ambilNilaiDesimal();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        BilanganDesimal hasil = this->ambilNilaiDesimal() / nilai.ambilNilaiBulat();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    throw std::runtime_error("Operasi pembagian '/' Bilangan tidak dapat dilakukan.");
}
Ncpp::Bilangan Ncpp::Bilangan::operator%(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return Bilangan((this->ambilNilaiBulat() % nilai.ambilNilaiBulat()).ubahKeString());
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        BilanganDesimal hasil = this->ambilNilaiDesimal() % nilai.ambilNilaiDesimal();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        BilanganDesimal hasil = this->ambilNilaiBulat() % nilai.ambilNilaiDesimal();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        BilanganDesimal hasil = this->ambilNilaiDesimal() % nilai.ambilNilaiBulat();
        return Bilangan(hasil.ubahKeStringPresisi(hasil.presisi()));
    }
    throw std::runtime_error("Operasi sisa pembagian '%' Bilangan tidak dapat dilakukan.");
}
Ncpp::Bilangan Ncpp::Bilangan::operator~() const {
    if(this->iniBulat()) {
        return Bilangan((~this->ambilNilaiBulat()).ubahKeString());
    }else if(this->iniDesimal()) {
        throw std::runtime_error("Operasi bitwise not '~' pada Bilangan desimal tidak dapat dilakukan.");
    }
    throw std::runtime_error("Operasi bitwise not '~' Bilangan tidak dapat dilakukan.");
}
Ncpp::Bilangan& Ncpp::Bilangan::operator++() {
	*this = *this + Bilangan("1");
	return *this;
}
Ncpp::Bilangan const Ncpp::Bilangan::operator++(int) {
	Bilangan temp = *this;
	*this = *this + Bilangan("1");
	return temp;
}
Ncpp::Bilangan& Ncpp::Bilangan::operator--() {
	*this = *this - Bilangan("1");
	return *this;
}
Ncpp::Bilangan const Ncpp::Bilangan::operator--(int) {
	Bilangan temp = *this;
	*this = *this - Bilangan("1");
	return temp;
}
Ncpp::Bilangan Ncpp::Bilangan::operator&(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return Bilangan((this->ambilNilaiBulat() & nilai.ambilNilaiBulat()).ubahKeString());
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        throw std::runtime_error("Operasi bitwise and '&' pada Bilangan desimal tidak dapat dilakukan.");
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        throw std::runtime_error("Operasi bitwise and '&' pada Bilangan bulat dengan Bilangan desimal tidak dapat dilakukan.");
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        throw std::runtime_error("Operasi bitwise and '&' pada Bilangan desimal dengan Bilangan bulat tidak dapat dilakukan.");
    }
    throw std::runtime_error("Operasi bitwise and '&' Bilangan tidak dapat dilakukan.");
}
Ncpp::Bilangan Ncpp::Bilangan::operator^(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return Bilangan((this->ambilNilaiBulat() ^ nilai.ambilNilaiBulat()).ubahKeString());
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        throw std::runtime_error("Operasi bitwise xor '^' pada Bilangan desimal tidak dapat dilakukan.");
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        throw std::runtime_error("Operasi bitwise xor '^' pada Bilangan bulat dengan Bilangan desimal tidak dapat dilakukan.");
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        throw std::runtime_error("Operasi bitwise xor '^' pada Bilangan desimal dengan Bilangan bulat tidak dapat dilakukan.");
    }
    throw std::runtime_error("Operasi bitwise xor '^' Bilangan tidak dapat dilakukan.");
}
Ncpp::Bilangan Ncpp::Bilangan::operator|(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return Bilangan((this->ambilNilaiBulat() | nilai.ambilNilaiBulat()).ubahKeString());
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        throw std::runtime_error("Operasi bitwise or '|' pada Bilangan desimal tidak dapat dilakukan.");
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        throw std::runtime_error("Operasi bitwise or '|' pada Bilangan bulat dengan Bilangan desimal tidak dapat dilakukan.");
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        throw std::runtime_error("Operasi bitwise or '|' pada Bilangan desimal dengan Bilangan bulat tidak dapat dilakukan.");
    }
    throw std::runtime_error("Operasi bitwise or '|' Bilangan tidak dapat dilakukan.");
}
Ncpp::Bilangan Ncpp::Bilangan::operator<<(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return Bilangan((this->ambilNilaiBulat() << nilai.ambilNilaiBulat()).ubahKeString());
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        throw std::runtime_error("Operasi bitwise left shift '<<' pada Bilangan desimal tidak dapat dilakukan.");
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        throw std::runtime_error("Operasi bitwise left shift '<<' pada Bilangan bulat dengan Bilangan desimal tidak dapat dilakukan.");
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        throw std::runtime_error("Operasi bitwise left shift '<<' pada Bilangan desimal dengan Bilangan bulat tidak dapat dilakukan.");
    }
    throw std::runtime_error("Operasi bitwise left shift '<<' Bilangan tidak dapat dilakukan.");
}
Ncpp::Bilangan Ncpp::Bilangan::operator>>(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return Bilangan((this->ambilNilaiBulat() >> nilai.ambilNilaiBulat()).ubahKeString());
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        throw std::runtime_error("Operasi bitwise right shift '>>' pada Bilangan desimal tidak dapat dilakukan.");
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        throw std::runtime_error("Operasi bitwise right shift '>>' pada Bilangan bulat dengan Bilangan desimal tidak dapat dilakukan.");
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        throw std::runtime_error("Operasi bitwise right shift '>>' pada Bilangan desimal dengan Bilangan bulat tidak dapat dilakukan.");
    }
    throw std::runtime_error("Operasi bitwise right shift '>>' Bilangan tidak dapat dilakukan.");
}
bool Ncpp::Bilangan::operator<(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return this->ambilNilaiBulat() < nilai.ambilNilaiBulat();
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        return this->ambilNilaiDesimal() < nilai.ambilNilaiDesimal();
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        return this->ambilNilaiBulat() < nilai.ambilNilaiDesimal();
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        return this->ambilNilaiDesimal() < nilai.ambilNilaiBulat();
    }
    throw std::runtime_error("Operasi lebih kecil '<' Bilangan tidak dapat dilakukan.");
}
bool Ncpp::Bilangan::operator<=(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return this->ambilNilaiBulat() <= nilai.ambilNilaiBulat();
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        return this->ambilNilaiDesimal() <= nilai.ambilNilaiDesimal();
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        return this->ambilNilaiBulat() <= nilai.ambilNilaiDesimal();
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        return this->ambilNilaiDesimal() <= nilai.ambilNilaiBulat();
    }
    throw std::runtime_error("Operasi lebih kecil atau sama dengan '<=' Bilangan tidak dapat dilakukan.");
}
bool Ncpp::Bilangan::operator>(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return this->ambilNilaiBulat() > nilai.ambilNilaiBulat();
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        return this->ambilNilaiDesimal() > nilai.ambilNilaiDesimal();
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        return this->ambilNilaiBulat() > nilai.ambilNilaiDesimal();
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        return this->ambilNilaiDesimal() > nilai.ambilNilaiBulat();
    }
    throw std::runtime_error("Operasi lebih besar '>' Bilangan tidak dapat dilakukan.");
}
bool Ncpp::Bilangan::operator>=(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return this->ambilNilaiBulat() >= nilai.ambilNilaiBulat();
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        return this->ambilNilaiDesimal() >= nilai.ambilNilaiDesimal();
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        return this->ambilNilaiBulat() >= nilai.ambilNilaiDesimal();
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        return this->ambilNilaiDesimal() >= nilai.ambilNilaiBulat();
    }
    throw std::runtime_error("Operasi lebih besar atau sama dengan '>=' Bilangan tidak dapat dilakukan.");
}
bool Ncpp::Bilangan::operator==(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return this->ambilNilaiBulat() == nilai.ambilNilaiBulat();
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        return this->ambilNilaiDesimal() == nilai.ambilNilaiDesimal();
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        return this->ambilNilaiBulat() == nilai.ambilNilaiDesimal();
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        return this->ambilNilaiDesimal() == nilai.ambilNilaiBulat();
    }
    throw std::runtime_error("Operasi persamaan '==' Bilangan tidak dapat dilakukan.");
}
bool Ncpp::Bilangan::operator!=(const Bilangan& nilai) const {
    if(this->iniBulat() && nilai.iniBulat()) {
        return this->ambilNilaiBulat() != nilai.ambilNilaiBulat();
    }
    if(this->iniDesimal() && nilai.iniDesimal()) {
        return this->ambilNilaiDesimal() != nilai.ambilNilaiDesimal();
    }
    if(this->iniBulat() && nilai.iniDesimal()) {
        return this->ambilNilaiBulat() != nilai.ambilNilaiDesimal();
    }
    if(this->iniDesimal() && nilai.iniBulat()) {
        return this->ambilNilaiDesimal() != nilai.ambilNilaiBulat();
    }
    throw std::runtime_error("Operasi pertidaksamaan '!=' Bilangan tidak dapat dilakukan.");
}
Ncpp::Bilangan& Ncpp::Bilangan::operator+=(const Bilangan& nilai) {
    *this = *this + nilai;
    return *this;
}
Ncpp::Bilangan& Ncpp::Bilangan::operator-=(const Bilangan& nilai) {
    *this = *this - nilai;
    return *this;
}
Ncpp::Bilangan& Ncpp::Bilangan::operator*=(const Bilangan& nilai) {
    *this = *this * nilai;
    return *this;
}
Ncpp::Bilangan& Ncpp::Bilangan::operator/=(const Bilangan& nilai) {
    *this = *this / nilai;
    return *this;
}
Ncpp::Bilangan& Ncpp::Bilangan::operator%=(const Bilangan& nilai) {
    *this = *this % nilai;
    return *this;
}
Ncpp::Bilangan& Ncpp::Bilangan::operator&=(const Bilangan& nilai) {
    *this = *this & nilai;
    return *this;
}
Ncpp::Bilangan& Ncpp::Bilangan::operator^=(const Bilangan& nilai) {
    *this = *this ^ nilai;
    return *this;
}
Ncpp::Bilangan& Ncpp::Bilangan::operator|=(const Bilangan& nilai) {
    *this = *this | nilai;
    return *this;
}
Ncpp::Bilangan& Ncpp::Bilangan::operator<<=(const Bilangan& nilai) {
    *this = *this << nilai;
    return *this;
}
Ncpp::Bilangan& Ncpp::Bilangan::operator>>=(const Bilangan& nilai) {
    *this = *this >> nilai;
    return *this;
}
