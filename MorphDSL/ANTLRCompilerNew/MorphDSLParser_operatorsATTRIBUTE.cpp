#include "stdafx.h"
#include "MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::openAttribute(std::string id1, double number, std::string id2) {
    cout << "OPEN - ATTRIBUTE" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << id1;
    cout << "<--  " << fFirst.str() << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << outputFigureName;
    fLast << id2[0] - 96;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    //when 5 pics created
    morphInterface.open(fFirst.str(), number, fLast.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::closeAttribute(std::string id1, double number, std::string id2) {

    cout << "CLOSE - ATTRIBUTE" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << id1;
    cout << "<--  " << fFirst.str() << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << outputFigureName;
    fLast << id2[0] - 96;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    //when 5 pics created
    morphInterface.close(fFirst.str(), number, fLast.str(), fNew.str());
    cout << "---END" << endl;
}