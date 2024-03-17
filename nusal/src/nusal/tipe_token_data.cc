#include "nusal/tipe_token_data.h"

nusal::tipe_token_data::tipe_token_data(
    const tipe_token& tipe, std::string pola
):
    tipe(tipe),
    pola(std::move(pola)) {}
