#include "ncpp/alat/mpz.h"
#include <gmp.h>

bool Ncpp::mpzIniNegatif(const mpz_t& nilai) {
    return mpz_cmp_si(nilai, 0) < 0;
}