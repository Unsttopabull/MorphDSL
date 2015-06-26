#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::complementNoCheck(string idStr) {
    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.complement(fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::complementImpl(const ParserToken* id) {
    cout << "COMPLEMENT" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    complementNoCheck(id->getText());
}

void MorphDSLSemantics::unionNoCheck(string id1Str, string id2Str) {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2Str);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.unionBB(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::unionImpl(const ParserToken* id1, const ParserToken* id2) {
    cout << "UNION" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    unionNoCheck(id1->getText(), id2->getText());
}

void MorphDSLSemantics::intersectionNoCheck(string id1Str, string id2Str) {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2Str);
    cout << "<--  " << fLast << endl;

    std::string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.intersection(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::intersectionImpl(const ParserToken* id1, const ParserToken* id2) {
    cout << "INTERSECTION" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    intersectionNoCheck(id1->getText(), id2->getText());
}

void MorphDSLSemantics::withoutNoCheck(string id1Str, string id2Str) {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2Str);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.without(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::withoutImpl(const ParserToken* id1, const ParserToken* id2) {
    cout << "WITHOUT" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    withoutNoCheck(id1->getText(), id2->getText());
}

void MorphDSLSemantics::hitMissNoCheck(string id1Str, string id2Str) {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2Str);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.hitmiss(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::hitMissImpl(const ParserToken* id1, const ParserToken* id2) {
    cout << "HITMISS" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    hitMissNoCheck(id1->getText(), id2->getText());
}

void MorphDSLSemantics::boundaryNoCheck(string idStr) {
    string fFirst = getImageNameFromId(idStr);
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.boundary(fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::boundaryImpl(const ParserToken* id1) {
    cout << "BOUNDARY" << endl;

    if (!checkVariableExist(id1)) {
        return;
    }

    boundaryNoCheck(id1->getText());
}

