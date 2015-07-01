#include "stdafx.h"
#include "MorphDSLSemantics.h"
#include "../Util/Spremenljivka.h"

using namespace LPM_MorphDSL;
using namespace std;

bool MorphDSLSemantics::checkVariablesExist(const string& id1, const string& id2) const {
    if (!checkVariableExist(id1)) {
        return false;
    }

    if (!checkVariableExist(id2)) {
        return false;
    }
    return true;
}

bool MorphDSLSemantics::checkVariableExist(const string& id) const {
    if (imeSlikeZaSpremenljivko.find(id) == imeSlikeZaSpremenljivko.end()) {
        cout << "ERROR: Spremenljivka '" << id << "' ne obstaja." << endl;
        parser->set_failedflag(true);
        return false;
    }
    return true;
}

bool MorphDSLSemantics::checkVariablesExist(const Identifier& id1, const Identifier& id2) const {
    if (!checkVariableExist(id1)) {
        return false;
    }

    if (!checkVariableExist(id2)) {
        return false;
    }
    return true;
}

bool MorphDSLSemantics::checkVariableExist(const Identifier& id) const {
    if (imeSlikeZaSpremenljivko.find(id.getText()) == imeSlikeZaSpremenljivko.end()) {
        cout << "ERROR: Spremenljivka '" << id.getText() << "' ne obstaja. (" << id.getToken()->get_line() << ", " << id.getToken()->getCharPositionInLine() << ")" << endl;
        parser->set_failedflag(true);
        return false;
    }
    return true;
}

string MorphDSLSemantics::getImageNameFromId(const string& id, SubIdentifier sub) const {
    Spremenljivka* spr = imeSlikeZaSpremenljivko.at(id);

    switch (sub) {
        case NONE:
            return spr->getSlika();
        case MASK:
            return spr->getMask();
        case SET:
        case ATTRIBUTE:
        case OKROGLOST:
        case VOLUMENT:
        default:
            return spr->getSlika();
    }
}

string MorphDSLSemantics::getImageNameFromId(const Identifier& id) const {
    return getImageNameFromId(id.getText(), id.getSubId());
}

Spremenljivka* MorphDSLSemantics::getVariableFromId(const string& id) const {
    return imeSlikeZaSpremenljivko.at(id);
}

string MorphDSLSemantics::getLastVariableImageName(bool noExtension) const {
    Spremenljivka* spr = imeSlikeZaSpremenljivko.at(zadnjaSpremenljivka);
    if (noExtension) {
        return spr->getBrezKoncnice();
    }
    return spr->getSlika();
}

string MorphDSLSemantics::getLastVariableImageNameWtf() const {
    Spremenljivka* spr = imeSlikeZaSpremenljivko.at(zadnjaSpremenljivka);
    return spr->getSlika() + ".wtf";
}

void MorphDSLSemantics::variableToFileName(const string& spremenljivka, const string& kategorija) {
    stringstream fId;
    fId << ".\\";
    fId << imeIzhodneSlike;
    fId << imageCounter++;

    Spremenljivka* spr = new Spremenljivka(spremenljivka, fId.str(), ".bmp", kategorija);
    imeSlikeZaSpremenljivko[spremenljivka] = spr;

    if (!kategorija.empty()) {
        if (tempSpremenljivke.find(kategorija) == tempSpremenljivke.end()) {
            tempSpremenljivke[kategorija] = vector <Spremenljivka*>();
        }
        tempSpremenljivke[kategorija].push_back(spr);
    }
}

void MorphDSLSemantics::initNovaSpremenljivka(const string& novaSpr) {
    if (imeSlikeZaSpremenljivko.find(novaSpr) != imeSlikeZaSpremenljivko.end()) {
        return;
    }

    zadnjaSpremenljivka = novaSpr;
    variableToFileName(zadnjaSpremenljivka, "");
}

string MorphDSLSemantics::initInternalVariable(const string& spremenljivka, const string& kategorija)  {
    stringstream sprStream;
    sprStream << "$" << spremenljivka << tempCnt++;

    string spr = sprStream.str();

    if (imeSlikeZaSpremenljivko.find(spr) != imeSlikeZaSpremenljivko.end()) {
        return initInternalVariable(spremenljivka, kategorija);
    }

    predZadnjaSpremenljivka = zadnjaSpremenljivka;
    zadnjaSpremenljivka = spr;
    variableToFileName(spr, kategorija);

    return spr;
}

void MorphDSLSemantics::clearTempVariablesCategory(const string& kategorija) {
    auto iter = tempSpremenljivke.find(kategorija);
    if (iter == tempSpremenljivke.end()) {
        return;
    }

    for (vector<Spremenljivka*>::const_iterator it = iter->second.begin(); it != iter->second.end(); ++it){
        imeSlikeZaSpremenljivko.erase((*it)->getText());
    }

    tempSpremenljivke.erase(kategorija);
}
