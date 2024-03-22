#pragma once

#include "ncpp/string/i_stringfy.h"
#include <typeinfo>

std::string Ncpp::IStringfy::ubahKeString() { return typeid(*this).name(); }
