#include "nusal/tipe_token_data.h"

Nusal::TipeTokenData::TipeTokenData(const TipeToken& tipe, std::string pola):
    tipe(tipe), pola(std::move(pola)) {}
