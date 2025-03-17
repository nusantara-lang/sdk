/*
 * ----------------------------------------------------------------------------
 * Project: Nusantara
 * Author: Fern Aerell
 * License: BSD 3-Clause License
 * Copyright (c) 2025, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "nusantara/lexer/token/token.h"
#include "nusantara/support/out_stream.h"

namespace nusantara {

OutStream& operator<<(OutStream& os, const Token& token)
{
    os << token.line + 1 << ':' << token.column + 1 << " [" << token.type << "] " << token.lexeme;
    return os;
}

} // namespace nusantara