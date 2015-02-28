#include "stdafx.h"
#include "MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::loadImpl(std::string id2, std::string currentFigure) {
    cout << "LOADING" << endl;

    stringstream fLast;//create a stringstream
    fLast << id2;
    cout << "<--  " << fLast.str() << endl;

    int firstLetter = fLast.str().find_last_of("/\\") + 1;
    int length = fLast.str().find_last_of(".") - firstLetter;
    outputFigureName = fLast.str().substr(firstLetter, length);
    cout << outputFigureName << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure[0] - 96; //96 => ASCII pred 'a', torej èe je prva èrka 'a' je rezultat 1
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    cout << "---END" << endl;

    morphInterface.LoadImg(fLast.str(), img);
    morphInterface.StoreImg(fNew.str(), img);
}

void MorphDSLParser::complementImpl(std::string id) {
    cout << "COMPLEMENT" << endl;

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

    morphInterface.complement(fLast.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::unionImpl(std::string id1, std::string id2) {
    cout << "UNION" << endl;

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

    morphInterface.unionBB(fFirst.str(), fLast.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::intersectionImpl(std::string id1, std::string id2) {
    cout << "INTERSECTION" << endl;

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

    morphInterface.intersection(fFirst.str(), fLast.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::withoutImpl(std::string id1, std::string id2) {
    cout << "WITHOUT" << endl;

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

    morphInterface.without(fFirst.str(), fLast.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::hitMissImpl(std::string id1, std::string id2) {
    cout << "HITMISS" << endl;

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

    morphInterface.hitmiss(fFirst.str(), fLast.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::boundaryImpl(std::string id1) {
    cout << "BOUNDARY" << endl;

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
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    morphInterface.boundary(fFirst.str(), fNew.str());
    cout << "---END" << endl;
}

