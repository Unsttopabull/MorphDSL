#pragma once
#include <map>
#include <string>
#include <vector>
#include "Enums.h"

namespace LPM_MorphDSL {
    class SqlWhere;

    class Sql {
    public:

        std::string fromId;
        SelectKw::Keyword selectKeyword;
        std::string selectFunkcija;

        void nekaj() {
        }

        void dodajOmejitev(std::string keyword, SqlWhere* omejitev);
        std::vector<SqlWhere*> getOmejtiveZaKeyword(std::string keyword) const;
        std::vector<std::string> getUporabljeneKeyworde() const;
        std::map<std::string, std::vector<SqlWhere*>> getOmejitve() const;

        std::vector<SqlWhere*> getOmejitveUrejeno() const {
            return omejitveUrejeno;
        }

    private:
        std::vector<SqlWhere*> omejitveUrejeno;
        std::map<std::string, std::vector<SqlWhere*>> omejitve;
    };

}
