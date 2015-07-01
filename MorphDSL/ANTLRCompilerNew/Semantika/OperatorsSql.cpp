#include "stdafx.h"
#include "MorphDSLSemantics.h"

using namespace LPM_MorphDSL;
using namespace std;


void MorphDSLSemantics::sqlImpl(Sql* sql, const string& spremenljivka) {

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
    for (size_t i = 0; i < whereOmejitve.size(); i++) {
        SqlWhere* omejitev = whereOmejitve[i];
        RelacijskiOperatorji relOp = omejitev->getRelOp();

        cout << "\tkeyword: " << "\t" + omejitev->getKeyword() << endl;
        if (omejitev->isNestedSql()) {
            cout << "\t\tNested!" << endl;
        }
        else {
            cout << "\t\t\t" << kw[omejitev->getRelOp()] << " " << omejitev->getVrednost() << endl;

            double vrednost = omejitev->getVrednost();

            switch (omejitev->getKeywordEnum()) {
                case SqlWhere::AREA:{
                    areaCount++;

                    if (areaCount % 2 == 0) {
                        newSpr = initInternalVariable(sql->fromId, "sql");

                        //cout << "\t\t\t" << newSpr << " = " << "open(AREA," << vrednost << "," << last << ")" << endl;
                        //openAreaNoCheck(vrednost, last);

                        cout << "\t\t\t" << newSpr << " = " << "open(AREA," << vrednost << "," << sql->fromId << ")" << endl;
                        openAreaNoCheck(vrednost, sql->fromId);

                        string newSpr2 = initInternalVariable(sql->fromId, "sql");
                        cout << "\t\t\t" << newSpr2 << " = " << "subtract(" << last << "," << newSpr << ")" << endl;
                        subtractNoCheck(last, newSpr);

                        last = newSpr2;
                    }
                    else {
                        newSpr = initInternalVariable(sql->fromId, "sql");

                        //cout << "\t\t\t" << newSpr << " = " << "open(AREA," << vrednost << "," << last << ")" << endl;
                        //openAreaNoCheck(vrednost, last);

                        cout << "\t\t\t" << newSpr << " = " << "open(AREA," << vrednost << "," << sql->fromId << ")" << endl;
                        openAreaNoCheck(vrednost, sql->fromId);

                        last = newSpr;
                    }
                    break;
                }
                case SqlWhere::RESPONSE:{
                    if (relOp == RelOp::LT) {
                        newSpr = initInternalVariable(sql->fromId, "sql");

                        cout << "\t\t\t" << newSpr << " = " << "multipy(" << -1 << ", " << last << ")" << endl;
                        multiplyNoCheck(-1, last); // e = multiply(-1, d)

                        string newSpr2 = initInternalVariable(sql->fromId, "sql");
                        cout << "\t\t\t" << newSpr2 << " = " << "treshold(" << vrednost << ", " << newSpr << ")" << endl;
                        tresholdImplNoCheck(vrednost, newSpr); //f = treshold(-5, e);

                        string newSpr3 = initInternalVariable(sql->fromId, "sql");
                        cout << "\t\t\t" << newSpr3 << " = " << "multipy(" << -1 << ", " << newSpr2 << ")" << endl;
                        multiplyNoCheck(-1, newSpr2); //g = multipy(-1, f)

                        last = newSpr3;
                    }
                    else if (relOp == RelOp::GT) {
                        newSpr = initInternalVariable(sql->fromId, "sql");
                        cout << "\t\t\t" << newSpr << " = " << "treshold(" << vrednost << ", " << last << ")" << endl;
                        tresholdImplNoCheck(vrednost, last);

                        last = newSpr;
                    }
                    break;
                }
                case SqlWhere::INTERNAL_GRADIENT:{
                    //TODO
                    newSpr = initInternalVariable(sql->fromId, "sql");

                    cout << "\t\t\t" << newSpr << " = " << "erode(BOX(" << vrednost << "), " << last << ")" << endl;
                    erodeBoxNoCheck(vrednost, last);

                    string newSpr2 = initInternalVariable(sql->fromId, "sql");
                    cout << "\t\t\t" << newSpr2 << " = " << "subtract(" << last << ", " << newSpr << ")" << endl;
                    subtractNoCheck(last, newSpr);

                    last = newSpr2;
                    break;
                }
                case SqlWhere::EXTERNAL_GRADIENT:
                    //TODO
                    break;
                case SqlWhere::VOLUMENT:
                    //TODO
                    break;
                case SqlWhere::OKROGLOST:
                    //TODO
                    break;
                case SqlWhere::ATRIBUTE:
                    //TODO
                    break;
                default:
                    break;
            }
        }
        cout << endl;
    }

    if (sql->selectFunkcija == "normalize") {
        newSpr = initInternalVariable(sql->fromId, "sql");
        cout << "\t\t\t" << newSpr << " = " << "normalize(" << last << ")" << endl;

        normalizeImpl();

        last = newSpr;
    }

    cout << endl;

    if (!spremenljivka.empty()) {
        Spremenljivka* s = getVariableFromId(last);
        switch (sql->selectKeyword) {
            case SelectKw::Star:
                //
                break;
            case SelectKw::Mask:
                s->setMask(s->getSlika());
                break;
            case SelectKw::Set: 
                break;
            case SelectKw::Attribute: 
                break;
            case SelectKw::Okroglost: 
                break;
            case SelectKw::Volument: 
                break;
            case SelectKw::InternalGradient: 
                break;
            case SelectKw::ExternalGradient: 
                break;
            default: 
                cout << "ERROR: Neveljavni kljuèna beseda SELECT" << endl;
                parser->set_failedflag(true);
                return;
        }

        imeSlikeZaSpremenljivko[spremenljivka] = s;

        cout << "\t\t\t" << spremenljivka << " = " << last << endl;
    }

    clearTempVariablesCategory("sql");

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