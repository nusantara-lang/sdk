#pragma once

#include <gmp.h>
#include <mpfr.h>

namespace Ncpp {

    int mpfrCmpDenganToleransi(const mpfr_t& nilai1, const mpfr_t& nilai2, const double& toleransi);

}