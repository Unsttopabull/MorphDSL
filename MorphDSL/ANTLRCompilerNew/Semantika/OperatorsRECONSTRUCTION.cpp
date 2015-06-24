#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::erodeImpl(const ParserToken* id1, const ParserToken* id2) {
    cout << "ERODE - RECONSTRUCTION MARKER" << endl;

    string fFirst = getImageNameFromId(id1->getText());
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    cout << "::::::::::::" << endl;

    string m1 = getImageNameFromId(id2->getText());
    cout << "<--  " << m1 << endl;

    morphInterface.erodeRECONSTRUCTION(m1, fFirst, fNew);

    cout << "---END" << endl;
}

void MorphDSLSemantics::dilateImpl(const ParserToken* id1, const ParserToken* id2) {
    cout << "DILATE - RECONSTRUCTION MARKER" << endl;

    string fFirst = getImageNameFromId(id1->getText());
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    string m1 = getImageNameFromId(id2->getText());
    cout << "<--  " << m1 << endl;

    morphInterface.dilateRECONSTRUCTION(m1, fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::openImpl(double number, const ParserToken* id) {
    cout << "OPEN RECONSTRUCTION BOX" << endl;

    string fLast = getImageNameFromId(id->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.openRECONSTRUCTION_BOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::closeImpl(double number, const ParserToken* id) {

    cout << "CLOSE RECONSTRUCTION BOX" << endl;

    string fLast = getImageNameFromId(id->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.closeRECONSTRUCTION_BOX(number, fLast, fNew);
    cout << "---END" << endl;
}
