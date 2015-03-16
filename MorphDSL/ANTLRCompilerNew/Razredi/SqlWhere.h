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
    SqlWhere(RelacijskiOperatorji relOperator, double vrednost, std::string whereKw);
    SqlWhere(Sql* stavek, std::string whereKw);

    ~SqlWhere();

    bool isNestedSql();
    Sql* getNestedSql();
    double getVrednost();

    std::string getKeyword() {
        return whereKeyword;
    }

private:
    Sql* sql;
    RelacijskiOperatorji relOperator;
    double vrednost;
    std::string whereKeyword;
};

