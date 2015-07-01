#pragma once
#include "Sql.h"

using namespace RelOp;
using namespace std;

namespace LPM_MorphDSL {

    class SqlWhere {

    public:

        enum Keyword {
            ERR,
            AREA,
            RESPONSE,
            INTERNAL_GRADIENT,
            EXTERNAL_GRADIENT,
            VOLUMENT,
            OKROGLOST,
            ATRIBUTE
        };

        SqlWhere();
        SqlWhere(RelacijskiOperatorji relOperator, double vrednost, string whereKw);
        SqlWhere(RelacijskiOperatorji relOperator, double vrednost, Keyword whereKw);
        SqlWhere(Sql* stavek, string whereKw);

        ~SqlWhere();

        bool isNestedSql();
        Sql* getNestedSql();
        double getVrednost();

        string getKeyword() {
            return whereKeyword;
        }

        void checkKeywordEnum() {
            auto kw = preslikava.find(whereKeyword);
            if (kw != preslikava.end()) {
                //vrnemo enum kljuè
                enumKeyword = kw->second;
                return;
            }

            enumKeyword = ERR;
        }

        Keyword getKeywordEnum() const {
            return enumKeyword;
        }

        RelacijskiOperatorji getRelOp() const {
            return relOperator;
        }

        void init() {
            preslikava["area"] = AREA;
            preslikava["response"] = RESPONSE;
            preslikava["internal_gradient"] = INTERNAL_GRADIENT;
            preslikava["external_gradient"] = EXTERNAL_GRADIENT;
            preslikava["volument"] = VOLUMENT;
            preslikava["okrloglost"] = OKROGLOST;
            preslikava["atribute"] = ATRIBUTE;
        }

    private:
        Sql* sql;
        RelacijskiOperatorji relOperator;
        double vrednost;
        string whereKeyword;
        Keyword enumKeyword;
        map<string, Keyword> preslikava;
    };

}