#pragma once
#include <map>
#include <string>
#include <vector>

class SqlWhere;

namespace SelectKw {
    enum Keyword {
        Error,
        Star,
        Mask,
        Set,
        Attribute,
        Okroglost,
        Volument,
        InternalGradient,
        ExternalGradient
    };

    static std::string kw[] = { "Error", "Star", "Mask", "Set", "Attribute", "Okroglost", "Volument", "InternalGradient", "ExternalGradient" };
}

class Sql {
public:
    Sql();
    ~Sql();

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

