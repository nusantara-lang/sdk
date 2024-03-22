#include "ncpp/string/i_stringfy.h"
#include <typeinfo>

std::string Ncpp::IStringfy::ubahKeString() const { return typeid(*this).name(); }
