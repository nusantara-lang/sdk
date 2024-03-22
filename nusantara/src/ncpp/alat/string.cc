#include "ncpp/alat/string.h"
#include <mpfr.h>
#include <format>
#include <string>

std::string Ncpp::ubahKeString(const mpz_t& nilai, const int& basis) {
	size_t bufferSize = mpz_sizeinbase(nilai, basis) + 2;
	char* buffer = new char[bufferSize];      
	mpz_get_str(buffer, basis, nilai);
	std::string result(buffer);
	delete[] buffer;
	return result;
}

std::string Ncpp::ubahKeString(const mpfr_t& nilai, const std::string& pattern, const bool& pemisah_koma) {
	int buffer_size = mpfr_snprintf(nullptr, 0, pattern.c_str(), nilai);
	std::string result(buffer_size, '\0');
	mpfr_snprintf(&result[0], buffer_size + 1, pattern.c_str(), nilai);
	if(pemisah_koma) {
		size_t pos = result.find('.');
		if (pos != std::string::npos) {
			result[pos] = ',';
		}
	}
	return result;
}

std::string Ncpp::ubahKeStringTetap(const mpfr_t& nilai, const int& presisi, const bool& pemisah_koma) {
	return ubahKeString(nilai, std::format("%.{}Rf", presisi), pemisah_koma);
}

std::string Ncpp::ubahKeStringPresisi(const mpfr_t& nilai, const int& presisi, const bool& pemisah_koma) {
	return ubahKeString(nilai, std::format("%.{}Rg", presisi), pemisah_koma);
}
