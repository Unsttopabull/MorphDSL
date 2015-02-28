#include "stdafx.h"
#include "MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::negateImpl(string id) {
    cout << "NEGATE" << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << outputFigureName;
    fLast << id[0] - 96;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    // morphInterface.negate("maribor1.bmp", "maribor2.bmp");
    morphInterface.negate(fLast.str(), fNew.str());
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

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    //when 5 pics created
    // d = open(AREA, 250, c)
    // morphInterface.openAREA(250, "maribor1.bmp", "maribor2.bmp");
    morphInterface.normalize(fLast.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::multiplyImpl(std::string id, double num) {
    cout << "MULTIPLY" << endl;
    cout << "<--  " << num << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << outputFigureName;
    fLast << id[0] - 96;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    morphInterface.multiply(fLast.str(), num, fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::multiplyImpl(double num, std::string id) {
    cout << "MULTIPLY" << endl;
    cout << "<--  " << num << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << outputFigureName;
    fLast << id[0] - 96;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    morphInterface.multiply(num, fLast.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::multiplyImpl(std::string id1, std::string id2) {
    cout << "MULTYPLY" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << "./";
    fFirst << outputFigureName;
    fFirst << id1[0] - 96;
    fFirst << ".bmp";
    cout << "<--  " << fFirst.str() << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << outputFigureName;
    fLast << id2[0] - 96;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    morphInterface.multiply(fFirst.str(), fLast.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::cropImpl(std::string id, double lowBound, double highBound) {
    cout << "CROP" << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << outputFigureName;
    fLast << id[0] - 96;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    morphInterface.crop(fLast.str(), lowBound, highBound, fNew.str());
    cout << "---END" << endl;
    cout << "---END" << endl;
}

void MorphDSLParser::subtractImpl(std::string id1, std::string id2) {
    cout << "SUBTRACT" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << "./";
    fFirst << outputFigureName;
    fFirst << id1[0] - 96;
    fFirst << ".bmp";
    cout << "<--  " << fFirst.str() << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << outputFigureName;
    fLast << id2[0] - 96;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    //when 5 pics created
    morphInterface.subtract(fFirst.str(), fLast.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::gradientInternalImpl(std::string id) {
    cout << "GRADIENT INTERNAL" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << "./";
    fFirst << outputFigureName;
    fFirst << id[0] - 96;
    fFirst << ".bmp";
    cout << "<--  " << fFirst.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    //when 5 pics created
    morphInterface.gradientINTERNAL(fFirst.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::gradientExternalImpl(std::string id) {
    cout << "GRADIENT EXTERNAL" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << "./";
    fFirst << outputFigureName;
    fFirst << id[0] - 96;
    fFirst << ".bmp";
    cout << "<--  " << fFirst.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    //when 5 pics created
    morphInterface.gradientEXTERNAL(fFirst.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::diferentialProfilesMorphologicalImpl(std::string id1, std::string id2) {
    cout << "DIF. PROFILES - MORPHOLOGICAL" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << "./";
    fFirst << outputFigureName;
    fFirst << id2[0] - 96;
    fFirst << ".bmp";
    cout << "<--  " << fFirst.str() << endl;

    stringstream fLast;//create a stringstream
    fLast << id1[0] - 96;
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    //fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    std::map<string, std::vector<double>>::iterator it;
    it = vect.find(fLast.str());

    morphInterface.diferentialProfilesMORPHOLOGICAL(fFirst.str(), it->second, fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::diferentialProfilesAttributeImpl(std::string id1, std::string id2) {
    cout << "DIF. PROFILES - ATTRIBUTE" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << "./";
    fFirst << outputFigureName;
    fFirst << id2[0] - 96;
    fFirst << ".bmp";
    cout << "<--  " << fFirst.str() << endl;

    stringstream fLast;//create a stringstream
    fLast << id1[0] - 96;
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    //fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    std::map<string, std::vector<double>>::iterator it;
    it = vect.find(fLast.str());

    morphInterface.diferentialProfilesATTRIBUTE(fFirst.str(), it->second, fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::mappingDmpImpl(std::string id1, std::string id2) {
    cout << "MAPPING - DMP" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << "./";
    fFirst << outputFigureName;
    fFirst << id2[0] - 96;
    fFirst << ".bmp";
    cout << "<--  " << fFirst.str() << endl;

    stringstream fLast;//create a stringstream
    fLast << id1[0] - 96;
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    //fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    std::map<string, std::vector<double>>::iterator it;
    it = vect.find(fLast.str());

    morphInterface.mappingDMP(fFirst.str(), it->second, fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::mappingDapImpl(std::string id1, std::string id2) {
    cout << "MAPPING - DAP" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << "./";
    fFirst << outputFigureName;
    fFirst << id2[0] - 96;
    fFirst << ".bmp";
    cout << "<--  " << fFirst.str() << endl;

    stringstream fLast;//create a stringstream
    fLast << id1[0] - 96;
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    //fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    std::map<string, std::vector<double>>::iterator it;
    it = vect.find(fLast.str());

    morphInterface.mappingDAP(fFirst.str(), it->second, fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::segmentationMsls1Impl(std::string id1, std::string id2) {
    cout << "SEGMENTATION - MSLS" << endl;

    cout << "MAPPING - DAP" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << "./";
    fFirst << outputFigureName;
    fFirst << id2[0] - 96;
    fFirst << ".bmp";
    cout << "<--  " << fFirst.str() << endl;

    stringstream fLast;//create a stringstream
    fLast << id1[0] - 96;
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    //fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    std::map<string, std::vector<double>>::iterator it;
    it = vect.find(fLast.str());

    morphInterface.segmentationMSLS(fFirst.str(), it->second, fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::segmentationMsls2Impl(std::string id1, std::string id2) {
    cout << "SEGMENTATION - MSLS" << endl;

    cout << "MAPPING - DAP" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << "./";
    fFirst << outputFigureName;
    fFirst << id1[0] - 96;
    fFirst << ".bmp";
    cout << "<--  " << fFirst.str() << endl;

    stringstream fLast;//create a stringstream
    fLast << id2[0] - 96;
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    //fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    std::map<string, std::vector<double>>::iterator it;
    it = vect.find(fLast.str());

    morphInterface.segmentationMSLS(fFirst.str(), it->second, fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::segmentationWatershadeImpl(std::string id) {
    cout << "SEGMENTATION - WATHERSHADE" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << "./";
    fFirst << outputFigureName;
    fFirst << id[0] - 96;
    fFirst << ".bmp";
    cout << "<--  " << fFirst.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".wtf";
    cout << "-->  " << fNew.str() << endl;

    morphInterface.segmentationWATHERSHADE(fFirst.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::segmentationWatershadeMarkerImpl(std::string id1, std::string id2) {
    cout << "SEGMENTATION - WATHERSHADE MARKER" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << "./";
    fFirst << outputFigureName;
    fFirst << id1[0] - 96;
    fFirst << ".bmp";
    cout << "<--  " << fFirst.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".wtf";
    cout << "-->  " << fNew.str() << endl;

    //					if (marker1!=NULL)
    //					{
    stringstream m1;//create a stringstream
    m1 << "./";
    m1 << outputFigureName;
    m1 << id2[0] - 96;
    //m1 << marker1->getText()[0]-96;
    m1 << ".bmp";
    cout << "<--  " << m1.str() << endl;

    morphInterface.segmentationWATHERSHADE(m1.str(), fFirst.str(), fNew.str());
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

    marker1 = NULL;
    marker2 = NULL;
}