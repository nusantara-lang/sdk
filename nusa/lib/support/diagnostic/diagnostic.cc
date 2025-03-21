/*
 * ----------------------------------------------------------------------------
 * Project: Nusa
 * Author: Fern Aerell
 * License: BSD 3-Clause License
 * Copyright (c) 2025, The Nusa Project Authors
 * ----------------------------------------------------------------------------
 */

#include "nusa/support/diagnostic/diagnostic.h"
#include "nusa/support/out_stream.h"
#include <algorithm>
#include <cstddef>
#include <string>

namespace nusa {

OutStream& operator<<(OutStream& os, const Diagnostic& diagnostic)
{
    if (diagnostic.charStream)
    {
        os << (diagnostic.charStream->path() != nullptr ? diagnostic.charStream->path() : "<unknown>");
        if (!diagnostic.locations.empty())
            os << ':';
    }
    else
        os << "<unknown>:";

    if (!diagnostic.locations.empty())
    {
        const auto& loc = diagnostic.locations.front();
        os << loc.line + 1 << ':' << loc.column + 1;
    }

    os << ' ' << diagnostic.module << ' ' << diagnostic.category << ": ";

    if (diagnostic.charStream && !diagnostic.locations.empty())
    {
        os << "\n\n";
        for (const auto& loc : diagnostic.locations)
        {
            std::string prefix = std::to_string(loc.line + 1) + "| ";
            os << prefix << diagnostic.charStream->lineView(loc.line) << '\n' << std::string(prefix.size() + loc.column, ' ') << std::string(std::max((size_t)1, loc.size), '^') << '\n';
        }
    }

    return os << diagnostic.message;
}

} // namespace nusa