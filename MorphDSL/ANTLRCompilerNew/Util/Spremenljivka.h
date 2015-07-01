#pragma once
#include <string>

namespace LPM_MorphDSL {
    using namespace std;

    class Spremenljivka {
        string ime;
        string slika;
        string brezKoncnice;
        string maskSlika;
        bool isTemp;
        string kategorija;

    public:

        Spremenljivka() {

        }

        Spremenljivka(string ime, string slika, string koncnica) {
            this->ime = ime;
            brezKoncnice = slika;
            this->slika += slika + koncnica;
        }

        Spremenljivka(string ime, string slika, string koncnica, string kateg) {
            this->ime = ime;
            brezKoncnice = slika;
            this->slika += slika + koncnica;

            if (!kateg.empty()) {
                kategorija = kateg;
                isTemp = true;
            }
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

        string getCategory() const {
            return kategorija;
        }

        bool isTemporary() const {
            return this->isTemp;
        }

        string getText() const {
            return ime;
        }
    };
}