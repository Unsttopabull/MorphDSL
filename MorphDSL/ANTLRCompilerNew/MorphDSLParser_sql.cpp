#include "stdafx.h"
#include "MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::sqlImpl(Sql* sql) {
    cout << "keyword" << std::endl;
    cout << "\t" << SelectKw::kw[sql->selectKeyword] << std::endl;
    cout << std::endl;

    cout << "funkcija" << std::endl;
    if (sql->selectFunkcija.empty()) {
        cout << "\t" << "ni funkcije nad keywordom" << std::endl;
    }
    else {
        cout << "\t" << sql->selectFunkcija << std::endl;
    }
    cout << std::endl;

    cout << "Nad katerim identifikatorjem izvajamo poizvedbo: " << sql->fromId << std::endl;
    cout << std::endl;

    cout << "Omejitve:" << std::endl;

    auto whereOmejitve = sql->getOmejitveUrejeno();
    for (auto i = 0; i < whereOmejitve.size(); i++) {
        SqlWhere* omejitev = whereOmejitve[i];

        std::cout << "\tkeyword: " << "\t" + omejitev->getKeyword() << std::endl;
        if (omejitev->isNestedSql()) {
            cout << "\t\tNested!" << std::endl;
        }
        else {
            cout << "\t\t" << omejitev->getVrednost() << std::endl;
        }
    }

    cout << endl;

    //auto keywords = sql->getUporabljeneKeyworde();
    //for (auto i = 0; i < keywords.size(); i++) {
    //    std::cout << "\tkeyword: " << keywords[i] << std::endl;

    //    auto omejitveNaKeyword = sql->getOmejtiveZaKeyword(keywords[i]);

    //    for (auto j = 0; j < omejitveNaKeyword.size(); j++) {
    //        auto curr = omejitveNaKeyword[j];
    //        if (curr->isNestedSql()) {
    //            std::cout << "\tnested : " << std::endl;
    //        }
    //        else {
    //            std::cout << "\t\t" << curr->getVrednost() << std::endl;
    //        }
    //    }

    //    std::cout << std::endl;
    //}
}
