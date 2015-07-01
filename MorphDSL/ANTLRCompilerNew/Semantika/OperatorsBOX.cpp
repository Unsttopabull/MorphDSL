#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::erodeBoxNoCheck(double number, const string& idStr) {
    cout << "<--  " << number << endl;

    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created

    morphInterface.erodeBOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::erodeBoxImpl(double number, const Identifier& id) {
    cout << "ERODEBOX: " << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    erodeBoxNoCheck(number, id.getText());
}

void MorphDSLSemantics::dilateBoxNoCheck(double number, const string& idStr) {
    cout << "<--  " << number << endl;

    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created

    morphInterface.dilateBOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::dilateBoxImpl(double number, const Identifier& id) {
    cout << "DILATEBOX: " << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    dilateBoxNoCheck(number, id.getText());
}

void MorphDSLSemantics::openBoxNoCheck(double number, const string& idStr) {
    cout << "<--  " << number << endl;

    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.openBOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::openBoxImpl(double number, const Identifier& id) {
    cout << "OPENBOX: " << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    openBoxNoCheck(number, id.getText());
}

void MorphDSLSemantics::closeBoxNoCheck(double number, const string& idStr) {
    cout << "<--  " << number << endl;

    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created

    morphInterface.closeBOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::closeBoxImpl(double number, const Identifier& id) {
    cout << "CLOSEBOX" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    closeBoxNoCheck(number, id.getText());
}
