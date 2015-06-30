#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::distanceTransformNoCheck(string idStr) {
    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.distanceTransform(fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::distanceTransformImpl(const Identifier* id) {
    cout << "DISTANCE TRANSFORM" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    distanceTransformNoCheck(id->getText());
}