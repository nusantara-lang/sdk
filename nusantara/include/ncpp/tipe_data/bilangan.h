#pragma once

#include "ncpp/tipe_data/i_tipe_data.h"
#include <string>
#include <variant>

namespace Ncpp {

    class Bilangan: public ITipeData<std::variant<int, double>> {
        public:
            explicit Bilangan(const std::string& nilai);
            explicit Bilangan(const int& nilai);
            explicit Bilangan(const double& nilai);
        private:
        protected:
    };

}