#pragma once
#include <string>

namespace LPM_MorphDSL {

    struct Spremenljivka {
        std::string slika;
        std::string brezKoncnice;
        bool isTemp;
        std::string tempOfVaraible; //TODO

        Spremenljivka() {

        }

        Spremenljivka(std::string slika, std::string koncnica, bool isTemp = false) {
            brezKoncnice = slika;
            this->slika += slika + koncnica;
            isTemp = false;
        }
    };
}