#include "stdafx.h"
#include "../MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;


void MorphDSLParser::sqlImpl(Sql* sql) {

    std::cout << std::endl;
    std::cout << "keyword" << std::endl;
    std::cout << "\t" << SelectKw::kw[sql->selectKeyword] << std::endl;
    std::cout << std::endl;

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

    bool needToSubtract = false;

    std::string last = sql->fromId;
    char prev;
    for (auto i = 0; i < whereOmejitve.size(); i++) {
        SqlWhere* omejitev = whereOmejitve[i];

        std::cout << "\tkeyword: " << "\t" + omejitev->getKeyword() << std::endl;
        if (omejitev->isNestedSql()) {
            cout << "\t\tNested!" << std::endl;
        }
        else {
            cout << "\t\t\t" << RelOp::kw[omejitev->getRelOp()] << " " << omejitev->getVrednost() << std::endl;

            double vrednost = omejitev->getVrednost();

            switch (omejitev->getKeywordEnum()) {
                case SqlWhere::AREA:
                    if (needToSubtract) {
                        std::string prevS;
                        prevS += sql->fromId[0] + 1;

                        last = sql->fromId[0] + 1;

                        prev = last[0] + 1;
                        cout << "\t\t\t" << prev << " = " << "open(AREA," << vrednost << "," << sql->fromId << ")" << std::endl;
                        zadnjaSpremenljivka = prev;

                        openArea(vrednost, sql->fromId);

                        prev = char(last[0] + 2);
                        cout << "\t\t\t" << prev << " = " << "subtract(" << char(last[0] - 1) << "," << ++last[0] << ")" << std::endl;
                        zadnjaSpremenljivka = prev;

                        std::string sub = last;
                        subtractImpl(prevS, sub);

                        last[0]++;
                        needToSubtract = false;
                    }
                    else {
                        prev = char(last[0] + 1);
                        cout << "\t\t\t" << prev << " = " << "open(AREA," << vrednost << "," << sql->fromId << ")" << std::endl;

                        initNovaSpremenljivka(string(&prev, 1));

                        openArea(vrednost, sql->fromId);

                        needToSubtract = true;
                    }
                    break;
                case SqlWhere::RESPONSE: {
                    prev = char(last[0] + 1);
                    cout << "\t\t\t" << prev << " = " << "treshold(" << vrednost << ", " << last << ")" << std::endl;
                    zadnjaSpremenljivka = prev;

                    std::string subb = last;

                    tresholdImpl(vrednost, subb);
                    break;
                }
                case SqlWhere::INTERNAL_GRADIENT: {
                    std::string prevS = last;

                    prev = (last[0] + 1);

                    cout << "\t\t\t" << prev << " = " << "erode(BOX," << vrednost << "," << sql->fromId << ")" << std::endl;
                    zadnjaSpremenljivka = prev;

                    erodeBoxImpl(vrednost, sql->fromId);

                    prev = char(last[0] + 2);
                    cout << "\t\t\t" << prev << " = " << "subtract(" << char(last[0] - 1) << "," << ++last[0] << ")" << std::endl;
                    zadnjaSpremenljivka = prev;

                    std::string sub = last;

                    subtractImpl(prevS, sub);

                    last[0]++;
                    break;
                }
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
        prev = (char)(last[0] + 2);
        cout << "\t\t\t" << prev << " = " << "normalize(" << ++last[0] << ")" << std::endl;
        zadnjaSpremenljivka = prev;

        normalizeImpl();
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