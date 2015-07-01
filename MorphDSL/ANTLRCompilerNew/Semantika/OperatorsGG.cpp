#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::negateNoCheck(const string& idStr) const {
    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    // morphInterface.negate("maribor1.bmp", "maribor2.bmp");

    morphInterface.negate(fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::negateImpl(const Identifier& id) const {
    cout << "NEGATE" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    negateNoCheck(id.getText());
}

void MorphDSLSemantics::normalizeImpl() const {
    cout << "NORMALIZE" << endl;

    string fLast = getImageNameFromId(predZadnjaSpremenljivka);

    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    // d = open(AREA, 250, c)
    // morphInterface.openAREA(250, "maribor1.bmp", "maribor2.bmp");
    morphInterface.normalize(fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::multiplyNoCheck(double num, const string& idStr) const {
    cout << "<--  " << num << endl;

    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.multiply(fLast, num, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::multiplyImpl(const Identifier& id, double num) const {
    cout << "MULTIPLY" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    multiplyNoCheck(num, id.getText());
}

void MorphDSLSemantics::multiplyImpl(double num, const Identifier& id) const {
    multiplyImpl(id, num);
}

void MorphDSLSemantics::multiplyNoCheck(const string& id1Str, const string& id2Str) const {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2Str);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.multiply(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::multiplyImpl(const Identifier& id1, const Identifier& id2) const {
    cout << "MULTYPLY" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    multiplyNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::cropNoCheck(const string& id1Str, double lowBound, double highBound) const {
    string fLast = getImageNameFromId(id1Str);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.crop(fLast, lowBound, highBound, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::cropImpl(const Identifier& id, double lowBound, double highBound) const {
    cout << "CROP" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    string id1Str = id.getText();

    cropNoCheck(id1Str, lowBound, highBound);
}

void MorphDSLSemantics::subtractNoCheck(const string& id1Str, const string& id2Str) const {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2Str);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created

    morphInterface.subtract(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::subtractImpl(const Identifier& id1, const Identifier& id2) const {
    cout << "SUBTRACT" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    subtractNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::gradientInternalNoCheck(const string& id1Str) const {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created

    morphInterface.gradientINTERNAL(fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::gradientInternalImpl(const Identifier& id) const {
    cout << "GRADIENT INTERNAL" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    gradientInternalNoCheck(id.getText());
}

void MorphDSLSemantics::gradientExternalNoCheck(const string& id1Str) const {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created

    morphInterface.gradientEXTERNAL(fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::gradientExternalImpl(const Identifier& id) const {
    cout << "GRADIENT EXTERNAL" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    string id1Str = id.getText();

    gradientExternalNoCheck(id1Str);
}

void MorphDSLSemantics::diferentialProfilesMorphologicalNoCheck(const string& id1Str, const string& id2Str, const vector<double>& vector) const {
    string fFirst = getImageNameFromId(id2Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1Str);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    morphInterface.diferentialProfilesMORPHOLOGICAL(fFirst, vector, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::diferentialProfilesMorphologicalImpl(const Identifier& id1, const Identifier& id2) const {
    cout << "DIF. PROFILES - MORPHOLOGICAL" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1.getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1Str << "' ni vektor." << endl;
        return;
    }

    diferentialProfilesMorphologicalNoCheck(id1Str, id2.getText(), vectorIter->second);
}

void MorphDSLSemantics::differentialProfilesAttributeNoCheck(const string& id1Str, const string& id2Str, const vector<double>& vector) const {
    string fFirst = getImageNameFromId(id2Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1Str);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    morphInterface.diferentialProfilesATTRIBUTE(fFirst, vector, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::diferentialProfilesAttributeImpl(const Identifier& id1, const Identifier& id2) const {
    cout << "DIF. PROFILES - ATTRIBUTE" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1.getToken()->getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1Str << "' ni vektor." << endl;
        return;
    }

    differentialProfilesAttributeNoCheck(id1Str, id2.getText(), vectorIter->second);
}

void MorphDSLSemantics::mappingDmpNoCheck(const string& id1Str, const string& id2Str, const vector<double>& vector) const {
    string fFirst = getImageNameFromId(id2Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1Str);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    morphInterface.mappingDMP(fFirst, vector, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::mappingDmpImpl(const Identifier& id1, const Identifier& id2) const {
    cout << "MAPPING - DMP" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1.getToken()->getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1Str << "' ni vektor." << endl;
        parser->set_failedflag(true);
        return;
    }

    mappingDmpNoCheck(id1Str, id2.getText(), vectorIter->second);
}

void MorphDSLSemantics::mappingDapNoCheck(const string& id2Str, const string& id1Str, const vector<double>& vector) const {
    string fFirst = getImageNameFromId(id2Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1Str);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    morphInterface.mappingDAP(fFirst, vector, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::mappingDapImpl(const Identifier& id1, const Identifier& id2) const {
    cout << "MAPPING - DAP" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1.getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1Str << "' ni vektor." << endl;
        parser->set_failedflag(true);
        return;
    }

    mappingDapNoCheck(id2.getText(), id1Str, vectorIter->second);
}

void MorphDSLSemantics::segmentationMsls1NoCheck(const string& id2Str, const string& id1Str, const vector<double>& vector) const {
    string fFirst = getImageNameFromId(id2Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1Str);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    morphInterface.segmentationMSLS(fFirst, vector, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::segmentationMsls1Impl(const Identifier& id1, const Identifier& id2) const {
    cout << "SEGMENTATION - MSLS" << endl;
    cout << "MAPPING - DAP" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1.getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1Str << "' ni vektor." << endl;
        parser->set_failedflag(true);
        return;
    }

    segmentationMsls1NoCheck(id2.getText(), id1Str, vectorIter->second);
}

void MorphDSLSemantics::segmentationMsls2NoCheck(const string& id1Str, const string& id2Str, const vector<double>& vector) const {
    string fFirst = getImageNameFromId(id2Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id1Str);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName(true);
    cout << "-->  " << fNew << ".wtf" << endl;

    morphInterface.segmentationMSLS(fFirst, vector, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::segmentationMsls2Impl(const Identifier& id1, const Identifier& id2) const {
    cout << "SEGMENTATION - MSLS" << endl;
    cout << "MAPPING - DAP" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    string id1Str = id1.getText();

    auto vectorIter = vect.find(id1Str);
    if (vectorIter == vect.end()) {
        cout << "ERROR: Spremenljivka '" << id1Str << "' ni vektor." << endl;
        parser->set_failedflag(true);
        return;
    }

    segmentationMsls2NoCheck(id1Str, id2.getText(), vectorIter->second);
}

void MorphDSLSemantics::segmentatonWatershadeNoCheck(const string& idStr) const {
    string fFirst = getImageNameFromId(idStr);
    cout << "<--  " << fFirst << endl;

    string fNew = getLastVariableImageNameWtf();
    cout << "-->  " << fNew << endl;

    morphInterface.segmentationWATHERSHADE(fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::segmentationWatershadeImpl(const Identifier& id) const {
    cout << "SEGMENTATION - WATHERSHADE" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    segmentatonWatershadeNoCheck(id.getText());
}

void MorphDSLSemantics::segmentationWatershadeMarkerNoCheck(const string& id1Str, const string& id2Str) const {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fNew = getLastVariableImageNameWtf();
    cout << "-->  " << fNew << endl;

    string m1 = getImageNameFromId(id2Str);
    cout << "<--  " << m1 << endl;

    morphInterface.segmentationWATHERSHADE(m1, fFirst, fNew);

    cout << "---END" << endl;
}

void MorphDSLSemantics::segmentationWatershadeMarkerImpl(const Identifier& id1, const Identifier& id2) const {
    cout << "SEGMENTATION - WATHERSHADE MARKER" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    segmentationWatershadeMarkerNoCheck(id1.getText(), id2.getText());
}