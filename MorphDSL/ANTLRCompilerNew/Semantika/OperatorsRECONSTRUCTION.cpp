#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::erodeNoCheck(string id1Str, string id2Str) {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    cout << "::::::::::::" << endl;

    string m1 = getImageNameFromId(id2Str);
    cout << "<--  " << m1 << endl;

    morphInterface.erodeRECONSTRUCTION(m1, fFirst, fNew);

    cout << "---END" << endl;
}

void MorphDSLSemantics::erodeImpl(const Identifier* id1, const Identifier* id2) {
    cout << "ERODE - RECONSTRUCTION MARKER" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    erodeNoCheck(id1->getText(), id2->getText());
}

void MorphDSLSemantics::dilateNoCheck(string id1Str, string id2Str) {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    string m1 = getImageNameFromId(id2Str);
    cout << "<--  " << m1 << endl;

    morphInterface.dilateRECONSTRUCTION(m1, fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::dilateImpl(const Identifier* id1, const Identifier* id2) {
    cout << "DILATE - RECONSTRUCTION MARKER" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    dilateNoCheck(id1->getText(), id2->getText());
}

void MorphDSLSemantics::openNoCheck(double number, string idStr) {
    cout << "<--  " << number << endl;

    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.openRECONSTRUCTION_BOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::openImpl(double number, const Identifier* id) {
    cout << "OPEN RECONSTRUCTION BOX" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    openNoCheck(number, id->getText());
}

void MorphDSLSemantics::closeNoCheck(double number, string idStr) {
    cout << "<--  " << number << endl;

    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.closeRECONSTRUCTION_BOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::closeImpl(double number, const Identifier* id) {
    cout << "CLOSE RECONSTRUCTION BOX" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    closeNoCheck(number, id->getText());
}
