#include "stdafx.h"
#include "MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::openAttribute(std::string id1, double number, std::string id2) {
    cout << "OPEN - ATTRIBUTE" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << id1;
    cout << "<--  " << fFirst.str() << endl;

    string fLast = getNewImageNameFromId(id2);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.open(fFirst.str(), number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::closeAttribute(std::string id1, double number, std::string id2) {

    cout << "CLOSE - ATTRIBUTE" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << id1;
    cout << "<--  " << fFirst.str() << endl;

    string fLast = getNewImageNameFromId(id2);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.close(fFirst.str(), number, fLast, fNew);
    cout << "---END" << endl;
}