#pragma once
#include <string>

namespace LPM_MorphDSL {
    using namespace std;

    class Spremenljivka {
        string slika;
        string brezKoncnice;
        string maskSlika;
        bool isTemp;

    public:

        Spremenljivka() {

        }

        Spremenljivka(string slika, string koncnica, bool isTemp) {
            brezKoncnice = slika;
            this->slika += slika + koncnica;
            this->isTemp = isTemp;
        }

        string getMask() const {
            return maskSlika;
        }

        void setMask(string slika) {
            maskSlika = slika;
        }

        string getBrezKoncnice() const {
            return brezKoncnice;
        }

        string getSlika() const {
            return slika;
        }
    };
}