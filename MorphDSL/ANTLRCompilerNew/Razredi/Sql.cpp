#include "StdAfx.h"
#include "Sql.h"

using namespace LPM_MorphDSL;
using namespace std;

void Sql::dodajOmejitev(string keyword, SqlWhere* omejitev) {
    omejitveUrejeno.push_back(omejitev);

    if (omejitve.find(keyword) == omejitve.end()) {
        omejitve[keyword] = vector<SqlWhere*>();
    }

    omejitve[keyword].push_back(omejitev);
}

vector<SqlWhere*> Sql::getOmejtiveZaKeyword(string keyword) const {
    if (omejitve.find(keyword) != omejitve.end()) {
        return omejitve.at(keyword);
    }
    return vector<SqlWhere*>();
}

vector<string> Sql::getUporabljeneKeyworde() const{
    vector<string> keywords;
    for (auto it = omejitve.cbegin(); it != omejitve.cend(); ++it) {
        keywords.push_back((*it).first);
    }

    return keywords;
}

map<string, vector<SqlWhere*>> Sql::getOmejitve() const {
    return omejitve;
}

vector<SqlWhere*> Sql::getOmejitveUrejeno() const {
    return omejitveUrejeno;
}