#include "stdafx.h"
#include "MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

int MorphDSLParser::toInt(const CommonTokenType* token) {
    int number;
    istringstream(token->getText()) >> number;

    return number;
}

double MorphDSLParser::toDouble(const CommonTokenType* token) {
    double number;
    istringstream(token->getText()) >> number;

    return number;
}

std::string MorphDSLParser::getNewImageNameFromId(std::string id) {
    auto idd = id[0];
    idd -= 96;

    stringstream fId;//create a stringstream
    fId << "./";
    fId << outputFigureName;
    fId << id[0] - 96;
    fId << ".bmp";

    return fId.str();
}

std::string MorphDSLParser::getNewImageName(bool noExtension) {
    auto cf = currentFigure->getText()[0];
    cf -= 96;

    stringstream fNew;
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;

    if (!noExtension) {
        fNew << ".bmp";
    }

    return fNew.str();
}

std::string MorphDSLParser::getNewImageNameWtf() {
    stringstream fNew;
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".wtf";

    return fNew.str();
}