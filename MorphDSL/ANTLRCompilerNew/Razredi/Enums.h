#pragma once

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

    static std::string kw[] = { "ERR", "<", ">", "==", "¨!=", "<=", ">=" };
}

namespace SubId {
    enum SubIdentifier {
        NONE,
        MASK,
        SET,
        ATTRIBUTE,
        OKROGLOST,
        VOLUMENT
    };
}