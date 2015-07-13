#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::negateNoCheck(const string& idStr) const {
    string fLast = getImageNameFromId(idStr);
    logger->inputId(idStr, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    // morphInterface.negate("maribor1.bmp", "maribor2.bmp");

    morphInterface.negate(fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::negateImpl(const Identifier& id) const {
    logger->startSection("NEGATE");

    if (!checkVariableExist(id)) {
        return;
    }

    negateNoCheck(id.getText());
}

void MorphDSLSemantics::normalizeImpl() const {
    logger->startSection("NORMALIZE");

    string fLast = getImageNameFromId(predZadnjaSpremenljivka);

    logger->inputId(predZadnjaSpremenljivka, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    //when 5 pics created
    // d = open(AREA, 250, c)
    // morphInterface.openAREA(250, "maribor1.bmp", "maribor2.bmp");
    morphInterface.normalize(fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::multiplyNoCheck(double num, const string& idStr) const {
    logger->inputValue(num);

    string fLast = getImageNameFromId(idStr);
    logger->inputId(idStr, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    morphInterface.multiply(fLast, num, fNew);
    logger->endSection();
}

void MorphDSLSemantics::multiplyImpl(const Identifier& id, double num) const {
    logger->startSection("MULTIPLY");

    if (!checkVariableExist(id)) {
        return;
    }

    multiplyNoCheck(num, id.getText());
}

void MorphDSLSemantics::multiplyImpl(double num, const Identifier& id) const {
    multiplyImpl(id, num);
}

void MorphDSLSemantics::multiplyNoCheck(const string& id1, const string& id2) const {
    string fFirst = getImageNameFromId(id1);
    logger->inputId(id1, fFirst);

    string fLast = getImageNameFromId(id2);
    logger->inputId(id2, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    morphInterface.multiply(fFirst, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::multiplyImpl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("MULTYPLY");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    multiplyNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::cropNoCheck(const string& id1, double lowBound, double highBound) const {
    logger->inputValue(lowBound);
    logger->inputValue(highBound);

    string fLast = getImageNameFromId(id1);
    logger->inputId(id1, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    morphInterface.crop(fLast, lowBound, highBound, fNew);
    logger->endSection();
}

void MorphDSLSemantics::cropImpl(const Identifier& id, double lowBound, double highBound) const {
    logger->startSection("CROP");

    if (!checkVariableExist(id)) {
        return;
    }

    string id1Str = id.getText();

    cropNoCheck(id1Str, lowBound, highBound);
}

void MorphDSLSemantics::subtractNoCheck(const string& id1, const string& id2) const {
    string fFirst = getImageNameFromId(id1);
    logger->inputId(id1, fFirst);

    string fLast = getImageNameFromId(id2);
    logger->inputId(id2, fLast);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    //when 5 pics created

    morphInterface.subtract(fFirst, fLast, fNew);
    logger->endSection();
}

void MorphDSLSemantics::subtractImpl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("SUBTRACT");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    subtractNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::gradientInternalNoCheck(const string& id1) const {
    string fFirst = getImageNameFromId(id1);
    logger->inputId(id1, fFirst);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    //when 5 pics created

    morphInterface.gradientINTERNAL(fFirst, fNew);
    logger->endSection();
}

void MorphDSLSemantics::gradientInternalImpl(const Identifier& id) const {
    logger->startSection("GRADIENT INTERNAL");

    if (!checkVariableExist(id)) {
        return;
    }

    gradientInternalNoCheck(id.getText());
}

void MorphDSLSemantics::gradientExternalNoCheck(const string& id) const {
    string fFirst = getImageNameFromId(id);
    logger->inputId(id, fFirst);

    string fNew = getLastVariableImageName();
    logger->outputId(zadnjaSpremenljivka, fNew);

    //when 5 pics created

    morphInterface.gradientEXTERNAL(fFirst, fNew);
    logger->endSection();
}

void MorphDSLSemantics::gradientExternalImpl(const Identifier& id) const {
    logger->startSection("GRADIENT EXTERNAL");

    if (!checkVariableExist(id)) {
        return;
    }

    gradientExternalNoCheck(id.getText());
}

void MorphDSLSemantics::diferentialProfilesMorphologicalNoCheck(const string& id1Str, const string& id2Str, const vector<double>& vector) const {
    string fFirst = getImageNameFromId(id2Str);
    logger->inputId(id2Str, fFirst);

    string fLast = getImageNameFromId(id1Str);
    logger->inputId(id1Str, fLast);

    string fNew = getLastVariableImageName(true);
    logger->outputString(fNew + ".wtf");

    morphInterface.diferentialProfilesMORPHOLOGICAL(fFirst, vector, fNew);
    logger->endSection();
}

void MorphDSLSemantics::diferentialProfilesMorphologicalImpl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("DIF. PROFILES - MORPHOLOGICAL");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1.getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        logger->errorNotVector(id1);
        parser->set_failedflag(true);
        return;
    }

    diferentialProfilesMorphologicalNoCheck(id1Str, id2.getText(), vectorIter->second);
}

void MorphDSLSemantics::differentialProfilesAttributeNoCheck(const string& id1, const string& id2, const vector<double>& vector) const {
    string fFirst = getImageNameFromId(id2);
    logger->inputId(id2, fFirst);

    string fLast = getImageNameFromId(id1);
    logger->inputId(id1, fLast);

    string fNew = getLastVariableImageName(true);
    logger->outputString(fNew + ".wtf");

    morphInterface.diferentialProfilesATTRIBUTE(fFirst, vector, fNew);
    logger->endSection();
}

void MorphDSLSemantics::diferentialProfilesAttributeImpl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("DIF. PROFILES - ATTRIBUTE");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1.getToken()->getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        logger->errorNotVector(id1);
        parser->set_failedflag(true);
        return;
    }

    differentialProfilesAttributeNoCheck(id1Str, id2.getText(), vectorIter->second);
}

void MorphDSLSemantics::mappingDmpNoCheck(const string& id1, const string& id2, const vector<double>& vector) const {
    string fFirst = getImageNameFromId(id2);
    logger->inputId(id2, fFirst);

    string fLast = getImageNameFromId(id1);
    logger->inputId(id1, fLast);

    string fNew = getLastVariableImageName(true);
    logger->outputString(fNew + ".wtf");

    morphInterface.mappingDMP(fFirst, vector, fNew);
    logger->endSection();
}

void MorphDSLSemantics::mappingDmpImpl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("MAPPING - DMP");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1.getToken()->getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        logger->errorNotVector(id1);
        parser->set_failedflag(true);
        return;
    }

    mappingDmpNoCheck(id1Str, id2.getText(), vectorIter->second);
}

void MorphDSLSemantics::mappingDapNoCheck(const string& id2, const string& id1, const vector<double>& vector) const {
    string fFirst = getImageNameFromId(id2);
    logger->inputId(id2, fFirst);

    string fLast = getImageNameFromId(id1);
    logger->inputId(id1, fLast);

    string fNew = getLastVariableImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    morphInterface.mappingDAP(fFirst, vector, fNew);
    logger->endSection();
}

void MorphDSLSemantics::mappingDapImpl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("MAPPING - DAP");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1.getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        logger->errorNotVector(id1);
        parser->set_failedflag(true);
        return;
    }

    mappingDapNoCheck(id2.getText(), id1Str, vectorIter->second);
}

void MorphDSLSemantics::segmentationMsls1NoCheck(const string& id2, const string& id1, const vector<double>& vector) const {
    string fFirst = getImageNameFromId(id2);
    logger->inputId(id2, fFirst);

    string fLast = getImageNameFromId(id1);
    logger->inputId(id1, fLast);

    string fNew = getLastVariableImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    morphInterface.segmentationMSLS(fFirst, vector, fNew);
    logger->endSection();
}

void MorphDSLSemantics::segmentationMsls1Impl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("SEGMENTATION - MSLS");
    logger->startSection("MAPPING - DAP");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1.getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        logger->errorNotVector(id1);
        parser->set_failedflag(true);
        return;
    }

    segmentationMsls1NoCheck(id2.getText(), id1Str, vectorIter->second);
}

void MorphDSLSemantics::segmentationMsls2NoCheck(const string& id1, const string& id2, const vector<double>& vector) const {
    string fFirst = getImageNameFromId(id2);
    logger->inputId(id2, fFirst);

    string fLast = getImageNameFromId(id1);
    logger->inputId(id1, fLast);

    string fNew = getLastVariableImageName(true);
    logger->outputString(fNew + ".wtf");

    morphInterface.segmentationMSLS(fFirst, vector, fNew);
    logger->endSection();
}

void MorphDSLSemantics::segmentationMsls2Impl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("SEGMENTATION - MSLS");
    logger->startSection("MAPPING - DAP");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1.getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        logger->errorNotVector(id1);
        parser->set_failedflag(true);
        return;
    }

    segmentationMsls2NoCheck(id1Str, id2.getText(), vectorIter->second);
}

void MorphDSLSemantics::segmentatonWatershadeNoCheck(const string& id) const {
    string fFirst = getImageNameFromId(id);
    logger->inputId(id, fFirst);

    string fNew = getLastVariableImageNameWtf();
    logger->outputId(zadnjaSpremenljivka, fNew);

    morphInterface.segmentationWATHERSHADE(fFirst, fNew);
    logger->endSection();
}

void MorphDSLSemantics::segmentationWatershadeImpl(const Identifier& id) const {
    logger->startSection("SEGMENTATION - WATHERSHADE");

    if (!checkVariableExist(id)) {
        return;
    }

    segmentatonWatershadeNoCheck(id.getText());
}

void MorphDSLSemantics::segmentationWatershadeMarkerNoCheck(const string& id1, const string& id2) const {
    string fFirst = getImageNameFromId(id1);
    logger->inputId(id1, fFirst);

    string fNew = getLastVariableImageNameWtf();
    logger->outputId(zadnjaSpremenljivka,fNew);

    string m1 = getImageNameFromId(id2);
    logger->inputId(id2, m1);

    morphInterface.segmentationWATHERSHADE(m1, fFirst, fNew);

    cout << "---END" << endl;
}

void MorphDSLSemantics::segmentationWatershadeMarkerImpl(const Identifier& id1, const Identifier& id2) const {
    logger->startSection("SEGMENTATION - WATHERSHADE MARKER");

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    segmentationWatershadeMarkerNoCheck(id1.getText(), id2.getText());
}