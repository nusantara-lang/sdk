/*
 * ----------------------------------------------------------------------------
 * Project: Nusantara
 * Author: Fern Aerell
 * License: BSD 3-Clause License
 * Copyright (c) 2025, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "nusantara/support/diagnostic/diagnostic_category.h"
#include "nusantara/support/out_stream.h"
#include <magic_enum.hpp>

namespace nusantara {

OutStream& operator<<(OutStream& os, const DiagnosticCategory& diagnosticCategory)
{
    switch (diagnosticCategory)
    {
    case DiagnosticCategory::warning:
        return os << "\033[33m" << magic_enum::enum_name(diagnosticCategory) << "\033[0m"; // Yellow
    case DiagnosticCategory::error:
        return os << "\033[31m" << magic_enum::enum_name(diagnosticCategory) << "\033[0m"; // Red
    default:
        return os << magic_enum::enum_name(diagnosticCategory);
    }
}

} // namespace nusantara