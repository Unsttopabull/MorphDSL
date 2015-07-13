#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::distanceTransformNoCheck(const string& id) const {
    string fLast = getImageNameFromId(id);
    logger->inputId(id, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    morphInterface.distanceTransform(fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::distanceTransformImpl(const Identifier& id) const {
    logger->startSection("DISTANCE TRANSFORM");

    if (!checkVariableExist(id)) {
        return;
    }

    distanceTransformNoCheck(id.getText());
}