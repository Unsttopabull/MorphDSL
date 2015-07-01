#pragma once
#include <map>
#include <string>
#include <vector>
#include "Enums.h"

using namespace std;

namespace LPM_MorphDSL {
    class SqlWhere;

    class Sql {
      public:

        string fromId;
        SelectKw::Keyword selectKeyword;
        string selectFunkcija;

        void nekaj() {
        }

        void dodajOmejitev(string keyword, SqlWhere* omejitev);

        vector<SqlWhere*> getOmejtiveZaKeyword(string keyword) const;
        vector<string> getUporabljeneKeyworde() const;
        map<string, vector<SqlWhere*>> getOmejitve() const;

        vector<SqlWhere*> getOmejitveUrejeno() const;

      private:
        vector<SqlWhere*> omejitveUrejeno;
        map<string, vector<SqlWhere*>> omejitve;
    };

}
