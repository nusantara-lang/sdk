#include "lexer/tipe_token_data.h"

Lexer::TipeTokenData::TipeTokenData(const TipeToken& tipe, std::string pola):
    tipe(tipe), pola(std::move(pola)) {}
