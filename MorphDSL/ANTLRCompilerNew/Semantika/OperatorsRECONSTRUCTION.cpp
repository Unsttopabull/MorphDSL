#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::erodeNoCheck(const string& id1Str, const string& id2Str) const {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    cout << "::::::::::::" << endl;

    string m1 = getImageNameFromId(id2Str);
    cout << "<--  " << m1 << endl;

    morphInterface.erodeRECONSTRUCTION(m1, fFirst, fNew);

    cout << "---END" << endl;
}

void MorphDSLSemantics::erodeImpl(const Identifier& id1, const Identifier& id2) const {
    cout << "ERODE - RECONSTRUCTION MARKER" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    erodeNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::dilateNoCheck(const string& id1Str, const string& id2Str) const {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    string m1 = getImageNameFromId(id2Str);
    cout << "<--  " << m1 << endl;

    morphInterface.dilateRECONSTRUCTION(m1, fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::dilateImpl(const Identifier& id1, const Identifier& id2) const {
    cout << "DILATE - RECONSTRUCTION MARKER" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    dilateNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::openNoCheck(double number, const string& idStr) const {
    cout << "<--  " << number << endl;

    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.openRECONSTRUCTION_BOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::openImpl(double number, const Identifier& id) const {
    cout << "OPEN RECONSTRUCTION BOX" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    openNoCheck(number, id.getText());
}

void MorphDSLSemantics::closeNoCheck(double number, const string& idStr) const {
    cout << "<--  " << number << endl;

    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.closeRECONSTRUCTION_BOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::closeImpl(double number, const Identifier& id) const {
    cout << "CLOSE RECONSTRUCTION BOX" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    closeNoCheck(number, id.getText());
}
