#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::distanceTransformNoCheck(const string& idStr) const {
    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.distanceTransform(fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::distanceTransformImpl(const Identifier& id) const {
    cout << "DISTANCE TRANSFORM" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    distanceTransformNoCheck(id.getText());
}