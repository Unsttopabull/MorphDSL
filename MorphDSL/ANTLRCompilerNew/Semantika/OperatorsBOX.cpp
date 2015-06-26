#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::erodeBoxNoCheck(double number, string idStr) {
    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created

    morphInterface.erodeBOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::erodeBoxImpl(double number, const ParserToken* id) {
    cout << "ERODEBOX: " << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    erodeBoxNoCheck(number, id->getText());
}

void MorphDSLSemantics::dilateBoxNoCheck(double number, string idStr) {
    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created

    morphInterface.dilateBOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::dilateBoxImpl(double number, const ParserToken* id) {
    cout << "DILATEBOX: " << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    dilateBoxNoCheck(number, id->getText());
}

void MorphDSLSemantics::openBoxNoCheck(double number, string idStr) {
    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.openBOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::openBoxImpl(double number, const ParserToken* id) {
    cout << "OPENBOX: " << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    openBoxNoCheck(number, id->getText());
}

void MorphDSLSemantics::closeBoxNoCheck(double number, string idStr) {
    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created

    morphInterface.closeBOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::closeBoxImpl(double number, const ParserToken* id) {
    cout << "CLOSEBOX" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    closeBoxNoCheck(number, id->getText());
}
