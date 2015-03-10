#pragma once
#include "Sql.h"

namespace RelOp {
    enum RelacijskiOperatorji {
        ERR,
        LT,
        GT,
        EQ,
        NE,
        LE,
        GE
    };
}

using namespace RelOp;
using namespace std;

class SqlWhere {

public:
    SqlWhere();
    SqlWhere(RelacijskiOperatorji relOperator, double vrednost);
    SqlWhere(Sql* stavek);

    ~SqlWhere();

    bool isNestedSql();
    Sql* getNestedSql();
    double getVrednost();

private:
    Sql* sql;
    RelacijskiOperatorji relOperator;
    double vrednost;
};

