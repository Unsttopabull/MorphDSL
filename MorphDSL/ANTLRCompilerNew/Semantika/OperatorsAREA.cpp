#include "stdafx.h"
#include "../MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::openAreaNoCheck(double number, std::string id) {
    string fLast = getImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    // d = open(AREA, 250, c)
    // morphInterface.openAREA(250, "maribor1.bmp", "maribor2.bmp");

    morphInterface.openAREA(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::openArea(double number, const CommonTokenType* id) {
    cout << "OPENAREA" << endl;

    if (!checkVariablesExist(id)) {
        return;
    }

    openAreaNoCheck(number, id->getText());
}

void MorphDSLParser::closeAreaNoCheck(double number, std::string id) {
    string fLast = getImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.closeAREA(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::closeArea(double number, const CommonTokenType* id) {
    cout << "CLOSEAREA" << endl;

    closeAreaNoCheck(number, id->getText());
}