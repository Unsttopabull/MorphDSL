#include "stdafx.h"
#include "../MorphDSLParser.hpp"
#include "../Util/Spremenljivka.h"

using namespace LPM_MorphDSL;
using namespace std;

int MorphDSLParser::toInt(const CommonTokenType* token) {
    int number;
    istringstream(token->getText()) >> number;

    return number;
}

double MorphDSLParser::toDouble(const CommonTokenType* token) {
    double number;
    istringstream(token->getText()) >> number;

    return number;
}

std::string MorphDSLParser::getImageNameFromId(std::string id) {
    return imeSlikeZaSpremenljivko[id].slika;
}

std::string MorphDSLParser::getNewImageName(bool noExtension) {
    auto d = zadnjaSpremenljivka;
    Spremenljivka spr = imeSlikeZaSpremenljivko[zadnjaSpremenljivka];
    if (noExtension) {
        return spr.brezKoncnice;
    }
    return spr.slika;
}

std::string MorphDSLParser::getNewImageNameWtf() {
    Spremenljivka spr = imeSlikeZaSpremenljivko[zadnjaSpremenljivka];
    return spr.slika + ".wtf";
}

void MorphDSLParser::spremenljivkaVImeDatoteke(std::string spremenljivka) {
    stringstream fId;//create a stringstream
    fId << ".\\";
    fId << imeIzhodneSlike;
    fId << imageCounter++;

    imeSlikeZaSpremenljivko[spremenljivka] = Spremenljivka(fId.str(), ".bmp");

    auto test = imeSlikeZaSpremenljivko[spremenljivka];
}

void MorphDSLParser::initNovaSpremenljivka(std::string novaSpr) {
    if (imeSlikeZaSpremenljivko.find(novaSpr) != imeSlikeZaSpremenljivko.end()) {
        return;
    }

    zadnjaSpremenljivka = novaSpr;
    spremenljivkaVImeDatoteke(zadnjaSpremenljivka);
}

void MorphDSLParser::loadImpl(std::string imeSlike, std::string imeSpremenljivke) {
    cout << "LOADING" << endl;
    cout << "<--  " << imeSlike << endl;

    int firstLetter = imeSlike.find_last_of("/\\") + 1;
    int length = imeSlike.find_last_of(".") - firstLetter;
    imeIzhodneSlike = imeSlike.substr(firstLetter, length);

    //cout << outputFigureName << endl;

    initNovaSpremenljivka(zadnjaSpremenljivka);

    std::string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    cout << "---END" << endl;

    morphInterface.LoadImg(imeSlike, img);
    morphInterface.StoreImg(fNew, img);
}