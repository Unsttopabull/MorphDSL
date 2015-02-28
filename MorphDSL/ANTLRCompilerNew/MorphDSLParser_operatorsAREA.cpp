#include "stdafx.h"
#include "MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::openArea(double number, std::string id) {
    cout << "OPENAREA" << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << outputFigureName;
    fLast << id[0] - 96;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    //when 5 pics created
    // d = open(AREA, 250, c)
    // morphInterface.openAREA(250, "maribor1.bmp", "maribor2.bmp");
    morphInterface.openAREA(number, fLast.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::closeArea(double number, std::string id) {
    cout << "CLOSEAREA" << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << outputFigureName;
    fLast << id[0] - 96;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    morphInterface.closeAREA(number, fLast.str(), fNew.str());
    cout << "---END" << endl;
}