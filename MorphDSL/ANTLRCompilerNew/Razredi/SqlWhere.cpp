#include "StdAfx.h"
#include "SqlWhere.h"


SqlWhere::SqlWhere() {
}

SqlWhere::SqlWhere(RelacijskiOperatorji relOperator, double vrednost) {
    this->relOperator = relOperator;
    this->vrednost = vrednost;
    sql = NULL;
}

SqlWhere::SqlWhere(Sql* stavek) {
    sql = stavek;
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