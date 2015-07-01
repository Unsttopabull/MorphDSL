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
        void complementNoCheck(const string& idStr);
        void unionNoCheck(const string& id1Str, const string& id2Str);
        void intersectionNoCheck(const string& id1Str, const string& id2Str);
        void withoutNoCheck(const string& id1Str, const string& id2Str);
        void hitMissNoCheck(const string& id1Str, const string& id2Str);
        void boundaryNoCheck(const string& idStr);

        //operatorsGG
        void negateNoCheck(const string& idStr);
        void multiplyNoCheck(const double num, const string& idStr);
        void multiplyNoCheck(const string& id1Str, const string& id2Str);
        void cropNoCheck(const string& id1Str, const double lowBound, double highBound);
        void subtractNoCheck(const string& id1Str, const string& id2Str);
        void gradientInternalNoCheck(const string& id1Str);
        void gradientExternalNoCheck(const string& id1Str);
        void diferentialProfilesMorphologicalNoCheck(const string& id1Str, const string& id2Str, const vector<double>& vector);
        void differentialProfilesAttributeNoCheck(const string& id1Str, const string& id2Str, const vector<double>& vector);
        void mappingDapNoCheck(const string& id2Str, const string& id1Str, const vector<double>& vector);
        void segmentationMsls1NoCheck(const string& id2Str, const string& id1Str, const vector<double>& vector);
        void segmentationMsls2NoCheck(const string& id1Str, const string& id2Str, const vector<double>& vector);
        void segmentatonWatershadeNoCheck(const string& idStr);
        void segmentationWatershadeMarkerNoCheck(const string& id1Str, const string& id2Str);

        //operatorsBOX
        void erodeBoxNoCheck(const double number, const string& idStr);
        void dilateBoxNoCheck(const double number, const string& idStr);
        void openBoxNoCheck(const double number, const string& idStr);
        void closeBoxNoCheck(const double number, const string& idStr);

        //operatorsRECONSTRUCTION
        void erodeNoCheck(const string& id1Str, const string& id2Str);
        void dilateNoCheck(const string& id1Str, const string& id2Str);
        void openNoCheck(const double number, const string& idStr);
        void closeNoCheck(const double number, const string& idStr);

        //operatorsAREA
        void openAreaNoCheck(const double number, const string& id);
        void closeAreaNoCheck(const double number, const string& id);

        //operatorsATTRIBUTE
        void openAttributeNoCheck(const string& attribute, const double number, const string& id2);
        void closeAttributeNoCheck(const string& attribute, const double number, const string& id2);

        //operatorsBG
        void distanceTransformNoCheck(const string& idStr);

        //operatorsGB
        void tresholdImplNoCheck(const double number, const string& id);

#pragma endregion 

    public:
        explicit MorphDSLSemantics(MorphDSLParser* p);

        void setZadnjaSpremenljivka(const string& spr) {
            predZadnjaSpremenljivka = zadnjaSpremenljivka;
            zadnjaSpremenljivka = spr;
        }

        string getZadnjaSpremenljivka() const {
            return zadnjaSpremenljivka;
        }

        void insertToVect(pair<string, vector<double>> pair) {
            vect.insert(vect.begin(), pair);
        }

        void loadImpl(string id2, string currentFigure);
        void initNovaSpremenljivka(const string& novaSpr);

#pragma region Implementacije

        //operatorsBB
        void complementImpl(const Identifier& id);
        void unionImpl(const Identifier& id1, const Identifier& id2);
        void intersectionImpl(const Identifier& id1, const Identifier& id2);
        void withoutImpl(const Identifier& id1, const Identifier& id2);
        void hitMissImpl(const Identifier& id1, const Identifier& id2);
        void boundaryImpl(const Identifier& id);

        //operatorsGG
        void negateImpl(const Identifier& id);
        void normalizeImpl();
        void multiplyImpl(const Identifier& id, double num);
        void multiplyImpl(double num, const Identifier& id);
        void multiplyImpl(const Identifier& id1, const Identifier& id2);
        void cropImpl(const Identifier& id, double lowBound, double highBound);
        void subtractImpl(const Identifier& id1, const Identifier& id2);
        void gradientInternalImpl(const Identifier& id);
        void gradientExternalImpl(const Identifier& id);
        void diferentialProfilesMorphologicalImpl(const Identifier& id1, const Identifier& id2);
        void diferentialProfilesAttributeImpl(const Identifier& id1, const Identifier& id2);
        void mappingDmpNoCheck(const string& id1Str, const string& id2Str, const vector<double>& vector);
        void mappingDmpImpl(const Identifier& id1, const Identifier& id2);
        void mappingDapImpl(const Identifier& id1, const Identifier& id2);
        void segmentationMsls1Impl(const Identifier& id1, const Identifier& id2);
        void segmentationMsls2Impl(const Identifier& id1, const Identifier& id2);
        void segmentationWatershadeImpl(const Identifier& id1);
        void segmentationWatershadeMarkerImpl(const Identifier& id1, const Identifier& id2);

        //operatorsBOX
        void erodeBoxImpl(const double number, const Identifier& id);
        void dilateBoxImpl(const double number, const Identifier& id);
        void openBoxImpl(const double number, const Identifier& id);
        void closeBoxImpl(const double number, const Identifier& id);

        //operatorsRECONSTRUCTION
        void erodeImpl(const Identifier& id1, const Identifier& id2);
        void dilateImpl(const Identifier& id1, const Identifier& id2);
        void openImpl(const double number, const Identifier& id);
        void closeImpl(const double number, const Identifier& id);

        //operatorsAREA
        void openArea(const double number, const Identifier& id);
        void closeArea(const double number, const Identifier& id);

        //operatorsATTRIBUTE
        void openAttribute(const string& attributeName, const double number, const Identifier& id2);
        void closeAttribute(const string& attributeName, const double number, const Identifier& id2);

        //operatorsBG
        void distanceTransformImpl(const Identifier& id);

        //operatorsGB
        void tresholdImpl(const double number, const Identifier& id);

        //sql
        void sqlImpl(Sql* sql, const string& spremenljivka);

#pragma endregion 
    };
}