#pragma once
#include "../Util/Spremenljivka.h"
#include "../Util/Identifier.h"
#include "../../ANTLRInterface/CompilerSemanticInterface.h"
#include <map>

#ifndef _MorphDSLParser_H
    #include "../MorphDSLParser.hpp"
#endif

namespace LPM_MorphDSL {   
    typedef MorphDSLParser::CommonTokenType ParserToken;

    class MorphDSLSemantics {

    private:
        MorphDSLParser* parser;

        CompilerSemanticInterface morphInterface;
        vector<vector<double>> img;
        map<string, vector<double>> vect;
        map<string, Spremenljivka*> imeSlikeZaSpremenljivko;
        map<string, vector<Spremenljivka*>> tempSpremenljivke;
        string imeIzhodneSlike;
        string zadnjaSpremenljivka;
        string predZadnjaSpremenljivka;
        int imageCounter;
        int tempCnt;

        //Util
        string getImageNameFromId(string id, SubIdentifier subId = NONE);
        string getImageNameFromId(Identifier* id);
        string getNewImageName(bool noExtension = false);
        string getNewImageNameWtf();
        void variableToFileName(std::string spremenljivka, string kategorija);

        bool checkVariablesExist(string id1, string id2);
        bool checkVariableExist(string id);

        bool checkVariablesExist(const Identifier* id1, const Identifier* id2);
        bool checkVariableExist(const Identifier* id1);

        Spremenljivka* getVariableFromId(string id);

        string initInternalVariable(string spremenljivka, std::string kategorija);
        void clearTempVariablesCategory(string kategorija);

#pragma region NO CHECK

        //operators BB
        void complementNoCheck(string idStr);
        void unionNoCheck(string id1Str, string id2Str);
        void intersectionNoCheck(string id1Str, string id2Str);
        void withoutNoCheck(string id1Str, string id2Str);
        void hitMissNoCheck(string id1Str, string id2Str);
        void boundaryNoCheck(string idStr);

        //operatorsGG
        void negateNoCheck(string idStr);
        void multiplyNoCheck(double num, string idStr);
        void multiplyNoCheck(string id1Str, string id2Str);
        void cropNoCheck(string id1Str, double lowBound, double highBound);
        void subtractNoCheck(string id1Str, string id2Str);
        void gradientInternalNoCheck(string id1Str);
        void gradientExternalNoCheck(string id1Str);
        void diferentialProfilesMorphologicalNoCheck(string id1Str, string id2Str, vector<double> vector);
        void differentialProfilesAttributeNoCheck(string id1Str, string id2Str, vector<double> vector);
        void mappingDapNoCheck(string id2Str, string id1Str, vector<double> vector);
        void segmentationMsls1NoCheck(string id2Str, string id1Str, vector<double> vector);
        void segmentationMsls2NoCheck(string id1Str, string id2Str, vector<double> vector);
        void segmentatonWatershadeNoCheck(string idStr);
        void segmentationWatershadeMarkerNoCheck(string id1Str, string id2Str);

        //operatorsBOX
        void erodeBoxNoCheck(double number, string idStr);
        void dilateBoxNoCheck(double number, string idStr);
        void openBoxNoCheck(double number, string idStr);
        void closeBoxNoCheck(double number, string idStr);

        //operatorsRECONSTRUCTION
        void erodeNoCheck(string id1Str, string id2Str);
        void dilateNoCheck(string id1Str, string id2Str);
        void openNoCheck(double number, string idStr);
        void closeNoCheck(double number, string idStr);

        //operatorsAREA
        void openAreaNoCheck(double number, string id);
        void closeAreaNoCheck(double number, string id);

        //operatorsATTRIBUTE
        void openAttributeNoCheck(string attribute, double number, string id2);
        void closeAttributeNoCheck(string attribute, double number, string id2);

        //operatorsBG
        void distanceTransformNoCheck(string idStr);

        //operatorsGB
        void tresholdImplNoCheck(double number, string id);

#pragma endregion 

    public:
        explicit MorphDSLSemantics(MorphDSLParser* p);

        void setZadnjaSpremenljivka(string spr) {
            predZadnjaSpremenljivka = zadnjaSpremenljivka;
            zadnjaSpremenljivka = spr;
        }

        string getZadnjaSpremenljivka() {
            return zadnjaSpremenljivka;
        }

        void insertToVect(pair<string, vector<double>> pair) {
            vect.insert(vect.begin(), pair);
        }

        void loadImpl(string id2, string currentFigure);
        void initNovaSpremenljivka(string novaSpr);

#pragma region Implementacije

        //operatorsBB
        void complementImpl(const Identifier* id);
        void unionImpl(const Identifier* id1, const Identifier* id2);
        void intersectionImpl(const Identifier* id1, const Identifier* id2);
        void withoutImpl(const Identifier* id1, const Identifier* id2);
        void hitMissImpl(const Identifier* id1, const Identifier* id2);
        void boundaryImpl(const Identifier* id);

        //operatorsGG
        void negateImpl(const Identifier* id);
        void normalizeImpl();
        void multiplyImpl(const Identifier* id, double num);
        void multiplyImpl(double num, const Identifier* id);
        void multiplyImpl(const Identifier* id1, const Identifier* id2);
        void cropImpl(const Identifier* id, double lowBound, double highBound);
        void subtractImpl(const Identifier* id1, const Identifier* id2);
        void gradientInternalImpl(const Identifier* id);
        void gradientExternalImpl(const Identifier* id);
        void diferentialProfilesMorphologicalImpl(const Identifier* id1, const Identifier* id2);
        void diferentialProfilesAttributeImpl(const Identifier* id1, const Identifier* id2);
        void mappingDmpNoCheck(string id1Str, string id2Str, vector<double> vector);
        void mappingDmpImpl(const Identifier* id1, const Identifier* id2);
        void mappingDapImpl(const Identifier* id1, const Identifier* id2);
        void segmentationMsls1Impl(const Identifier* id1, const Identifier* id2);
        void segmentationMsls2Impl(const Identifier* id1, const Identifier* id2);
        void segmentationWatershadeImpl(const Identifier* id1);
        void segmentationWatershadeMarkerImpl(const Identifier* id1, const Identifier* id2);

        //operatorsBOX
        void erodeBoxImpl(double number, const Identifier* id);
        void dilateBoxImpl(double number, const Identifier* id);
        void openBoxImpl(double number, const Identifier* id);
        void closeBoxImpl(double number, const Identifier* id);

        //operatorsRECONSTRUCTION
        void erodeImpl(const Identifier* id1, const Identifier* id2);
        void dilateImpl(const Identifier* id1, const Identifier* id2);
        void openImpl(double number, const Identifier* id);
        void closeImpl(double number, const Identifier* id);

        //operatorsAREA
        void openArea(double number, const Identifier* id);
        void closeArea(double number, const Identifier* id);

        //operatorsATTRIBUTE
        void openAttribute(const string attributeName, double number, const Identifier* id2);
        void closeAttribute(const string attributeName, double number, const Identifier* id2);

        //operatorsBG
        void distanceTransformImpl(const Identifier* id);

        //operatorsGB
        void tresholdImpl(double number, const Identifier* id);

        //sql
        void sqlImpl(Sql* sql, string spremenljivka);

#pragma endregion 
    };
}