#include "lexer/tipe_token.h"

Lexer::TipeToken::Nama::Nama(std::string nilai): nilai(std::move(nilai)) {}

Lexer::TipeToken::Pola::Pola(std::string nilai): nilai(std::move(nilai)) {}

Lexer::TipeToken::TipeToken(
    const Nama& nama, const Pola& pola, const bool& skip
):
    nama(nama.nilai),
    pola(pola.nilai), 
    skip(skip) 
{}

std::string Lexer::TipeToken::ubahKeString() const { return nama; }

const std::string& Lexer::TipeToken::getNama() const {
    return this->nama;
}

const std::string& Lexer::TipeToken::getPola() const {
    return this->pola;
}

const bool& Lexer::TipeToken::isSkip() const {
    return this->skip;
}

