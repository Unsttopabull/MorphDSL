#pragma once
#include "../Util/Spremenljivka.h"
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
        //const CommonTokenType*    currentFigure;
        vector<vector<double>> img;
        map<string, vector<double>> vect;
        map<string, Spremenljivka> imeSlikeZaSpremenljivko;
        string imeIzhodneSlike;
        string zadnjaSpremenljivka;
        int imageCounter;
        int tempCnt;

        //Util
        string getImageNameFromId(string id);
        string getNewImageName(bool noExtension = false);
        string getNewImageNameWtf();

        void variableToFileName(string spremenljivka, bool isTemp = false);

        bool checkVariablesExist(string id1, string id2);
        bool checkVariableExist(string id);

        bool checkVariablesExist(const ParserToken* id1, const ParserToken* id2);
        bool checkVariableExist(const ParserToken* id1);

        Spremenljivka getVariableFromId(string id);

        string initInternalVariable(string spremenljivka);

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
        void subtractImplNoCheck(string id1Str, string id2Str);
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
        void complementImpl(const ParserToken* id);
        void unionImpl(const ParserToken* id1, const ParserToken* id2);
        void intersectionImpl(const ParserToken* id1, const ParserToken* id2);
        void withoutImpl(const ParserToken* id1, const ParserToken* id2);
        void hitMissImpl(const ParserToken* id1, const ParserToken* id2);
        void boundaryImpl(const ParserToken* id);

        //operatorsGG
        void negateImpl(const ParserToken* id);
        void normalizeImpl();
        void multiplyImpl(const ParserToken* id, double num);
        void multiplyImpl(double num, const ParserToken* id);
        void multiplyImpl(const ParserToken* id1, const ParserToken* id2);
        void cropImpl(const ParserToken* id, double lowBound, double highBound);
        void subtractImpl(const ParserToken* id1, const ParserToken* id2);
        void gradientInternalImpl(const ParserToken* id);
        void gradientExternalImpl(const ParserToken* id);
        void diferentialProfilesMorphologicalImpl(const ParserToken* id1, const ParserToken* id2);
        void diferentialProfilesAttributeImpl(const ParserToken* id1, const ParserToken* id2);
        void mappingDmpNoCheck(string id1Str, string id2Str, vector<double> vector);
        void mappingDmpImpl(const ParserToken* id1, const ParserToken* id2);
        void mappingDapImpl(const ParserToken* id1, const ParserToken* id2);
        void segmentationMsls1Impl(const ParserToken* id1, const ParserToken* id2);
        void segmentationMsls2Impl(const ParserToken* id1, const ParserToken* id2);
        void segmentationWatershadeImpl(const ParserToken* id1);
        void segmentationWatershadeMarkerImpl(const ParserToken* id1, const ParserToken* id2);

        //operatorsBOX
        void erodeBoxImpl(double number, const ParserToken* id);
        void dilateBoxImpl(double number, const ParserToken* id);
        void openBoxImpl(double number, const ParserToken* id);
        void closeBoxImpl(double number, const ParserToken* id);

        //operatorsRECONSTRUCTION
        void erodeImpl(const ParserToken* id1, const ParserToken* id2);
        void dilateImpl(const ParserToken* id1, const ParserToken* id2);
        void openImpl(double number, const ParserToken* id);
        void closeImpl(double number, const ParserToken* id);

        //operatorsAREA
        void openArea(double number, const ParserToken* id);
        void closeArea(double number, const ParserToken* id);

        //operatorsATTRIBUTE
        void openAttribute(const ParserToken* attribute, double number, const ParserToken* id2);
        void closeAttribute(const ParserToken* attribute, double number, const ParserToken* id2);

        //operatorsBG
        void distanceTransformImpl(const ParserToken* id);

        //operatorsGB
        void tresholdImpl(double number, const ParserToken* id);

        //sql
        void sqlImpl(Sql* sql, string spremenljivka);

#pragma endregion 
    };
}