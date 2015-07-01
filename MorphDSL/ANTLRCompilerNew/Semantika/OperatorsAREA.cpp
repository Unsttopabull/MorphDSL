#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::openAreaNoCheck(const double number, const string& id) const {
    cout << "<--  " << number << endl;

    string fLast = getImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    // d = open(AREA, 250, c)
    // morphInterface.openAREA(250, "maribor1.bmp", "maribor2.bmp");

    morphInterface.openAREA(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::openArea(const double number, const Identifier& id) const {
    cout << "OPENAREA" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    openAreaNoCheck(number, id.getText());
}

void MorphDSLSemantics::closeAreaNoCheck(const double number, const string& id) const {
    cout << "<--  " << number << endl;

    string fLast = getImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.closeAREA(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::closeArea(const double number, const Identifier& id) const {
    cout << "CLOSEAREA" << endl;

    closeAreaNoCheck(number, id.getText());
}