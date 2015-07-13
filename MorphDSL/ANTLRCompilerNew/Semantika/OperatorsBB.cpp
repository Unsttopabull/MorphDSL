#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::complementNoCheck(const string& idStr) const {
    string fLast = getImageNameFromId(idStr);
    logger->inputId(idStr, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    morphInterface.complement(fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::complementImpl(const Identifier& id) const {
    logger->startSection("COMPLEMENT");

    if (!checkVariableExist(id)) {
        return;
    }

    complementNoCheck(id.getText());
}

void MorphDSLSemantics::unionNoCheck(const string& id1, const string& id2) const {
    string fFirst = getImageNameFromId(id1);
    logger->inputId(id1, fFirst);

    string fLast = getImageNameFromId(id2);
    logger->inputId(id2, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    morphInterface.unionBB(fFirst, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::unionImpl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("UNION");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    unionNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::intersectionNoCheck(const string& id1Str, const string& id2Str) const {
    string fFirst = getImageNameFromId(id1Str);
    logger->inputId(id1Str, fFirst);

    string fLast = getImageNameFromId(id2Str);
    logger->inputId(id2Str, fLast);

    std::string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    morphInterface.intersection(fFirst, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::intersectionImpl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("INTERSECTION");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    intersectionNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::withoutNoCheck(const string& id1, const string& id2) const {
    string fFirst = getImageNameFromId(id1);
    logger->inputId(id1, fFirst);

    string fLast = getImageNameFromId(id2);
    logger->inputId(id2, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    morphInterface.without(fFirst, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::withoutImpl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("WITHOUT");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    withoutNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::hitMissNoCheck(const string& id1, const string& id2) const {
    string fFirst = getImageNameFromId(id1);
    logger->inputId(id1, fFirst);

    string fLast = getImageNameFromId(id2);
    logger->inputId(id2, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    morphInterface.hitmiss(fFirst, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::hitMissImpl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("HITMISS");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    hitMissNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::boundaryNoCheck(const string& idStr) const {
    string fFirst = getImageNameFromId(idStr);
    logger->inputId(idStr, fFirst);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    morphInterface.boundary(fFirst, fNew);
    logger->endSection();
}

void MorphDSLSemantics::boundaryImpl(const Identifier& id1) const {
    logger->startSection("BOUNDARY");

    if (!checkVariableExist(id1)) {
        return;
    }

    boundaryNoCheck(id1.getText());
}

