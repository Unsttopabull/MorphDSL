#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::openAttributeNoCheck(const string& attribute, const double number, const string& id2) const {
    logger->inputString(attribute);

    string fLast = getImageNameFromId(id2);
    logger->inputId(id2, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    //when 5 pics created

    morphInterface.open(attribute, number, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::openAttribute(const string& attributeName, const double number, const Identifier& id2) const {
    logger->startSection("OPEN - ATTRIBUTE");

    string id2Str = id2.getText();
    if (!checkVariableExist(id2Str)) {
        return;
    }

    openAttributeNoCheck(attributeName, number, id2Str);
}

void MorphDSLSemantics::closeAttributeNoCheck(const string& attribute, const double number, const string& id2) const {
    logger->inputString(attribute);

    string fLast = getImageNameFromId(id2);
    logger->inputId(id2, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    //when 5 pics created

    morphInterface.close(attribute, number, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::closeAttribute(const string& attributeName, const double number, const Identifier& id2) const {
    logger->startSection("CLOSE - ATTRIBUTE");

    string id2Str = id2.getText();
    if (!checkVariableExist(id2Str)) {
        return;
    }

    closeAttributeNoCheck(attributeName, number, id2Str);
}