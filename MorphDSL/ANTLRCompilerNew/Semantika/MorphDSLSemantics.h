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

    public:
        MorphDSLSemantics(MorphDSLParser* p);

        void setZadnjaSpremenljivka(std::string spr) {
            zadnjaSpremenljivka = spr;
        }

        std::string getZadnjaSpremenljivka() {
            return zadnjaSpremenljivka;
        }

        void insertToVect(std::pair<string, std::vector<double>> pair) {
            vect.insert(vect.begin(), pair);
        }

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

        void initNovaSpremenljivka(string novaSpr);
        string initInternalVariable(string spremenljivka);

        void loadImpl(string id2, string currentFigure);

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
        void subtractImplNoCheck(string id1Str, string id2Str);
        void subtractImpl(const ParserToken* id1, const ParserToken* id2);
        void gradientInternalImpl(const ParserToken* id);
        void gradientExternalImpl(const ParserToken* id);
        void diferentialProfilesMorphologicalImpl(const ParserToken* id1, const ParserToken* id2);
        void diferentialProfilesAttributeImpl(const ParserToken* id1, const ParserToken* id2);
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
        void openAreaNoCheck(double number, string id);
        void openArea(double number, const ParserToken* id);
        void closeAreaNoCheck(double number, string id);
        void closeArea(double number, const ParserToken* id);

        //operatorsATTRIBUTE
        void openAttribute(const ParserToken* id1, double number, const ParserToken* id2);
        void closeAttribute(const ParserToken* id1, double number, const ParserToken* id2);

        //operatorsBG
        void distanceTransformImpl(const ParserToken* id);

        //operatorsGB
        void tresholdImpl(double number, const ParserToken* id);
        void tresholdImplNoCheck(double number, string id);

        //sql
        void sqlImpl(Sql* sql, string spremenljivka);
    };
}