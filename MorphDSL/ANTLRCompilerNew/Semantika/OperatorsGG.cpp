#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::negateNoCheck(string idStr) {
    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    // morphInterface.negate("maribor1.bmp", "maribor2.bmp");

    morphInterface.negate(fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::negateImpl(const Identifier* id) {
    cout << "NEGATE" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    negateNoCheck(id->getText());
}

void MorphDSLSemantics::normalizeImpl() {
    cout << "NORMALIZE" << endl;

    string fLast = getImageNameFromId(predZadnjaSpremenljivka);

    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    // d = open(AREA, 250, c)
    // morphInterface.openAREA(250, "maribor1.bmp", "maribor2.bmp");
    morphInterface.normalize(fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::multiplyNoCheck(double num, string idStr) {
    cout << "<--  " << num << endl;

    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.multiply(fLast, num, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::multiplyImpl(const Identifier* id, double num) {
    cout << "MULTIPLY" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    multiplyNoCheck(num, id->getText());
}

void MorphDSLSemantics::multiplyImpl(double num, const Identifier* id) {
    multiplyImpl(id, num);
}

void MorphDSLSemantics::multiplyNoCheck(string id1Str, string id2Str) {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2Str);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.multiply(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::multiplyImpl(const Identifier* id1, const Identifier* id2) {
    cout << "MULTYPLY" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    multiplyNoCheck(id1->getText(), id2->getText());
}

void MorphDSLSemantics::cropNoCheck(string id1Str, double lowBound, double highBound) {
    string fLast = getImageNameFromId(id1Str);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.crop(fLast, lowBound, highBound, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::cropImpl(const Identifier* id, double lowBound, double highBound) {
    cout << "CROP" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    string id1Str = id->getText();

    cropNoCheck(id1Str, lowBound, highBound);
}

void MorphDSLSemantics::subtractNoCheck(string id1Str, string id2Str) {
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

void MorphDSLSemantics::subtractImpl(const Identifier* id1, const Identifier* id2) {
    cout << "SUBTRACT" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    subtractNoCheck(id1->getText(), id2->getText());
}

void MorphDSLSemantics::gradientInternalNoCheck(string id1Str) {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created

    morphInterface.gradientINTERNAL(fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::gradientInternalImpl(const Identifier* id) {
    cout << "GRADIENT INTERNAL" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    gradientInternalNoCheck(id->getText());
}

void MorphDSLSemantics::gradientExternalNoCheck(string id1Str) {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created

    morphInterface.gradientEXTERNAL(fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::gradientExternalImpl(const Identifier* id) {
    cout << "GRADIENT EXTERNAL" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    string id1Str = id->getText();

    gradientExternalNoCheck(id1Str);
}

void MorphDSLSemantics::diferentialProfilesMorphologicalNoCheck(string id1Str, string id2Str, vector<double> vector) {
    string fFirst = getImageNameFromId(id2Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1Str);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    morphInterface.diferentialProfilesMORPHOLOGICAL(fFirst, vector, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::diferentialProfilesMorphologicalImpl(const Identifier* id1, const Identifier* id2) {
    cout << "DIF. PROFILES - MORPHOLOGICAL" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1->getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1 << "' ni vektor." << endl;
        return;
    }

    diferentialProfilesMorphologicalNoCheck(id1Str, id2->getText(), vectorIter->second);
}

void MorphDSLSemantics::differentialProfilesAttributeNoCheck(string id1Str, string id2Str, vector<double> vector) {
    string fFirst = getImageNameFromId(id2Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1Str);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    morphInterface.diferentialProfilesATTRIBUTE(fFirst, vector, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::diferentialProfilesAttributeImpl(const Identifier* id1, const Identifier* id2) {
    cout << "DIF. PROFILES - ATTRIBUTE" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1->getToken()->getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1 << "' ni vektor." << endl;
        return;
    }

    differentialProfilesAttributeNoCheck(id1Str, id2->getText(), vectorIter->second);
}

void MorphDSLSemantics::mappingDmpNoCheck(string id1Str, string id2Str, vector<double> vector) {
    string fFirst = getImageNameFromId(id2Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1Str);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    morphInterface.mappingDMP(fFirst, vector, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::mappingDmpImpl(const Identifier* id1, const Identifier* id2) {
    cout << "MAPPING - DMP" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1->getToken()->getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1 << "' ni vektor." << endl;
        parser->set_failedflag(true);
        return;
    }

    mappingDmpNoCheck(id1Str, id2->getText(), vectorIter->second);
}

void MorphDSLSemantics::mappingDapNoCheck(string id2Str, string id1Str, vector<double> vector) {
    string fFirst = getImageNameFromId(id2Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1Str);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    morphInterface.mappingDAP(fFirst, vector, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::mappingDapImpl(const Identifier* id1, const Identifier* id2) {
    cout << "MAPPING - DAP" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1->getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1 << "' ni vektor." << endl;
        parser->set_failedflag(true);
        return;
    }

    mappingDapNoCheck(id2->getText(), id1Str, vectorIter->second);
}

void MorphDSLSemantics::segmentationMsls1NoCheck(string id2Str, string id1Str, vector<double> vector) {
    string fFirst = getImageNameFromId(id2Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1Str);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    morphInterface.segmentationMSLS(fFirst, vector, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::segmentationMsls1Impl(const Identifier* id1, const Identifier* id2) {
    cout << "SEGMENTATION - MSLS" << endl;
    cout << "MAPPING - DAP" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1->getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1 << "' ni vektor." << endl;
        parser->set_failedflag(true);
        return;
    }

    segmentationMsls1NoCheck(id2->getText(), id1Str, vectorIter->second);
}

void MorphDSLSemantics::segmentationMsls2NoCheck(string id1Str, string id2Str, vector<double> vector) {
    string fFirst = getImageNameFromId(id2Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1Str);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    morphInterface.segmentationMSLS(fFirst, vector, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::segmentationMsls2Impl(const Identifier* id1, const Identifier* id2) {
    cout << "SEGMENTATION - MSLS" << endl;
    cout << "MAPPING - DAP" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1->getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1 << "' ni vektor." << endl;
        parser->set_failedflag(true);
        return;
    }

    segmentationMsls2NoCheck(id1Str, id2->getText(), vectorIter->second);
}

void MorphDSLSemantics::segmentatonWatershadeNoCheck(string idStr) {
    string fFirst = getImageNameFromId(idStr);
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageNameWtf();
    cout << "-->  " << fNew << endl;

    morphInterface.segmentationWATHERSHADE(fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::segmentationWatershadeImpl(const Identifier* id) {
    cout << "SEGMENTATION - WATHERSHADE" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    segmentatonWatershadeNoCheck(id->getText());
}

void MorphDSLSemantics::segmentationWatershadeMarkerNoCheck(string id1Str, string id2Str) {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageNameWtf();
    cout << "-->  " << fNew << endl;

    string m1 = getImageNameFromId(id2Str);
    cout << "<--  " << m1 << endl;

    morphInterface.segmentationWATHERSHADE(m1, fFirst, fNew);

    cout << "---END" << endl;
}

void MorphDSLSemantics::segmentationWatershadeMarkerImpl(const Identifier* id1, const Identifier* id2) {
    cout << "SEGMENTATION - WATHERSHADE MARKER" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    segmentationWatershadeMarkerNoCheck(id1->getText(), id2->getText());
}