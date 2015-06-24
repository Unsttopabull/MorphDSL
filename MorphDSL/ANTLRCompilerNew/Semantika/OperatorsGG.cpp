#include "stdafx.h"
#include "../MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::negateImpl(const CommonTokenType* id) {
    cout << "NEGATE" << endl;

    string fLast = getImageNameFromId(id->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    // morphInterface.negate("maribor1.bmp", "maribor2.bmp");
    morphInterface.negate(fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::normalizeImpl() {
    cout << "NORMALIZE" << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << imeIzhodneSlike;
    fLast << zadnjaSpremenljivka[0] - 96 - 1;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    // d = open(AREA, 250, c)
    // morphInterface.openAREA(250, "maribor1.bmp", "maribor2.bmp");
    morphInterface.normalize(fLast.str(), fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::multiplyImpl(const CommonTokenType* id, double num) {
    cout << "MULTIPLY" << endl;
    cout << "<--  " << num << endl;

    string fLast = getImageNameFromId(id->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.multiply(fLast, num, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::multiplyImpl(double num, const CommonTokenType* id) {
    if (!checkVariablesExist(id)) {
        return;
    }

    cout << "MULTIPLY" << endl;
    cout << "<--  " << num << endl;

    string fLast = getImageNameFromId(id->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.multiply(num, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::multiplyImpl(const CommonTokenType* id1, const CommonTokenType* id2) {
    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    cout << "MULTYPLY" << endl;

    string fFirst = getImageNameFromId(id1->getText());
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.multiply(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::cropImpl(const CommonTokenType* id, double lowBound, double highBound) {
    if (!checkVariablesExist(id)) {
        return;
    }

    cout << "CROP" << endl;

    string fLast = getImageNameFromId(id->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.crop(fLast, lowBound, highBound, fNew);
    cout << "---END" << endl;
    cout << "---END" << endl;
}

void MorphDSLParser::subtractImplNoCheck(string id1Str, string id2Str) {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2Str);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created

    morphInterface.subtract(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::subtractImpl(const CommonTokenType* id1, const CommonTokenType* id2) {
    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    cout << "SUBTRACT" << endl;

    subtractImplNoCheck(id1->getText(), id2->getText());
}

void MorphDSLParser::gradientInternalImpl(const CommonTokenType* id) {
    if (!checkVariablesExist(id)) {
        return;
    }

    cout << "GRADIENT INTERNAL" << endl;

    string fFirst = getImageNameFromId(id->getText());
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.gradientINTERNAL(fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::gradientExternalImpl(const CommonTokenType* id) {
    if (!checkVariablesExist(id)) {
        return;
    }

    cout << "GRADIENT EXTERNAL" << endl;

    string fFirst = getImageNameFromId(id->getText());
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.gradientEXTERNAL(fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::diferentialProfilesMorphologicalImpl(const CommonTokenType* id1, const CommonTokenType* id2) {
    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    cout << "DIF. PROFILES - MORPHOLOGICAL" << endl;

    string fFirst = getImageNameFromId(id2->getText());
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    auto vector = vect.find(id1->getText());
    if (vector == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1 << "' ni vektor." << endl;
        return;
    }

    morphInterface.diferentialProfilesMORPHOLOGICAL(fFirst, vector->second, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::diferentialProfilesAttributeImpl(const CommonTokenType* id1, const CommonTokenType* id2) {
    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    cout << "DIF. PROFILES - ATTRIBUTE" << endl;

    string fFirst = getImageNameFromId(id2->getText());
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    if (fFirst.empty()) {
        cout << "ERROR: Spremenljivka '" << id2 << "' ne obstaja." << endl;
        return;
    }

    auto vector = vect.find(id1->getText());
    if (vector == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1 << "' ni vektor." << endl;
        return;
    }

    morphInterface.diferentialProfilesATTRIBUTE(fFirst, vector->second, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::mappingDmpImpl(const CommonTokenType* id1, const CommonTokenType* id2) {
    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    cout << "MAPPING - DMP" << endl;

    string fFirst = getImageNameFromId(id2->getText());
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    if (fFirst.empty()) {
        cout << "ERROR: Spremenljivka '" << id2 << "' ne obstaja." << endl;
        return;
    }

    auto vector = vect.find(id1->getText());
    if (vector == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1 << "' ni vektor." << endl;
        return;
    }

    morphInterface.mappingDMP(fFirst, vector->second, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::mappingDapImpl(const CommonTokenType* id1, const CommonTokenType* id2) {
    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    cout << "MAPPING - DAP" << endl;

    string fFirst = getImageNameFromId(id2->getText());
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    if (fFirst.empty()) {
        cout << "ERROR: Spremenljivka '" << id2 << "' ne obstaja." << endl;
        return;
    }

    auto vector = vect.find(id1->getText());
    if (vector == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1 << "' ni vektor." << endl;
        return;
    }

    morphInterface.mappingDAP(fFirst, vector->second, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::segmentationMsls1Impl(const CommonTokenType* id1, const CommonTokenType* id2) {
    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    cout << "SEGMENTATION - MSLS" << endl;

    cout << "MAPPING - DAP" << endl;

    string fFirst = getImageNameFromId(id2->getText());
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    if (fFirst.empty()) {
        cout << "ERROR: Spremenljivka '" << id2 << "' ne obstaja." << endl;
        return;
    }

    auto vector = vect.find(id1->getText());
    if (vector == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1 << "' ni vektor." << endl;
        return;
    }

    morphInterface.segmentationMSLS(fFirst, vector->second, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::segmentationMsls2Impl(const CommonTokenType* id1, const CommonTokenType* id2) {
    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    cout << "SEGMENTATION - MSLS" << endl;

    cout << "MAPPING - DAP" << endl;

    string fFirst = getImageNameFromId(id2->getText());
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    if (fFirst.empty()) {
        cout << "ERROR: Spremenljivka '" << id2 << "' ne obstaja." << endl;
        return;
    }

    auto vector = vect.find(id1->getText());
    if (vector == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1 << "' ni vektor." << endl;
        return;
    }

    morphInterface.segmentationMSLS(fFirst, vector->second, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::segmentationWatershadeImpl(const CommonTokenType* id) {
    if (!checkVariablesExist(id)) {
        return;
    }

    cout << "SEGMENTATION - WATHERSHADE" << endl;

    string fFirst = getImageNameFromId(id->getText());
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageNameWtf();
    cout << "-->  " << fNew << endl;

    morphInterface.segmentationWATHERSHADE(fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::segmentationWatershadeMarkerImpl(const CommonTokenType* id1, const CommonTokenType* id2) {
    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    cout << "SEGMENTATION - WATHERSHADE MARKER" << endl;

    string fFirst = getImageNameFromId(id1->getText());
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageNameWtf();
    cout << "-->  " << fNew << endl;

    string m1 = getImageNameFromId(id2->getText());
    cout << "<--  " << m1 << endl;

    morphInterface.segmentationWATHERSHADE(m1, fFirst, fNew);

    cout << "---END" << endl;
}