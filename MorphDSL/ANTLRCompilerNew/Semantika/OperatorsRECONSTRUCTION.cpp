#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::erodeNoCheck(const string& id1, const string& id2) const {
    string fFirst = getImageNameFromId(id1);
    logger->inputId(id1, fFirst);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    cout << "::::::::::::" << endl;

    string m1 = getImageNameFromId(id2);
    logger->inputId(id2, m1);

    morphInterface.erodeRECONSTRUCTION(m1, fFirst, fNew);

    logger->endSection();
}

void MorphDSLSemantics::erodeImpl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("ERODE - RECONSTRUCTION MARKER");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    erodeNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::dilateNoCheck(const string& id1, const string& id2) const {
    string fFirst = getImageNameFromId(id1);
    logger->inputId(id1, fFirst);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    string m1 = getImageNameFromId(id2);
    logger->inputId(id2, m1);

    morphInterface.dilateRECONSTRUCTION(m1, fFirst, fNew);
    logger->endSection();
}

void MorphDSLSemantics::dilateImpl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("DILATE - RECONSTRUCTION MARKER");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    dilateNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::openNoCheck(double number, const string& id) const {
    logger->inputValue(number);

    string fLast = getImageNameFromId(id);
    logger->inputId(id, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    morphInterface.openRECONSTRUCTION_BOX(number, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::openImpl(double number, const Identifier& id) const {
    logger->startSection("OPEN RECONSTRUCTION BOX");

    if (!checkVariableExist(id)) {
        return;
    }

    openNoCheck(number, id.getText());
}

void MorphDSLSemantics::closeNoCheck(double number, const string& id) const {
    logger->inputValue(number);

    string fLast = getImageNameFromId(id);
    logger->inputId(id, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    morphInterface.closeRECONSTRUCTION_BOX(number, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::closeImpl(double number, const Identifier& id) const {
    logger->startSection("CLOSE RECONSTRUCTION BOX");

    if (!checkVariableExist(id)) {
        return;
    }

    closeNoCheck(number, id.getText());
}
