#include "stdafx.h"
#include "../MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::distanceTransformImpl(std::string id) {
    cout << "DISTANCE TRANSFORM" << endl;

    string fLast = getImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.distanceTransform(fLast, fNew);
    cout << "---END" << endl;
}