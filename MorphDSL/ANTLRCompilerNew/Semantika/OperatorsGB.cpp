#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::tresholdImplNoCheck(const double number, const string& id) const {
    cout << "<-- " << number << endl;

    string fLast = getImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    cout << "---END" << endl;

    //when 5 pics created
    morphInterface.treshold(number, fLast, fNew);
}

void MorphDSLSemantics::tresholdImpl(const double number, const Identifier& id) const {
    cout << "TRESHOLDING" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    tresholdImplNoCheck(number, id.getText());
}