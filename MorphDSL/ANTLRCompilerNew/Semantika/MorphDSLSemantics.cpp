#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;

MorphDSLSemantics::MorphDSLSemantics(MorphDSLParser* p) {
    imeIzhodneSlike = "";
    imageCounter = 1;
    tempCnt = 0;

    parser = p;
}

void MorphDSLSemantics::loadImpl(string imeSlike, string imeSpremenljivke) {
    cout << "LOADING" << endl;
    cout << "<--  " << imeSlike << endl;

    int firstLetter = imeSlike.find_last_of("/\\") + 1;
    int length = imeSlike.find_last_of(".") - firstLetter;
    imeIzhodneSlike = imeSlike.substr(firstLetter, length);

    //cout << outputFigureName << endl;

    initNovaSpremenljivka(zadnjaSpremenljivka);

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    cout << "---END" << endl;

    imeSlike = imeSlike.substr(1, imeSlike.length() - 2);

    morphInterface.LoadImg(imeSlike, img);
    morphInterface.StoreImg(fNew, img);
}
