#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::openAttribute(const ParserToken* attributeName, double number, const ParserToken* id2) {
    cout << "OPEN - ATTRIBUTE" << endl;

    std::string fFirst = attributeName->getText();
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.open(fFirst, number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::closeAttribute(const ParserToken* attributeName, double number, const ParserToken* id2) {
    cout << "CLOSE - ATTRIBUTE" << endl;

    std::string fFirst = attributeName->getText();
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.close(fFirst, number, fLast, fNew);
    cout << "---END" << endl;
}