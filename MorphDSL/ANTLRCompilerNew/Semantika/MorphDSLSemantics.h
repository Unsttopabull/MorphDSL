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
        ILogger* logger;

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
        string getImageNameFromId(const string& id, SubIdentifier subId = NONE) const;
        string getImageNameFromId(const Identifier& id) const;
        string getLastVariableImageName(bool noExtension = false) const;
        string getLastVariableImageNameWtf() const;
        void variableToFileName(const string& spremenljivka, const string& kategorija);

        bool checkVariablesExist(const string& id1, const string& id2) const;
        bool checkVariableExist(const string& id) const;

        bool checkVariablesExist(const Identifier& id1, const Identifier& id2) const;
        bool checkVariableExist(const Identifier& id1) const;

        Spremenljivka* getVariableFromId(const string& id) const;

        string initInternalVariable(const string& spremenljivka, const string& kategorija);
        void clearTempVariablesCategory(const string& kategorija);

#pragma region NO CHECK

        //operators BB
        void complementNoCheck(const string& idStr) const;
        void unionNoCheck(const string& id1Str, const string& id2Str) const;
        void intersectionNoCheck(const string& id1Str, const string& id2Str) const;
        void withoutNoCheck(const string& id1Str, const string& id2Str) const;
        void hitMissNoCheck(const string& id1Str, const string& id2Str) const;
        void boundaryNoCheck(const string& idStr) const;

        //operatorsGG
        void negateNoCheck(const string& idStr) const;
        void multiplyNoCheck(const double num, const string& idStr) const;
        void multiplyNoCheck(const string& id1Str, const string& id2Str) const;
        void cropNoCheck(const string& id1Str, const double lowBound, double highBound) const;
        void subtractNoCheck(const string& id1Str, const string& id2Str) const;
        void gradientInternalNoCheck(const string& id1Str) const;
        void gradientExternalNoCheck(const string& id1Str) const;
        void diferentialProfilesMorphologicalNoCheck(const string& id1Str, const string& id2Str, const vector<double>& vector) const;
        void differentialProfilesAttributeNoCheck(const string& id1Str, const string& id2Str, const vector<double>& vector) const;
        void mappingDapNoCheck(const string& id2Str, const string& id1Str, const vector<double>& vector) const;
        void segmentationMsls1NoCheck(const string& id2Str, const string& id1Str, const vector<double>& vector) const;
        void segmentationMsls2NoCheck(const string& id1Str, const string& id2Str, const vector<double>& vector) const;
        void segmentatonWatershadeNoCheck(const string& idStr) const;
        void segmentationWatershadeMarkerNoCheck(const string& id1Str, const string& id2Str) const;

        //operatorsBOX
        void erodeBoxNoCheck(const double number, const string& idStr) const;
        void dilateBoxNoCheck(const double number, const string& idStr) const;
        void openBoxNoCheck(const double number, const string& idStr) const;
        void closeBoxNoCheck(const double number, const string& idStr) const;

        //operatorsRECONSTRUCTION
        void erodeNoCheck(const string& id1Str, const string& id2Str) const;
        void dilateNoCheck(const string& id1Str, const string& id2Str) const;
        void openNoCheck(const double number, const string& idStr) const;
        void closeNoCheck(const double number, const string& idStr) const;

        //operatorsAREA
        void openAreaNoCheck(const double number, const string& id) const;
        void closeAreaNoCheck(const double number, const string& id) const;

        //operatorsATTRIBUTE
        void openAttributeNoCheck(const string& attribute, const double number, const string& id2) const;
        void closeAttributeNoCheck(const string& attribute, const double number, const string& id2) const;

        //operatorsBG
        void distanceTransformNoCheck(const string& idStr) const;

        //operatorsGB
        void tresholdImplNoCheck(const double number, const string& id) const;

#pragma endregion 

    public:
        explicit MorphDSLSemantics(MorphDSLParser* p, ILogger* logger);

        void insertToVect(pair<string, vector<double>> pair);

        void setZadnjaSpremenljivka(const string& spr);
        string getZadnjaSpremenljivka() const;

        void loadImpl(string id2, string currentFigure);
        void initNovaSpremenljivka(const string& novaSpr);

#pragma region Implementacije

        //operatorsBB
        void complementImpl(const Identifier& id) const;
        void unionImpl(const Identifier& id1, const Identifier& id2) const;
        void intersectionImpl(const Identifier& id1, const Identifier& id2) const;
        void withoutImpl(const Identifier& id1, const Identifier& id2) const;
        void hitMissImpl(const Identifier& id1, const Identifier& id2) const;
        void boundaryImpl(const Identifier& id) const;

        //operatorsGG
        void negateImpl(const Identifier& id) const;
        void normalizeImpl() const;
        void multiplyImpl(const Identifier& id, double num) const;
        void multiplyImpl(double num, const Identifier& id) const;
        void multiplyImpl(const Identifier& id1, const Identifier& id2) const;
        void cropImpl(const Identifier& id, double lowBound, double highBound) const;
        void subtractImpl(const Identifier& id1, const Identifier& id2) const;
        void gradientInternalImpl(const Identifier& id) const;
        void gradientExternalImpl(const Identifier& id) const;
        void diferentialProfilesMorphologicalImpl(const Identifier& id1, const Identifier& id2) const;
        void diferentialProfilesAttributeImpl(const Identifier& id1, const Identifier& id2) const;
        void mappingDmpNoCheck(const string& id1Str, const string& id2Str, const vector<double>& vector) const;
        void mappingDmpImpl(const Identifier& id1, const Identifier& id2) const;
        void mappingDapImpl(const Identifier& id1, const Identifier& id2) const;
        void segmentationMsls1Impl(const Identifier& id1, const Identifier& id2) const;
        void segmentationMsls2Impl(const Identifier& id1, const Identifier& id2) const;
        void segmentationWatershadeImpl(const Identifier& id1) const;
        void segmentationWatershadeMarkerImpl(const Identifier& id1, const Identifier& id2) const;

        //operatorsBOX
        void erodeBoxImpl(const double number, const Identifier& id) const;
        void dilateBoxImpl(const double number, const Identifier& id) const;
        void openBoxImpl(const double number, const Identifier& id) const;
        void closeBoxImpl(const double number, const Identifier& id) const;

        //operatorsRECONSTRUCTION
        void erodeImpl(const Identifier& id1, const Identifier& id2) const;
        void dilateImpl(const Identifier& id1, const Identifier& id2) const;
        void openImpl(const double number, const Identifier& id) const;
        void closeImpl(const double number, const Identifier& id) const;

        //operatorsAREA
        void openArea(const double number, const Identifier& id) const;
        void closeArea(const double number, const Identifier& id) const;

        //operatorsATTRIBUTE
        void openAttribute(const string& attributeName, const double number, const Identifier& id2) const;
        void closeAttribute(const string& attributeName, const double number, const Identifier& id2) const;

        //operatorsBG
        void distanceTransformImpl(const Identifier& id) const;

        //operatorsGB
        void tresholdImpl(const double number, const Identifier& id) const;

        //sql
        void sqlImpl(Sql* sql, const string& spremenljivka);

#pragma endregion 
    };
}