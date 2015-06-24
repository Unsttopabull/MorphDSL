#include "stdafx.h"
#include "../MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::complementImpl(const CommonTokenType* id) {
    cout << "COMPLEMENT" << endl;

    string fLast = getImageNameFromId(id->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.complement(fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::unionImpl(const CommonTokenType* id1, const CommonTokenType* id2) {
    cout << "UNION" << endl;

    string fFirst = getImageNameFromId(id1->getText());
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.unionBB(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::intersectionImpl(const CommonTokenType* id1, const CommonTokenType* id2) {
    cout << "INTERSECTION" << endl;

    string fFirst = getImageNameFromId(id1->getText());
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2->getText());
    cout << "<--  " << fLast << endl;

    std::string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.intersection(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::withoutImpl(const CommonTokenType* id1, const CommonTokenType* id2) {
    cout << "WITHOUT" << endl;

    string fFirst = getImageNameFromId(id1->getText());
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.without(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::hitMissImpl(const CommonTokenType* id1, const CommonTokenType* id2) {
    cout << "HITMISS" << endl;

    string fFirst = getImageNameFromId(id1->getText());
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.hitmiss(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::boundaryImpl(const CommonTokenType* id1) {
    cout << "BOUNDARY" << endl;

    string fFirst = getImageNameFromId(id1->getText());
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.boundary(fFirst, fNew);
    cout << "---END" << endl;
}

