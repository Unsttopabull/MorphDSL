grammar MorphDSL;

options {
	language=Cpp;
	backtrack = true;
}

//Da lažje beremo generirano kodo in tokeni niso oznaèeni z številkami npr. T_9 = '\"' ampak T_DOUBLE_QUOTE
tokens {
	T_DOUBLE_QUOTE = '\"';
	T_LPAREN = '(';
	T_RPAREN = ')';
	T_COMMA = ',';
	T_EQUALS = '=';
	T_LESS_THAN = '<';
	T_LESS_THAN_OR_EQ = '<=';
	T_MORE_THAN = '>';
	T_MORE_THAN_OR_EQ = '>=';
	T_NOT_EQUAL = '!=';
	T_AREA = 'AREA';
	T_ATTRIBUTE = 'ATTRIBUTE';
	T_BOX = 'BOX';
	T_DAP = 'DAP';
	T_DMP = 'DMP';
	T_EXTERNAL = 'EXTERNAL';
	T_INTERNAL = 'INTERNAL';
	T_MORPHOLOGICAL = 'MORPHOLOGICAL';
	T_MSLS = 'MSLS';
	T_RECONSTRUCTION = 'RECONSTRUCTION';
	T_WATHERSHADE = 'WATHERSHADE';
	T_BOUNDARY = 'boundary';
	T_CLOSE = 'close';
	T_COMPLEMENT = 'complement';
	T_CROP = 'crop';
	T_DIFERENTIALPROFILES = 'diferentialProfiles';
	T_DILATE = 'dilate';
	T_DISTANCETRANSFORM = 'distanceTransform';
	T_ERODE = 'erode';
	T_GRADIENT = 'gradient';
	T_HITMISS = 'hitmiss';
	T_INTERSECTION = 'intersection';
	T_LOAD = 'load';
	T_MAPPING = 'mapping';
	T_MULTIPLY = 'multiply';
	T_NEGATE = 'negate';
	T_NORMALIZE = 'normalize';
	T_OPEN = 'open';
	T_SEGMENTATION = 'segmentation';
	T_SUBTRACT = 'subtract';
	T_TRESHOLD = 'treshold';
	T_UNION = 'union';
	T_WITHOUT = 'without';
	T_STAR = '*';
	T_SELECT = 'SELECT';
	T_WHERE = 'WHERE';
	T_AND = 'AND';
	T_FROM = 'FROM';
	T_AREA_SQL = 'area';
	T_RESPONSE = 'response';
	T_INTERNAL_GRADIENT = 'internal_gradient';
	T_EXTERNAL_GRADIENT = 'external_gradient';
	T_VOLUMENT = 'volument';
	T_OKROGLOST = 'okroglost';
	T_ATRIBUTE = 'atribute';
	T_ATTRIBUTE_SQL = 'attribute';
	T_MASK = 'mask';
	T_SET = 'set';
}

@rulecatch{
  catch(ANTLR_Exception< MorphDSLLexerImplTraits, RECOGNITION_EXCEPTION, StreamType> rex) {
    rex.print();
	set_failedflag(true);
  }
}

@parser::namespace{	LPM_MorphDSL }

//header za .hpp in .cpp
@parser::header {using namespace std;}

//include za .hpp
@parser::includes {
#include "MorphDSLLexer.hpp"
#include "Razredi/Enums.h"
#include "Razredi/SqlWhere.h"
#include "Util/Spremenljivka.h"
#include "../ANTLRInterface/CompilerSemanticInterface.h"
#include <string>
#include <map>
#include <vector>
}

//Include za .cpp
@parser::postinclude {#include    "stdafx.h"
/* Stdafx.h mora vedno biti na vrhu (prvi definiran) */
#include	"Razredi/SqlWhere.h"
}

//dodano v telo razreda v headerju (*.hpp)
@parser::context {

private:
	CompilerSemanticInterface morphInterface;
	//const CommonTokenType*    currentFigure;
	std::vector<std::vector<double>> img;
	map<string, std::vector<double>> vect;
	map<string, Spremenljivka> imeSlikeZaSpremenljivko;
	string imeIzhodneSlike;
	string zadnjaSpremenljivka;
	int imageCounter;
	int tempCnt;

    //Util
    int toInt(const CommonTokenType* token);
    double toDouble(const CommonTokenType* token);
    std::string getImageNameFromId(std::string id);
    std::string getNewImageName(bool noExtension = false);
    std::string getNewImageNameWtf();

    void spremenljivkaVImeDatoteke(std::string spremenljivka, bool isTemp = false);

    bool checkVariablesExist(std::string id1, std::string id2);
	bool checkVariablesExist(std::string id);

    bool checkVariablesExist(const CommonTokenType* id1, const CommonTokenType* id2);
    bool checkVariablesExist(const CommonTokenType* id1);

	Spremenljivka getSpremenljivkaFromId(std::string id);

	void initNovaSpremenljivka(string novaSpr);
    std::string initInternalSpremenljivka(std::string spremenljivka);

    void loadImpl(std::string id2, std::string currentFigure);

    //operatorsBB
    void complementImpl(const CommonTokenType* id);
    void unionImpl(const CommonTokenType* id1, const CommonTokenType* id2);
    void intersectionImpl(const CommonTokenType* id1, const CommonTokenType* id2);
    void withoutImpl(const CommonTokenType* id1, const CommonTokenType* id2);
    void hitMissImpl(const CommonTokenType* id1, const CommonTokenType* id2);
    void boundaryImpl(const CommonTokenType* id);

    //operatorsGG
    void negateImpl(const CommonTokenType* id);
    void normalizeImpl();
    void multiplyImpl(const CommonTokenType* id, double num);
    void multiplyImpl(double num, const CommonTokenType* id);
    void multiplyImpl(const CommonTokenType* id1, const CommonTokenType* id2);
    void cropImpl(const CommonTokenType* id, double lowBound, double highBound);
	void subtractImplNoCheck(string id1Str, string id2Str);
    void subtractImpl(const CommonTokenType* id1, const CommonTokenType* id2);
    void gradientInternalImpl(const CommonTokenType* id);
    void gradientExternalImpl(const CommonTokenType* id);
    void diferentialProfilesMorphologicalImpl(const CommonTokenType* id1, const CommonTokenType* id2);
	void diferentialProfilesAttributeImpl(const CommonTokenType* id1, const CommonTokenType* id2);
    void mappingDmpImpl(const CommonTokenType* id1, const CommonTokenType* id2);
	void mappingDapImpl(const CommonTokenType* id1, const CommonTokenType* id2);
    void segmentationMsls1Impl(const CommonTokenType* id1, const CommonTokenType* id2);
	void segmentationMsls2Impl(const CommonTokenType* id1, const CommonTokenType* id2);
	void segmentationWatershadeImpl(const CommonTokenType* id1);
	void segmentationWatershadeMarkerImpl(const CommonTokenType* id1, const CommonTokenType* id2);

	//operatorsBOX
	void erodeBoxImpl(double number, const CommonTokenType* id);
	void dilateBoxImpl(double number, const CommonTokenType* id);
	void openBoxImpl(double number, const CommonTokenType* id);
	void closeBoxImpl(double number, const CommonTokenType* id);

	//operatorsRECONSTRUCTION
	void erodeImpl(const CommonTokenType* id1, const CommonTokenType* id2);
	void dilateImpl(const CommonTokenType* id1, const CommonTokenType* id2);
	void openImpl(double number, const CommonTokenType* id);
	void closeImpl(double number, const CommonTokenType* id);

    //operatorsAREA
	void openAreaNoCheck(double number, std::string id);
    void openArea(double number, const CommonTokenType* id);
	void closeAreaNoCheck(double number, std::string id);
    void closeArea(double number, const CommonTokenType* id);

    //operatorsATTRIBUTE
    void openAttribute(const CommonTokenType* id1, double number, const CommonTokenType* id2);
    void closeAttribute(const CommonTokenType* id1, double number, const CommonTokenType* id2);

	//operatorsBG
	void distanceTransformImpl(const CommonTokenType* id);

    //operatorsGB
    void tresholdImpl(double number, const CommonTokenType* id);
    void tresholdImplNoCheck(double number, std::string id);

	//sql
	void sqlImpl(Sql* sql, std::string spremenljivka);
}

@lexer::namespace {	LPM_MorphDSL }
@lexer::postinclude {#include    "stdafx.h"
/* Stdafx.h mora vedno biti na vrhu (prvi definiran) */
}

//sprememba delovanja kot v originalnem grammarju
@lexer::traits 
{
	class MorphDSLLexer; 
	class MorphDSLParser; 

	template<class ImplTraits>
	class UserTraits : public antlr3::CustomTraitsBase<ImplTraits>
	{
	public:

		static const bool TOKENS_ACCESSED_FROM_OWNING_RULE = true;
	};

	typedef antlr3::Traits< MorphDSLLexer, MorphDSLParser, UserTraits > MorphDSLLexerTraits;
	typedef MorphDSLLexerTraits MorphDSLParserTraits;

/*
	   class MorphDSLLexer;
	   class MorphDSLParser;
	   typedef antlr3::Traits< MorphDSLLexer, MorphDSLParser > MorphDSLLexerTraits;
	   typedef MorphDSLLexerTraits MorphDSLParserTraits;
*/
}

program
	@init { 
		imeIzhodneSlike = "";
		imageCounter = 1;
		tempCnt = 0;
	}:
 	load (assignment | COMMENT)+;

load
	: imeSpremenljivke=ID '=' 'load' '(' '\"' imeSlike=ID '\"' ')' 
	{
		this->zadnjaSpremenljivka = $imeSpremenljivke.text;
		loadImpl($imeSlike.text, $imeSpremenljivke.text);
	}
	;

assignment : 
	figurevector '=' 
	( operatorsBB 
	| operatorsGG
	| operatorsBBGG
	| operatorsBG
	| operatorsGB
	| vector
	| sql[$figurevector.text]
	);

figurevector : ID { 
	zadnjaSpremenljivka = $ID.text; 
	initNovaSpremenljivka(zadnjaSpremenljivka);
};

sql[std::string spremenljivka] returns [Sql* sql]
	@init {
		$sql = new Sql(); 
	} 
	@after {
		sqlImpl($sql, spremenljivka); delete $sql;
	}
	: 'SELECT' operatorSql 'FROM' ID 'WHERE' w1=sqlWhere
	{
		 sql->dodajOmejitev($w1.keyword, $w1.stavek); 
	}
	('AND' w2=sqlWhere 
		{ 
			sql->dodajOmejitev($w2.keyword, $w2.stavek);
		} 
	)*
	  {
	    $sql->selectKeyword = $operatorSql.selectKw;
	    $sql->selectFunkcija = $operatorSql.funkcija;
	    $sql->fromId = $ID.text;
	  }
	;

operatorSql returns [SelectKw::Keyword selectKw, std::string funkcija]
	: operatorName '(' sk1=selectKeyword { $selectKw = $sk1.kw; $funkcija = $operatorName.text; } ')'
	| sk2=selectKeyword { $selectKw = $sk2.kw; }
	| '*' { $selectKw = SelectKw::Star; }
	;
	
selectKeyword returns [SelectKw::Keyword kw]
	@init{ $kw = SelectKw::Error; }
	: 'mask' { $kw = SelectKw::Mask; }
	| 'set'  { $kw = SelectKw::Set; }
	| 'attribute' { $kw = SelectKw::Attribute; }
	| 'okroglost' { $kw = SelectKw::Okroglost; }
	| 'volument'  { $kw = SelectKw::Volument; }
	| 'internal_gradient'  { $kw = SelectKw::InternalGradient; }
	| 'external_gradient' { $kw = SelectKw::ExternalGradient; }
	;

operatorName: 'normalize';

sqlWhere returns [std::string keyword, SqlWhere* stavek]
	: val1=DOUBLENUMBER op1=relOp kv1=sqlWhereKeyword
	{ 
		$keyword = $kv1.text;
		$stavek = new SqlWhere($op1.relOperator, toDouble($val1), $kv1.text);
	}
	| kv2=sqlWhereKeyword op2=relOp val2=DOUBLENUMBER
	{ 
		$keyword = $kv2.text;
		$stavek = new SqlWhere($op2.relOperator, toDouble($val2), $kv2.text);
	}
	| kv3=sqlWhereKeyword '=' '(' sql[""] ')'
	{
		$keyword = $kv3.text;
		$stavek = new SqlWhere($sql.sql, $kv3.text);
	}
	;

sqlWhereKeyword
	: 'area'
	| 'response'
	| 'internal_gradient'
	| 'external_gradient'
	| 'volument'
	| 'okroglost'
	| 'atribute'
	;
	
relOp returns [RelOp::RelacijskiOperatorji relOperator]
	@init  { $relOperator = RelOp::ERR;}
	: '>'  { $relOperator = RelOp::GT; }
	| '<'  { $relOperator = RelOp::LT; }
	| '='  { $relOperator = RelOp::EQ; }
	| '!=' { $relOperator = RelOp::NE; }
	| '>=' { $relOperator = RelOp::GE; }
	| '<=' { $relOperator = RelOp::LE; }
	;

operatorsBB : 
	( 'complement' '(' cId=ID ')' {	complementImpl($cId); }
	| 'union' '(' uId1=ID ',' uId2=ID ')' { unionImpl($uId1, $uId2); }
	| 'intersection' '(' iId1=ID ',' iId2=ID ')' { intersectionImpl($iId1, $iId2); }
	| 'without' '(' wId1=ID ',' wId2=ID ')' { withoutImpl($wId1, $wId2); }
	| 'hitmiss' '(' hId1=ID ',' hId2=ID ')' { hitMissImpl($hId1, $hId2); }
	| 'boundary' '(' bId=ID ')' { boundaryImpl($bId); }
	);
	
operatorsGG : 
	( 'negate' '(' nId=ID ')' { negateImpl($nId); }
	| 'normalize' { normalizeImpl(); }
	| 'multiply' '(' mId=ID ',' mDbl=DOUBLENUMBER ')' { multiplyImpl($mId, toDouble($mDbl)); }
	| 'multiply' '(' mDbl2=DOUBLENUMBER ',' mId2=ID ')' { multiplyImpl(toDouble($mDbl2), $mId2); }
	| 'multiply' '(' mId3=ID ',' mId4=ID ')'  { multiplyImpl($mId3, $mId4); }
	| 'crop' '(' cId=ID ',' interval ')'  { cropImpl($cId, $interval.start, $interval.stop); }
	| 'subtract' '(' sId1=ID ',' sId2=ID ')'  { subtractImpl($sId1, $sId2); }
	| 'gradient' '(' 'INTERNAL' ',' giId=ID ')'  { gradientInternalImpl($giId); }
	| 'gradient' '(' 'EXTERNAL' ',' geId=ID ')'  { gradientExternalImpl($geId); }
	| 'diferentialProfiles' '(' 'MORPHOLOGICAL' ',' dpmId1=ID ',' dpmId2=ID ')'  { diferentialProfilesMorphologicalImpl($dpmId1, $dpmId2); }
	| 'diferentialProfiles' '(' 'ATTRIBUTE' ',' dpaId1=ID ',' dpaId2=ID ')'  { diferentialProfilesAttributeImpl($dpaId1, $dpaId2); }
	| 'mapping' '(' 'DMP' ',' dmpId1=ID ',' dmpId2=ID /*',' dmpId3=ID */ ')'  { }
	| 'mapping' '(' 'DAP' ',' dapId1=ID ',' dapId2=ID /*',' dapId3=ID */ ')'  { }
	| 'segmentation' '(' 'MSLS' ',' msls_1_Id1=ID ',' msls_1_Id2=ID ')'  { segmentationMsls1Impl($msls_1_Id1, $msls_1_Id2); }
	| 'segmentation' '(' 'MSLS' ',' msls_2_Id1=ID ',' msls_2_Id2=ID ')'  { segmentationMsls2Impl($msls_2_Id1, $msls_2_Id2); }
	| 'segmentation' '(' 'WATHERSHADE' ',' watershadeId=ID ')'  { segmentationWatershadeImpl($watershadeId); }
	/* //Spremenjeno v kodi, odstranjen marker in dodan še en ID
	| 'segmentation' '(' 'WATHERSHADE' ',' marker ',' watershadeMarkerId=ID ')' )
	*/
	| ('segmentation' '(' 'WATHERSHADE' ',' watershadeMarkerId2=ID ',' watershadeMarkerId1=ID ')' ) { segmentationWatershadeMarkerImpl($watershadeMarkerId1, $watershadeMarkerId2); })
	;
	
interval returns[double start, double stop]: 
	dbl1=DOUBLENUMBER ',' dbl2=DOUBLENUMBER
	{
		istringstream($dbl1.text) >> $start;
		istringstream($dbl2.text) >> $stop;
	};

operatorsBBGG : 
	( operatorsBOX 
	| operatorsRECONSTRUCTION 
	| operatorsAREA 
	| operatorsATTRIBUTE 
	);
	
operatorsBOX : 
	( 'erode' '(' 'BOX' '(' eNum=DOUBLENUMBER ')' ',' eId=ID ')'  { erodeBoxImpl(toDouble($eNum), $eId); }
	| 'dilate' '(' 'BOX' '(' dNum=DOUBLENUMBER ')' ',' dId=ID ')' { dilateBoxImpl(toDouble($dNum), $dId); }
	| 'open' '(' 'BOX' '(' oNum=DOUBLENUMBER ')' ',' oId=ID ')'   { openBoxImpl(toDouble($oNum), $oId); }
	| 'close' '(' 'BOX' '(' cNum=DOUBLENUMBER ')' ',' cId=ID ')'  { closeBoxImpl(toDouble($cNum), $cId); }
	);	
	
operatorsRECONSTRUCTION : 
    /*'erode' '(' 'RECONSTRUCTION' ',' marker ',' ID ')' //sprememba v kodi 'marker' zamenjan z še enim ID-jem */ 
	  'erode' '(' 'RECONSTRUCTION' ',' eId2=ID ',' eId1=ID ')' { erodeImpl($eId1, $eId2); }
	/*'dilate' '(' 'RECONSTRUCTION' ',' marker ',' ID ')' //sprememba v kodi 'marker' zamenjan z še enim ID-jem */
	| 'dilate' '(' 'RECONSTRUCTION' ',' dId2=ID ',' dId1=ID ')' { dilateImpl($dId1, $dId2); }
	| 'open' '(' 'RECONSTRUCTION' ',' 'BOX' '(' oDbl=DOUBLENUMBER ')' ',' oId=ID ')'  { openImpl(toDouble($oDbl), $oId); }
	| 'close' '(' 'RECONSTRUCTION' ',' 'BOX' '(' cDbl=DOUBLENUMBER ')' ',' cId=ID ')' { closeImpl(toDouble($cDbl), $cId); }
	;	
	
operatorsAREA : 
	( 'open' '(' 'AREA' ',' oDbl=DOUBLENUMBER ',' oId=ID ')' { openArea(toDouble($oDbl), $oId); }
	| 'close' '(' 'AREA' ',' cDbl=DOUBLENUMBER ',' cId=ID ')' { closeArea(toDouble($cDbl), $cId); }
	);

operatorsATTRIBUTE : 
	( 'open' '(' oId1=ID ',' oDbl=DOUBLENUMBER ',' oId2=ID ')' { openAttribute($oId1, toDouble($oDbl), $oId2); }
	| 'close' '(' cId1=ID ',' cDbl=DOUBLENUMBER ',' cId2=ID ')' { closeAttribute($cId1, toDouble($cDbl), $cId2); }
	);
	
operatorsBG : 'distanceTransform' '(' ID ')' { distanceTransformImpl($ID); };

operatorsGB : 'treshold' '(' DOUBLENUMBER ',' ID ')' { tresholdImpl(toDouble($DOUBLENUMBER), $ID); };

marker : 
	( ID 
	| DOUBLENUMBER 
	);
	
vector 
	@init{ std::vector<double> tmp; }
	@after {
		std::string fNew = zadnjaSpremenljivka;

		std::map<string, std::vector<double>>::iterator it = vect.begin();
		vect.insert (it, std::pair<string, std::vector<double>>(fNew, tmp));
	}
	: 
	(st=DOUBLENUMBER ( ',' ) { tmp.push_back(toDouble($st)); } )*  (kncSt=DOUBLENUMBER { tmp.push_back(toDouble($kncSt)); });



//LEXER PRAVILA

ID: ( 'a' .. 'z' | 'A' .. 'Z' | '_' | '\\' | '.' | ':' )+ ( '[' NUMBER ']' )?;

DOUBLENUMBER: NUMBER ( '.' NUMBER )?;

fragment NUMBER: ( '0' .. '9' )+;

WS:	( ' ' | '\t' | '\n' | '\r' ) { $channel = HIDDEN; };

COMMENT: '/' '/' (~ ( '\r' | '\n' ) )* { $channel = HIDDEN; };
