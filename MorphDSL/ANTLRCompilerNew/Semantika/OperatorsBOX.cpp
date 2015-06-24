#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::erodeBoxImpl(double number, const ParserToken* id) {
    cout << "ERODEBOX: " << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << imeIzhodneSlike;
    fLast << number;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.erodeBOX(number, fLast.str(), fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::dilateBoxImpl(double number, const ParserToken* id) {

    cout << "DILATEBOX: " << endl;

    string fLast = getImageNameFromId(id->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.dilateBOX(number, fLast, fNew);
    cout << "---END" << endl;

}

void MorphDSLSemantics::openBoxImpl(double number, const ParserToken* id) {
    cout << "OPENBOX: " << endl;

    string fLast = getImageNameFromId(id->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.openBOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::closeBoxImpl(double number, const ParserToken* id) {
    cout << "CLOSEBOX" << endl;

    string fLast = getImageNameFromId(id->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.closeBOX(number, fLast, fNew);
    cout << "---END" << endl;
}
