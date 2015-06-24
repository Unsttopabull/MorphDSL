#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::complementImpl(const ParserToken* id) {
    cout << "COMPLEMENT" << endl;

    string fLast = getImageNameFromId(id->getText());
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.complement(fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::unionImpl(const ParserToken* id1, const ParserToken* id2) {
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

void MorphDSLSemantics::intersectionImpl(const ParserToken* id1, const ParserToken* id2) {
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

void MorphDSLSemantics::withoutImpl(const ParserToken* id1, const ParserToken* id2) {
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

void MorphDSLSemantics::hitMissImpl(const ParserToken* id1, const ParserToken* id2) {
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

void MorphDSLSemantics::boundaryImpl(const ParserToken* id1) {
    cout << "BOUNDARY" << endl;

    string fFirst = getImageNameFromId(id1->getText());
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.boundary(fFirst, fNew);
    cout << "---END" << endl;
}

