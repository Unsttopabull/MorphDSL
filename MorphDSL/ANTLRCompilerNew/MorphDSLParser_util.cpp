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