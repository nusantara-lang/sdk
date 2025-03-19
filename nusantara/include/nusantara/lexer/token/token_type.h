/*
 * ----------------------------------------------------------------------------
 * Project: Nusantara
 * Author: Fern Aerell
 * License: BSD 3-Clause License
 * Copyright (c) 2025, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef NUSANTARA_LEXER_TOKEN_TOKEN_TYPE_H
#define NUSANTARA_LEXER_TOKEN_TOKEN_TYPE_H

#include "nusantara/support/out_stream.h"

namespace nusantara {

enum class TokenType
{
    // Parenthesis
    PAREN_OPEN,  // pattern: '('
    PAREN_CLOSE, // pattern: ')'

    // Separators
    COMMA, // pattern: ','

    // Data types
    KW_DT_NUM, // pattern: 'num'
    KW_DT_STR, // pattern: 'str'

    // Keywords
    KW_F,   // pattern: 'f'
    KW_USE, // pattern: 'use'

    // Literals
    LIT_NUM, // pattern: [0-9]+ ('.' [0-9]+)?
    LIT_STR, // pattern: ('\'' ~'\''* '\'' | '"' ~'"'* '"')

    // Other
    ID, // pattern: [a-zA-Z_][a-zA-Z0-9_]*

    // System
    UNKNOWN, // unknown
    NEOF,    // eof
};

OutStream& operator<<(OutStream& os, const TokenType& type);

} // namespace nusantara

#endif