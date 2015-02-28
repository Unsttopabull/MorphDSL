#include "stdafx.h"
#include "MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::erodeBoxImpl(double number, std::string id) {
    cout << "ERODEBOX: " << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << outputFigureName;
    fLast << number;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    //when 5 pics created
    morphInterface.erodeBOX(number, fLast.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::dilateBoxImpl(double number, std::string id) {

    cout << "DILATEBOX: " << endl;

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
    morphInterface.dilateBOX(number, fLast.str(), fNew.str());
    cout << "---END" << endl;

}

void MorphDSLParser::openBoxImpl(double number, std::string id) {
    cout << "OPENBOX: " << endl;

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
    morphInterface.openBOX(number, fLast.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::closeBoxImpl(double number, std::string id) {
    cout << "CLOSEBOX" << endl;

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
    morphInterface.closeBOX(number, fLast.str(), fNew.str());
    cout << "---END" << endl;
}
