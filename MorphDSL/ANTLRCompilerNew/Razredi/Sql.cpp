#include "StdAfx.h"
#include "Sql.h"


Sql::Sql() {
}


Sql::~Sql() {
}

void Sql::dodajOmejitev(std::string keyword, SqlWhere* omejitev) {
    if (omejitve.find(keyword) != omejitve.end()) {
        omejitve[keyword].push_back(omejitev);
    }
    else {
        omejitve[keyword] = std::vector<SqlWhere*>();
        omejitve[keyword].push_back(omejitev);
    }
    auto test = omejitve[keyword];
}

std::vector<SqlWhere*> Sql::getOmejtiveZaKeyword(std::string keyword) {
    if (omejitve.find(keyword) != omejitve.end()) {
        return omejitve[keyword];
    }
    else {
        return std::vector<SqlWhere*>();
    }
}

std::vector<std::string> Sql::getUporabljeneKeyworde() {
    std::vector<std::string> keywords;
    for (auto it = omejitve.cbegin(); it != omejitve.cend(); ++it) {
        keywords.push_back((*it).first);
    }

    return keywords;
}