#include "stdafx.h"
#include "../MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::complementImpl(std::string id) {
    cout << "COMPLEMENT" << endl;

    string fLast = getImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.complement(fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::unionImpl(std::string id1, std::string id2) {
    cout << "UNION" << endl;

    string fFirst = getImageNameFromId(id1);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.unionBB(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::intersectionImpl(std::string id1, std::string id2) {
    cout << "INTERSECTION" << endl;

    string fFirst = getImageNameFromId(id1);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2);
    cout << "<--  " << fLast << endl;

    std::string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.intersection(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::withoutImpl(std::string id1, std::string id2) {
    cout << "WITHOUT" << endl;

    string fFirst = getImageNameFromId(id1);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.without(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::hitMissImpl(std::string id1, std::string id2) {
    cout << "HITMISS" << endl;

    string fFirst = getImageNameFromId(id1);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.hitmiss(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::boundaryImpl(std::string id1) {
    cout << "BOUNDARY" << endl;

    string fFirst = getImageNameFromId(id1);
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.boundary(fFirst, fNew);
    cout << "---END" << endl;
}

