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

bool MorphDSLSemantics::checkVariablesExist(const Identifier* id1, const Identifier* id2) {
    if (!checkVariableExist(id1)) {
        return false;
    }

    if (!checkVariableExist(id2)) {
        return false;
    }
    return true;
}

bool MorphDSLSemantics::checkVariableExist(const Identifier* id) {
    if (imeSlikeZaSpremenljivko.find(id->getText()) == imeSlikeZaSpremenljivko.end()) {
        cout << "ERROR: Spremenljivka '" << id->getText() << "' ne obstaja. (" << id->getToken()->get_line() << ", " << id->getToken()->getCharPositionInLine() << ")" << endl;
        parser->set_failedflag(true);
        return false;
    }
    return true;
}

std::string MorphDSLSemantics::getImageNameFromId(std::string id, SubIdentifier sub) {
    Spremenljivka spr = imeSlikeZaSpremenljivko[id];

    switch (sub) {
        case NONE:
            return spr.getSlika();
        case MASK:
            return spr.getMask();
        case SET:
        case ATTRIBUTE:
        case OKROGLOST:
        case VOLUMENT:
        default:
            return spr.getSlika();
    }
}

std::string MorphDSLSemantics::getImageNameFromId(Identifier* id) {
    return getImageNameFromId(id->getText(), id->getSubId());
}

Spremenljivka MorphDSLSemantics::getVariableFromId(std::string id) {
    return imeSlikeZaSpremenljivko[id];
}

std::string MorphDSLSemantics::getNewImageName(bool noExtension) {
    Spremenljivka spr = imeSlikeZaSpremenljivko[zadnjaSpremenljivka];
    if (noExtension) {
        return spr.getBrezKoncnice();
    }
    return spr.getSlika();
}

std::string MorphDSLSemantics::getNewImageNameWtf() {
    Spremenljivka spr = imeSlikeZaSpremenljivko[zadnjaSpremenljivka];
    return spr.getSlika() + ".wtf";
}

void MorphDSLSemantics::variableToFileName(std::string spremenljivka, bool isTemp) {
    stringstream fId;
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

    predZadnjaSpremenljivka = zadnjaSpremenljivka;
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

