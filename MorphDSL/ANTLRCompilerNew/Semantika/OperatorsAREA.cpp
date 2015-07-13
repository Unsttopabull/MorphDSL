#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::openAreaNoCheck(const double number, const string& id) const {
    logger->inputValue(number);

    string fLast = getImageNameFromId(id);
    logger->inputId(id, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    //when 5 pics created
    // d = open(AREA, 250, c)
    // morphInterface.openAREA(250, "maribor1.bmp", "maribor2.bmp");

    morphInterface.openAREA(number, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::openArea(const double number, const Identifier& id) const {
    logger->startSection("OPENAREA");

    if (!checkVariableExist(id)) {
        return;
    }

    openAreaNoCheck(number, id.getText());
}

void MorphDSLSemantics::closeAreaNoCheck(const double number, const string& id) const {
    logger->inputValue(number);

    string fLast = getImageNameFromId(id);
    logger->inputId(zadnjaSpremenljivka, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    morphInterface.closeAREA(number, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::closeArea(const double number, const Identifier& id) const {
    logger->startSection("CLOSEAREA");

    closeAreaNoCheck(number, id.getText());
}