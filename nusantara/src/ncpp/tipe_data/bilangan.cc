#include "ncpp/tipe_data/bilangan.h"

Ncpp::Bilangan::Bilangan(const std::string& nilai): ITipeData<std::variant<int, double>>({}) {}

Ncpp::Bilangan::Bilangan(const int& nilai): ITipeData<std::variant<int, double>>(nilai) {}

Ncpp::Bilangan::Bilangan(const double& nilai): ITipeData<std::variant<int, double>>(nilai) {}