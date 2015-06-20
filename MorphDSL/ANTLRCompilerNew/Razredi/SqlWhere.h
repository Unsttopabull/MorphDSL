#pragma once
#include "Sql.h"

using namespace RelOp;
using namespace std;

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
    SqlWhere(RelacijskiOperatorji relOperator, double vrednost, std::string whereKw);
    SqlWhere(RelacijskiOperatorji relOperator, double vrednost, Keyword whereKw);
    SqlWhere(Sql* stavek, std::string whereKw);

    ~SqlWhere();

    bool isNestedSql();
    Sql* getNestedSql();
    double getVrednost();

    std::string getKeyword() {
        return whereKeyword;
    }

    void checkKeywordEnum() {
        auto kw = preslikava.find(whereKeyword);
        if (kw != preslikava.end()) {
            //vrnemo enum kljuè
            enumKeyword = kw->second;
            return;
        }

        enumKeyword = SqlWhere::ERR;
    }

    Keyword getKeywordEnum() {
        return enumKeyword;
    }

    RelacijskiOperatorji getRelOp() {
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
    std::string whereKeyword;
    Keyword enumKeyword;
    std::map<std::string, Keyword> preslikava;
};

