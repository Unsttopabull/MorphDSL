#pragma once
#include "../Razredi/Enums.h"

#ifndef _MorphDSLParser_H
#include "../MorphDSLParser.hpp"
#endif

namespace LPM_MorphDSL {
    using namespace SubId;

    typedef MorphDSLParser::CommonTokenType ParserToken;

    class Identifier {
    public:

        Identifier() {
        }

        Identifier(const ParserToken* token, SubIdentifier subId) {
            this->token = token;
            this->subId = subId;
        }

        Identifier(const ParserToken* token, string subId) {
            this->token = token;
            //TODO parse subID
            this->subId = NONE;
        }

        explicit Identifier(const ParserToken* token) {
            this->token = token;
            this->subId = NONE;
        }

        const ParserToken* getToken() const {
            return token;
        }

        SubIdentifier getSubId() const {
            return subId;
        }

        void setSubId(SubIdentifier subId) {
            this->subId = subId;
        }

        string getText() const {
            return token->getText();
        }

    private:
        const ParserToken* token;
        SubIdentifier subId;
    };
}
