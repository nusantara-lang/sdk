#include "nusal/tipe_token_data.h"

nusal::tipe_token_data::tipe_token_data(
    const tipe_token& tipe, std::string nama, std::string pola
):
    tipe(tipe),
    nama(std::move(nama)), pola(std::move(pola)) {}
