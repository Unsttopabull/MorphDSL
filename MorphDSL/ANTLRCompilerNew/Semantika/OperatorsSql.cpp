#include "stdafx.h"
#include "../MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;


void MorphDSLParser::sqlImpl(Sql* sql, string spremenljivka) {

    cout << endl;
    cout << "keyword" << endl;
    cout << "\t" << SelectKw::kw[sql->selectKeyword] << endl;
    cout << endl;

    cout << "funkcija" << endl;
    if (sql->selectFunkcija.empty()) {
        cout << "\t" << "ni funkcije nad keywordom" << endl;
    }
    else {
        cout << "\t" << sql->selectFunkcija << endl;
    }
    cout << endl;

    //cout << "Nad katerim identifikatorjem izvajamo poizvedbo: " << sql->fromId << std::endl;
    cout << endl;

    cout << "Omejitve:" << endl;

    auto whereOmejitve = sql->getOmejitveUrejeno();

    int areaCount = 0;

    string last = sql->fromId;
    string newSpr;
    for (auto i = 0; i < whereOmejitve.size(); i++) {
        SqlWhere* omejitev = whereOmejitve[i];

        cout << "\tkeyword: " << "\t" + omejitev->getKeyword() << endl;
        if (omejitev->isNestedSql()) {
            cout << "\t\tNested!" << endl;
        }
        else {
            cout << "\t\t\t" << kw[omejitev->getRelOp()] << " " << omejitev->getVrednost() << endl;

            double vrednost = omejitev->getVrednost();

            switch (omejitev->getKeywordEnum()) {
                case SqlWhere::AREA:
                    areaCount++;

                    if (areaCount % 2 == 0) {
                        newSpr = initInternalVariable(sql->fromId);

                        cout << "\t\t\t" << newSpr << " = " << "open(AREA," << vrednost << "," << last << ")" << endl;
                        //openAreaNoCheck(vrednost, last);

                        string newSpr2 = initInternalVariable(sql->fromId);
                        cout << "\t\t\t" << newSpr2 << " = " << "subtract(" << last << "," << newSpr << ")" << endl;
                        //subtractImplNoCheck(last, newSpr);

                        last = newSpr2;
                    }
                    else {
                        newSpr = initInternalVariable(sql->fromId);

                        cout << "\t\t\t" << newSpr << " = " << "open(AREA," << vrednost << "," << last << ")" << endl;
                        //openAreaNoCheck(vrednost, last);

                        last = newSpr;
                    }
                    break;
                case SqlWhere::RESPONSE:
                    newSpr = initInternalVariable(sql->fromId);

                    cout << "\t\t\t" << newSpr << " = " << "treshold(" << vrednost << ", " << last << ")" << endl;
                    //tresholdImplNoCheck(vrednost, last);

                    last = newSpr;
                    break;
                case SqlWhere::INTERNAL_GRADIENT: 
                    break;
                case SqlWhere::EXTERNAL_GRADIENT:
                    break;
                case SqlWhere::VOLUMENT:
                    break;
                case SqlWhere::OKROGLOST:
                    break;
                case SqlWhere::ATRIBUTE:
                    break;
                default:
                    break;
            }
        }
        cout << endl;
    }

    if (sql->selectFunkcija == "normalize") {
        newSpr = initInternalVariable(sql->fromId);
        cout << "\t\t\t" << newSpr << " = " << "normalize(" << last << ")" << endl;

        //normalizeImpl();

        last = newSpr;
    }

    cout << endl;

    if (!spremenljivka.empty()) {
        Spremenljivka s = getVariableFromId(last);
        imeSlikeZaSpremenljivko[spremenljivka] = s;

        cout << "\t\t\t" << spremenljivka << " = " << last << endl;
    }

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