#include "stdafx.h"
#include "MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::tresholdImpl(double number, std::string id) {
    //cout<<convertLetterToNumber(ID2->getText()[0])<<endl;
    cout << "TRESHOLDING" << endl;

    string fLast = getNewImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    cout << "---END" << endl;

    //when 5 pics created
    morphInterface.treshold(number, fLast, fNew);
}