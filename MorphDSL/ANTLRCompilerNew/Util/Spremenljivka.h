#pragma once
#include <string>

namespace LPM_MorphDSL {

    struct Spremenljivka {
        std::string slika;
        std::string brezKoncnice;

        Spremenljivka() {

        }

        Spremenljivka(std::string slika, std::string koncnica) {
            brezKoncnice = slika;
            this->slika += slika + koncnica;
        }
    };
}