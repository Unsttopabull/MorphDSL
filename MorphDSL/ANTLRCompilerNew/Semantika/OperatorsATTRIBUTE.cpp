#include "stdafx.h"
#include "../MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::openAttribute(const CommonTokenType* attributeName, double number, const CommonTokenType* id2) {
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

void MorphDSLParser::closeAttribute(const CommonTokenType* attributeName, double number, const CommonTokenType* id2) {
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