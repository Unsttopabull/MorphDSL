#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;

MorphDSLSemantics::MorphDSLSemantics(MorphDSLParser* p, ILogger* log) {
    imeIzhodneSlike = "";
    imageCounter = 1;
    tempCnt = 0;

    parser = p;
    logger = log;
}

void MorphDSLSemantics::loadImpl(string imeSlike, string imeSpremenljivke) {
    int firstLetter = imeSlike.find_last_of("/\\") + 1;

    logger->logLine("LOADING");
    logger->inputString(imeSlike.substr(1, imeSlike.length() - 2));
    
    int length = imeSlike.find_last_of(".") - firstLetter;
    imeIzhodneSlike = imeSlike.substr(firstLetter, length);

    //cout << outputFigureName << endl;

    initNovaSpremenljivka(zadnjaSpremenljivka);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);
    logger->endSection();

    imeSlike = imeSlike.substr(1, imeSlike.length() - 2);

    morphInterface.LoadImg(imeSlike, img);
    morphInterface.StoreImg(fNew, img);
}

void MorphDSLSemantics::setZadnjaSpremenljivka(const string& spr) {
    predZadnjaSpremenljivka = zadnjaSpremenljivka;
    zadnjaSpremenljivka = spr;
}

string MorphDSLSemantics::getZadnjaSpremenljivka() const {
    return zadnjaSpremenljivka;
}

void MorphDSLSemantics::insertToVect(pair<string, vector<double>> pair) {
    vect.insert(vect.begin(), pair);
}
