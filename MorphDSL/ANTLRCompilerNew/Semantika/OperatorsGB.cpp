#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::tresholdImplNoCheck(double number, std::string id) {
    string fLast = getImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    cout << "---END" << endl;

    //when 5 pics created
    morphInterface.treshold(number, fLast, fNew);
}

void MorphDSLSemantics::tresholdImpl(double number, const ParserToken* id) {
    cout << "TRESHOLDING" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    tresholdImplNoCheck(number, id->getText());
}