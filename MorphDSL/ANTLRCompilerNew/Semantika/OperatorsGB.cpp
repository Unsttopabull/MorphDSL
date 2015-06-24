#include "stdafx.h"
#include "../MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::tresholdImplNoCheck(double number, std::string id) {
    string fLast = getImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    cout << "---END" << endl;

    //when 5 pics created
    morphInterface.treshold(number, fLast, fNew);
}

void MorphDSLParser::tresholdImpl(double number, const CommonTokenType* id) {
    cout << "TRESHOLDING" << endl;

    if (!checkVariablesExist(id)) {
        return;
    }

    tresholdImplNoCheck(number, id->getText());
}