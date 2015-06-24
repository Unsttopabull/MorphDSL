#include "stdafx.h"
#include "../MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::erodeImpl(const CommonTokenType* id1, const CommonTokenType* id2) {
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

void MorphDSLParser::dilateImpl(const CommonTokenType* id1, const CommonTokenType* id2) {
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

void MorphDSLParser::openImpl(double number, const CommonTokenType* id) {
    cout << "OPEN RECONSTRUCTION BOX" << endl;

    string fLast = getImageNameFromId(id->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.openRECONSTRUCTION_BOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::closeImpl(double number, const CommonTokenType* id) {

    cout << "CLOSE RECONSTRUCTION BOX" << endl;

    string fLast = getImageNameFromId(id->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.closeRECONSTRUCTION_BOX(number, fLast, fNew);
    cout << "---END" << endl;
}
