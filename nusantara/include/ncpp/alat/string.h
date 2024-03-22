#pragma once

#include <gmp.h>
#include <mpfr.h>
#include <string>

namespace Ncpp {
	
	std::string ubahKeString(const mpz_t& nilai, const int& basis);
	std::string ubahKeString(const mpfr_t& nilai, const std::string& pattern, const bool& pemisahKoma = false);
	std::string ubahKeStringTetap(const mpfr_t& nilai, const int& presisi, const bool& pemisahKoma = false);
	std::string ubahKeStringPresisi(const mpfr_t& nilai, const int& presisi, const bool& pemisahKoma = false);

}
