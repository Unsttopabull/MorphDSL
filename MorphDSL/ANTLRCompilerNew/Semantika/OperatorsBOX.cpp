#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::erodeBoxNoCheck(double number, const string& id) const {
    logger->inputValue(number);

    string fLast = getImageNameFromId(id);
    logger->inputId(id, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    //when 5 pics created

    morphInterface.erodeBOX(number, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::erodeBoxImpl(double number, const Identifier& id) const {
    logger->startSection("ERODEBOX: ");

    if (!checkVariableExist(id)) {
        return;
    }

    erodeBoxNoCheck(number, id.getText());
}

void MorphDSLSemantics::dilateBoxNoCheck(double number, const string& id) const {
    logger->inputValue(number);

    string fLast = getImageNameFromId(id);
    logger->inputId(id, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    //when 5 pics created

    morphInterface.dilateBOX(number, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::dilateBoxImpl(double number, const Identifier& id) const {
    logger->startSection("DILATEBOX: ");

    if (!checkVariableExist(id)) {
        return;
    }

    dilateBoxNoCheck(number, id.getText());
}

void MorphDSLSemantics::openBoxNoCheck(double number, const string& id) const {
    logger->inputValue(number);

    string fLast = getImageNameFromId(id);
    logger->inputId(id, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    //when 5 pics created
    morphInterface.openBOX(number, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::openBoxImpl(double number, const Identifier& id) const {
    logger->startSection("OPENBOX: ");

    if (!checkVariableExist(id)) {
        return;
    }

    openBoxNoCheck(number, id.getText());
}

void MorphDSLSemantics::closeBoxNoCheck(double number, const string& id) const {
    logger->inputValue(number);

    string fLast = getImageNameFromId(id);
    logger->inputId(id, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    //when 5 pics created

    morphInterface.closeBOX(number, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::closeBoxImpl(double number, const Identifier& id) const {
    logger->startSection("CLOSEBOX");

    if (!checkVariableExist(id)) {
        return;
    }

    closeBoxNoCheck(number, id.getText());
}
