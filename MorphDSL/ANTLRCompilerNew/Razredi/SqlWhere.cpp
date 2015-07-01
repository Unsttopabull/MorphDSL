#include "StdAfx.h"
#include "SqlWhere.h"

using namespace LPM_MorphDSL;

SqlWhere::SqlWhere() {
    init();
}

SqlWhere::SqlWhere(RelacijskiOperatorji relOperator, double vrednost, std::string whereKw) {
    init();

    this->relOperator = relOperator;
    this->vrednost = vrednost;
    sql = NULL;
    whereKeyword = whereKw;

    checkKeywordEnum();
}

SqlWhere::SqlWhere(RelacijskiOperatorji relOperator, double vrednost, Keyword whereKw) {
    init();

    this->relOperator = relOperator;
    this->vrednost = vrednost;
    sql = NULL;
    enumKeyword = whereKw;

    switch (whereKw) {
        case AREA:
            whereKeyword = "area";
            break;
        case RESPONSE:
            whereKeyword = "response";
            break;
        case INTERNAL_GRADIENT:
            whereKeyword = "internal_gradient";
            break;
        case EXTERNAL_GRADIENT:
            whereKeyword = "external_gradient";
            break;
        case VOLUMENT:
            whereKeyword = "volument";
            break;
        case OKROGLOST:
            whereKeyword = "okroglost";
            break;
        case ATRIBUTE:
            whereKeyword = "atribute";
            break;
        default:
            whereKeyword = "ERR";
            break;
    }
}

SqlWhere::SqlWhere(Sql* stavek, std::string whereKw) {
    sql = stavek;
    whereKeyword = whereKw;

    checkKeywordEnum();
}

SqlWhere::~SqlWhere() {
}

bool SqlWhere::isNestedSql() {
    return sql != NULL;
}

Sql* SqlWhere::getNestedSql() {
    return sql;
}

double SqlWhere::getVrednost() {
    return vrednost;
}