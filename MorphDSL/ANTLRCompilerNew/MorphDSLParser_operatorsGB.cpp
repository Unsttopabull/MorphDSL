#include "stdafx.h"
#include "MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::tresholdImpl(double number, std::string id) {
    //cout<<convertLetterToNumber(ID2->getText()[0])<<endl;
    cout << "TRESHOLDING" << endl;

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

    cout << "---END" << endl;

    //when 5 pics created
    morphInterface.treshold(number, fLast.str(), fNew.str());
}