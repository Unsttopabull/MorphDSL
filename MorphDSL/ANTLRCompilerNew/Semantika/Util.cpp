#include "stdafx.h"
#include "MorphDSLSemantics.h"
#include "../Util/Spremenljivka.h"

using namespace LPM_MorphDSL;
using namespace std;

bool MorphDSLSemantics::checkVariablesExist(std::string id1, std::string id2) {
    if (!checkVariableExist(id1)) {
        return false;
    }

    if (!checkVariableExist(id2)) {
        return false;
    }
    return true;
}

bool MorphDSLSemantics::checkVariableExist(std::string id) {
    if (imeSlikeZaSpremenljivko.find(id) == imeSlikeZaSpremenljivko.end()) {
        cout << "ERROR: Spremenljivka '" << id << "' ne obstaja." << endl;
        parser->set_failedflag(true);
        return false;
    }
    return true;
}

bool MorphDSLSemantics::checkVariablesExist(const ParserToken* id1, const ParserToken* id2) {
    if (!checkVariableExist(id1)) {
        return false;
    }

    if (!checkVariableExist(id2)) {
        return false;
    }
    return true;
}

bool MorphDSLSemantics::checkVariableExist(const ParserToken* id) {
    if (imeSlikeZaSpremenljivko.find(id->getText()) == imeSlikeZaSpremenljivko.end()) {
        cout << "ERROR: Spremenljivka '" << id->getText() << "' ne obstaja. (" << id->get_line() << ", " << id->getCharPositionInLine() << ")" << endl;
        parser->set_failedflag(true);
        return false;
    }
    return true;
}

std::string MorphDSLSemantics::getImageNameFromId(std::string id) {
    return imeSlikeZaSpremenljivko[id].slika;
}

Spremenljivka MorphDSLSemantics::getVariableFromId(std::string id) {
    return imeSlikeZaSpremenljivko[id];
}

std::string MorphDSLSemantics::getNewImageName(bool noExtension) {
    auto d = zadnjaSpremenljivka;
    Spremenljivka spr = imeSlikeZaSpremenljivko[zadnjaSpremenljivka];
    if (noExtension) {
        return spr.brezKoncnice;
    }
    return spr.slika;
}

std::string MorphDSLSemantics::getNewImageNameWtf() {
    Spremenljivka spr = imeSlikeZaSpremenljivko[zadnjaSpremenljivka];
    return spr.slika + ".wtf";
}

void MorphDSLSemantics::variableToFileName(std::string spremenljivka, bool isTemp) {
    stringstream fId;//create a stringstream
    fId << ".\\";
    fId << imeIzhodneSlike;
    fId << imageCounter++;

    imeSlikeZaSpremenljivko[spremenljivka] = Spremenljivka(fId.str(), ".bmp", isTemp);

    auto test = imeSlikeZaSpremenljivko[spremenljivka];
}

void MorphDSLSemantics::initNovaSpremenljivka(std::string novaSpr) {
    if (imeSlikeZaSpremenljivko.find(novaSpr) != imeSlikeZaSpremenljivko.end()) {
        return;
    }

    zadnjaSpremenljivka = novaSpr;
    variableToFileName(zadnjaSpremenljivka);
}

std::string MorphDSLSemantics::initInternalVariable(std::string spremenljivka) {
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

//void MorphDSLSemantics::clearTempSpremenljivke() {
//    for (std::pair<string, Spremenljivka> s : imeSlikeZaSpremenljivko) {
//        if (s.second.isTemp) {
//            imeSlikeZaSpremenljivko.erase(s.first);
//        }
//    }
//}

void MorphDSLSemantics::loadImpl(std::string imeSlike, std::string imeSpremenljivke) {
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
