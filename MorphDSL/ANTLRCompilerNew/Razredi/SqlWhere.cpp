#include "StdAfx.h"
#include "SqlWhere.h"


SqlWhere::SqlWhere() {
}

SqlWhere::SqlWhere(RelacijskiOperatorji relOperator, double vrednost, std::string whereKw) {
    this->relOperator = relOperator;
    this->vrednost = vrednost;
    sql = NULL;
    whereKeyword = whereKw;
}

SqlWhere::SqlWhere(Sql* stavek, std::string whereKw) {
    sql = stavek;
    whereKeyword = whereKw;
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