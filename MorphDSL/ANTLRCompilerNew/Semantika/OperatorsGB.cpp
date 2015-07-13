#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::tresholdImplNoCheck(const double number, const string& id) const {
    cout << "<-- " << number << endl;

    string fLast = getImageNameFromId(id);
    logger->inputId(id, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    logger->endSection();

    //when 5 pics created
    morphInterface.treshold(number, fLast, fNew);
}

void MorphDSLSemantics::tresholdImpl(const double number, const Identifier& id) const {
    logger->startSection("TRESHOLDING");

    if (!checkVariableExist(id)) {
        return;
    }

    tresholdImplNoCheck(number, id.getText());
}