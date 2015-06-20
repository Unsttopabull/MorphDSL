#pragma once
#include <map>
#include <string>
#include <vector>
#include "Enums.h"

class SqlWhere;

class Sql {
public:

    SelectKw::Keyword selectKeyword;
    std::string fromId;
    std::string selectFunkcija;

    void nekaj() {
    }

    void dodajOmejitev(std::string keyword, SqlWhere* omejitev);
    std::vector<SqlWhere*> getOmejtiveZaKeyword(std::string keyword);
    std::vector<std::string> getUporabljeneKeyworde();
    std::map<std::string, std::vector<SqlWhere*>> getOmejitve();

    std::vector<SqlWhere*> getOmejitveUrejeno() {
        return omejitveUrejeno;
    }

private:
    std::vector<SqlWhere*> omejitveUrejeno;
    std::map<std::string, std::vector<SqlWhere*>> omejitve;
};

