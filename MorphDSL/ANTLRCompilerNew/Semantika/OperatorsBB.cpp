#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::complementNoCheck(const string& idStr) const {
    string fLast = getImageNameFromId(idStr);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.complement(fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::complementImpl(const Identifier& id) const {
    cout << "COMPLEMENT" << endl;

    if (!checkVariableExist(id)) {
        return;
    }

    complementNoCheck(id.getText());
}

void MorphDSLSemantics::unionNoCheck(const string& id1Str, const string& id2Str) const {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2Str);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.unionBB(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::unionImpl(const Identifier& id1, const Identifier& id2) const {
    cout << "UNION" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    unionNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::intersectionNoCheck(const string& id1Str, const string& id2Str) const {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2Str);
    cout << "<--  " << fLast << endl;

    std::string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.intersection(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::intersectionImpl(const Identifier& id1, const Identifier& id2) const {
    cout << "INTERSECTION" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    intersectionNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::withoutNoCheck(const string& id1Str, const string& id2Str) const {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2Str);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.without(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::withoutImpl(const Identifier& id1, const Identifier& id2) const {
    cout << "WITHOUT" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    withoutNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::hitMissNoCheck(const string& id1Str, const string& id2Str) const {
    string fFirst = getImageNameFromId(id1Str);
    cout << "<--  " << fFirst << endl;

    string fLast = getImageNameFromId(id2Str);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.hitmiss(fFirst, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::hitMissImpl(const Identifier& id1, const Identifier& id2) const {
    cout << "HITMISS" << endl;

    if (!checkVariablesExist(id1, id2)) {
        return;
    }

    hitMissNoCheck(id1.getText(), id2.getText());
}

void MorphDSLSemantics::boundaryNoCheck(const string& idStr) const {
    string fFirst = getImageNameFromId(idStr);
    cout << "<--  " << fFirst << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.boundary(fFirst, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::boundaryImpl(const Identifier& id1) const {
    cout << "BOUNDARY" << endl;

    if (!checkVariableExist(id1)) {
        return;
    }

    boundaryNoCheck(id1.getText());
}

