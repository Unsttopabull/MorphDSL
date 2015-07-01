#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLSemantics::openAttributeNoCheck(const string& attribute, const double number, const string& id2) {
    cout << "<--  " << attribute << endl;

    string fLast = getImageNameFromId(id2);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created

    morphInterface.open(attribute, number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::openAttribute(const string& attributeName, const double number, const Identifier& id2) {
    cout << "OPEN - ATTRIBUTE" << endl;

    string id2Str = id2.getText();
    if (!checkVariableExist(id2Str)) {
        return;
    }

    openAttributeNoCheck(attributeName, number, id2Str);
}

void MorphDSLSemantics::closeAttributeNoCheck(const string& attribute, const double number, const string& id2) {
    cout << "<--  " << attribute << endl;

    string fLast = getImageNameFromId(id2);
    cout << "<--  " << fLast << endl;

    string fNew = getLastVariableImageName();
    cout << "-->  " << fNew << endl;

    //when 5 pics created

    morphInterface.close(attribute, number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLSemantics::closeAttribute(const string& attributeName, const double number, const Identifier& id2) {
    cout << "CLOSE - ATTRIBUTE" << endl;

    string id2Str = id2.getText();
    if (!checkVariableExist(id2Str)) {
        return;
    }

    closeAttributeNoCheck(attributeName, number, id2Str);
}