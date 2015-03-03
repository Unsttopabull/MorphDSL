#include "stdafx.h"
#include "MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::negateImpl(string id) {
    cout << "NEGATE" << endl;

    string fLast = getNewImageNameFromId(id);
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
    fLast << outputFigureName;
    fLast << currentFigure->getText()[0] - 96 - 1;
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

void MorphDSLParser::multiplyImpl(std::string id, double num) {
    cout << "MULTIPLY" << endl;
    cout << "<--  " << num << endl;

    string fLast = getNewImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.multiply(fLast, num, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::multiplyImpl(double num, std::string id) {
    cout << "MULTIPLY" << endl;
    cout << "<--  " << num << endl;

    string fLast = getNewImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.multiply(num, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::multiplyImpl(std::string id1, std::string id2) {
    cout << "MULTYPLY" << endl;

    string fFirst = getNewImageNameFromId(id1);
    cout << "<--  " << fFirst << endl;

    string fLast = getNewImageNameFromId(id2);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.multiply(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::cropImpl(std::string id, double lowBound, double highBound) {
    cout << "CROP" << endl;

    string fLast = getNewImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.crop(fLast, lowBound, highBound, fNew);
    cout << "---END" << endl;
    cout << "---END" << endl;
}

void MorphDSLParser::subtractImpl(std::string id1, std::string id2) {
    cout << "SUBTRACT" << endl;

    string fFirst = getNewImageNameFromId(id1);
    cout << "<--  " << fFirst << endl;

    string fLast = getNewImageNameFromId(id2);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.subtract(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::gradientInternalImpl(std::string id) {
    cout << "GRADIENT INTERNAL" << endl;

    string fFirst = getNewImageNameFromId(id);
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.gradientINTERNAL(fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::gradientExternalImpl(std::string id) {
    cout << "GRADIENT EXTERNAL" << endl;

    string fFirst = getNewImageNameFromId(id);
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created
    morphInterface.gradientEXTERNAL(fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::diferentialProfilesMorphologicalImpl(std::string id1, std::string id2) {
    cout << "DIF. PROFILES - MORPHOLOGICAL" << endl;

    string fFirst = getNewImageNameFromId(id2);
    cout << "<--  " << fFirst << endl;

    stringstream fLast;//create a stringstream
    fLast << id1[0] - 96;
    cout << "<--  " << fLast.str() << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << endl;

    std::map<string, std::vector<double>>::iterator it;
    it = vect.find(fLast.str());

    morphInterface.diferentialProfilesMORPHOLOGICAL(fFirst, it->second, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::diferentialProfilesAttributeImpl(std::string id1, std::string id2) {
    cout << "DIF. PROFILES - ATTRIBUTE" << endl;

    string fFirst = getNewImageNameFromId(id2);
    cout << "<--  " << fFirst << endl;

    stringstream fLast;//create a stringstream
    fLast << id1[0] - 96;
    cout << "<--  " << fLast.str() << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << endl;

    std::map<string, std::vector<double>>::iterator it;
    it = vect.find(fLast.str());

    morphInterface.diferentialProfilesATTRIBUTE(fFirst, it->second, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::mappingDmpImpl(std::string id1, std::string id2) {
    cout << "MAPPING - DMP" << endl;

    string fFirst = getNewImageNameFromId(id2);
    cout << "<--  " << fFirst << endl;

    stringstream fLast;//create a stringstream
    fLast << id1[0] - 96;
    cout << "<--  " << fLast.str() << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << endl;

    std::map<string, std::vector<double>>::iterator it;
    it = vect.find(fLast.str());

    morphInterface.mappingDMP(fFirst, it->second, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::mappingDapImpl(std::string id1, std::string id2) {
    cout << "MAPPING - DAP" << endl;

    string fFirst = getNewImageNameFromId(id2);
    cout << "<--  " << fFirst << endl;

    stringstream fLast;//create a stringstream
    fLast << id1[0] - 96;
    cout << "<--  " << fLast.str() << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << endl;

    std::map<string, std::vector<double>>::iterator it;
    it = vect.find(fLast.str());

    morphInterface.mappingDAP(fFirst, it->second, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::segmentationMsls1Impl(std::string id1, std::string id2) {
    cout << "SEGMENTATION - MSLS" << endl;

    cout << "MAPPING - DAP" << endl;

    string fFirst = getNewImageNameFromId(id2);
    cout << "<--  " << fFirst << endl;

    stringstream fLast;//create a stringstream
    fLast << id1[0] - 96;
    cout << "<--  " << fLast.str() << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << endl;

    std::map<string, std::vector<double>>::iterator it;
    it = vect.find(fLast.str());

    morphInterface.segmentationMSLS(fFirst, it->second, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::segmentationMsls2Impl(std::string id1, std::string id2) {
    cout << "SEGMENTATION - MSLS" << endl;

    cout << "MAPPING - DAP" << endl;

    string fFirst = getNewImageNameFromId(id1);
    cout << "<--  " << fFirst << endl;

    stringstream fLast;//create a stringstream
    fLast << id2[0] - 96;
    cout << "<--  " << fLast.str() << endl;

    string fNew = getNewImageName(true);
    cout << "-->  " << fNew << endl;

    std::map<string, std::vector<double>>::iterator it;
    it = vect.find(fLast.str());

    morphInterface.segmentationMSLS(fFirst, it->second, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::segmentationWatershadeImpl(std::string id) {
    cout << "SEGMENTATION - WATHERSHADE" << endl;

    string fFirst = getNewImageNameFromId(id);
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageNameWtf();
    cout << "-->  " << fNew << endl;

    morphInterface.segmentationWATHERSHADE(fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::segmentationWatershadeMarkerImpl(std::string id1, std::string id2) {
    cout << "SEGMENTATION - WATHERSHADE MARKER" << endl;

    string fFirst = getNewImageNameFromId(id1);
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageNameWtf();
    cout << "-->  " << fNew << endl;

    //					if (marker1!=NULL)
    //					{
    stringstream m1;//create a stringstream
    m1 << "./";
    m1 << outputFigureName;
    m1 << id2[0] - 96;
    //m1 << marker1->getText()[0]-96;
    m1 << ".bmp";
    cout << "<--  " << m1.str() << endl;

    morphInterface.segmentationWATHERSHADE(m1.str(), fFirst, fNew);
    //					}
    /*					else if (marker2 != NULL)
    {
    stringstream nss;//create a stringstream
    nss << marker2->getText();
    int number;
    istringstream(nss.str()) >> number;
    cout<<"<--  "<<number<<endl;

    morphInterface.segmentationWATHERSHADE(number, fFirst.str(), fNew.str());
    }
    */
    cout << "---END" << endl;

    //marker1 = NULL;
    //marker2 = NULL;
}