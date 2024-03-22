#include "ncpp/alat/mpfr.h"

int Ncpp::mpfrCmpDenganToleransi(const mpfr_t& nilai1, const mpfr_t& nilai2, const double& toleransi) {
    mpfr_t diff;
    mpfr_init(diff);
    mpfr_sub(diff, nilai1, nilai2, MPFR_RNDN);
    mpfr_abs(diff, diff, MPFR_RNDN);
    if (mpfr_cmp_d(diff, toleransi) < 0) {
        mpfr_clear(diff);
        return 0;
    }
    if (mpfr_cmp(nilai1, nilai2) > 0) {
        mpfr_clear(diff);
        return 1;
    }
    mpfr_clear(diff);
    return -1;
}
