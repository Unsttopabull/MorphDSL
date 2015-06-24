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

bool MorphDSLParser::checkVariablesExist(std::string id1, std::string id2) {
    if (imeSlikeZaSpremenljivko.find(id1) == imeSlikeZaSpremenljivko.end()) {
        cout << "ERROR: Spremenljivka '" << id1 << "' ne obstaja." << endl;
        this->set_failedflag(true);
        return false;
    }

    if (imeSlikeZaSpremenljivko.find(id2) == imeSlikeZaSpremenljivko.end()) {
        cout << "ERROR: Spremenljivka '" << id2 << "' ne obstaja." << endl;
        this->set_failedflag(true);
        return false;
    }
    return true;
}

bool MorphDSLParser::checkVariablesExist(std::string id) {
    if (imeSlikeZaSpremenljivko.find(id) == imeSlikeZaSpremenljivko.end()) {
        cout << "ERROR: Spremenljivka '" << id << "' ne obstaja." << endl;
        this->set_failedflag(true);
        return false;
    }
    return true;
}

bool MorphDSLParser::checkVariablesExist(const CommonTokenType* id1, const CommonTokenType* id2) {
    if (imeSlikeZaSpremenljivko.find(id1->getText()) == imeSlikeZaSpremenljivko.end()) {
        cout << "ERROR: Spremenljivka '" << id1->getText() << "' ne obstaja. (" << id1->get_line() << ", " << id1->getCharPositionInLine() << ")" << endl;
        this->set_failedflag(true);
        return false;
    }

    if (imeSlikeZaSpremenljivko.find(id2->getText()) == imeSlikeZaSpremenljivko.end()) {
        cout << "ERROR: Spremenljivka '" << id2->getText() << "' ne obstaja. (" << id2->get_line() << ", " << id2->getCharPositionInLine() << ")" << endl;
        this->set_failedflag(true);
        return false;
    }
    return true;
}

bool MorphDSLParser::checkVariablesExist(const CommonTokenType* id) {
    if (imeSlikeZaSpremenljivko.find(id->getText()) == imeSlikeZaSpremenljivko.end()) {
        cout << "ERROR: Spremenljivka '" << id->getText() << "' ne obstaja. (" << id->get_line() << ", " << id->getCharPositionInLine() << ")" << endl;
        this->set_failedflag(true);
        return false;
    }
    return true;
}

std::string MorphDSLParser::getImageNameFromId(std::string id) {
    return imeSlikeZaSpremenljivko[id].slika;
}

Spremenljivka MorphDSLParser::getVariableFromId(std::string id) {
    return imeSlikeZaSpremenljivko[id];
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

void MorphDSLParser::variableToFileName(std::string spremenljivka, bool isTemp) {
    stringstream fId;//create a stringstream
    fId << ".\\";
    fId << imeIzhodneSlike;
    fId << imageCounter++;

    imeSlikeZaSpremenljivko[spremenljivka] = Spremenljivka(fId.str(), ".bmp", isTemp);

    auto test = imeSlikeZaSpremenljivko[spremenljivka];
}

void MorphDSLParser::initNovaSpremenljivka(std::string novaSpr) {
    if (imeSlikeZaSpremenljivko.find(novaSpr) != imeSlikeZaSpremenljivko.end()) {
        return;
    }

    zadnjaSpremenljivka = novaSpr;
    variableToFileName(zadnjaSpremenljivka);
}

std::string MorphDSLParser::initInternalVariable(std::string spremenljivka) {
    stringstream sprStream;
    sprStream << "$" << spremenljivka << tempCnt++;

    string spr = sprStream.str();

    if (imeSlikeZaSpremenljivko.find(spr) != imeSlikeZaSpremenljivko.end()) {
        return initInternalVariable(spremenljivka);
    }

    zadnjaSpremenljivka = spr;
    variableToFileName(spr, true);

    return spr;
}

//void MorphDSLParser::clearTempSpremenljivke() {
//    for (std::pair<string, Spremenljivka> s : imeSlikeZaSpremenljivko) {
//        if (s.second.isTemp) {
//            imeSlikeZaSpremenljivko.erase(s.first);
//        }
//    }
//}

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
