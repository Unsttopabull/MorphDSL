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
	T_MORE_THAN = '>';
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
}

@parser::namespace{	LPM_MorphDSL }

//header za .hpp in .cpp
@parser::header {using namespace std;}

//include za .hpp
@parser::includes {
#include "MorphDSLLexer.hpp"
#include "Razredi/SqlWhere.h"
#include "../ANTLRInterface/CompilerSemanticInterface.h"
#include <string>
#include <map>
#include <vector>
}
//Include za .cpp
@parser::postinclude {#include    "stdafx.h"
#include	"Razredi/SqlWhere.h"
#include	"Razredi/Sql.h"
}

//dodano v telo razreda v headerju (*.hpp)
@parser::context {

private:
	CompilerSemanticInterface morphInterface;
	//const CommonTokenType*    currentFigure;
	std::vector<std::vector<double>> img;
	map<string, std::vector<double>> vect;
	string imeIzhodneSlike;
	string zadnjaSpremenljivka;
	int imageCounter;

    //Util
    int toInt(const CommonTokenType* token);
    double toDouble(const CommonTokenType* token);
    std::string getNewImageNameFromId(std::string id);
    std::string getNewImageName(bool noExtension = false);
    std::string getNewImageNameWtf();

    void loadImpl(std::string id2, std::string currentFigure);

    //operatorsBB
    void complementImpl(std::string id);
    void unionImpl(std::string id1, std::string id2);
    void intersectionImpl(std::string id1, std::string id2);
    void withoutImpl(std::string id1, std::string id2);
    void hitMissImpl(std::string id1, std::string id2);
    void boundaryImpl(std::string id);

    //operatorsGG
    void negateImpl(std::string id);
    void normalizeImpl();
    void multiplyImpl(std::string id, double num);
    void multiplyImpl(double num, std::string id);
    void multiplyImpl(std::string id1, std::string id2);
    void cropImpl(std::string id, double lowBound, double highBound);
    void subtractImpl(std::string id1, std::string id2);
    void gradientInternalImpl(std::string id);
    void gradientExternalImpl(std::string id);
    void diferentialProfilesMorphologicalImpl(std::string id1, std::string id2);
	void diferentialProfilesAttributeImpl(std::string id1, std::string id2);
    void mappingDmpImpl(std::string id1, std::string id2);
	void mappingDapImpl(std::string id1, std::string id2);
    void segmentationMsls1Impl(std::string id1, std::string id2);
	void segmentationMsls2Impl(std::string id1, std::string id2);
	void segmentationWatershadeImpl(std::string id1);
	void segmentationWatershadeMarkerImpl(std::string id1, std::string id2);

	//operatorsBOX
	void erodeBoxImpl(double number, std::string id);
	void dilateBoxImpl(double number, std::string id);
	void openBoxImpl(double number, std::string id);
	void closeBoxImpl(double number, std::string id);

	//operatorsRECONSTRUCTION
	void erodeImpl(std::string id1, std::string id2);
	void dilateImpl(std::string id1, std::string id2);
	void openImpl(double number, std::string id);
	void closeImpl(double number, std::string id);

    //operatorsAREA
    void openArea(double number, std::string id);
    void closeArea(double number, std::string id);

    //operatorsATTRIBUTE
    void openAttribute(std::string id1, double number, std::string id2);
    void closeAttribute(std::string id1, double number, std::string id2);

	//operatorsBG
	void distanceTransformImpl(std::string id);

    //operatorsGB
    void tresholdImpl(double number, std::string id);

	//sql
	void sqlImpl(Sql* sql);
}

@lexer::namespace {	LPM_MorphDSL }
@lexer::postinclude {#include    "stdafx.h"}

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
		//zadnjaSpremenljivka = NULL;
		/*
		interval2 = NULL;
		marker1 = NULL;
		marker2 = NULL;
		*/
		imeIzhodneSlike = "";
		imageCounter = 0;
	}:
 	load assignment+;

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
	| sql
	);

figurevector : ID { zadnjaSpremenljivka = $ID.text; };

sql returns [Sql* sql]
	@init {
		$sql = new Sql(); 
	}
	@after { sqlImpl($sql); delete $sql;}
	: 'SELECT' operatorSql 'FROM' ID 'WHERE' w1=sqlWhere { sql->dodajOmejitev($w1.keyword, $w1.stavek); }
	  ('AND' w2=sqlWhere 
		{ 
			$sql->dodajOmejitev($w2.keyword, $w2.stavek);
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
	| 'external_greadient' { $kw = SelectKw::ExternalGradient; }
	;

operatorName: 'normalize';

sqlWhere returns [std::string keyword, SqlWhere* stavek]
	: val1=DOUBLENUMBER op1=relOp kv1=sqlWhereKeyword 
	{ 
		$keyword = $kv1.text;
		$stavek = new SqlWhere($op1.relOperator, toDouble($val1), $keyword);
	}
	| kv2=sqlWhereKeyword op2=relOp val2=DOUBLENUMBER
	{ 
		$keyword = $kv2.text;
		$stavek = new SqlWhere($op2.relOperator, toDouble($val2), $keyword);
	}
	| kv3=sqlWhereKeyword '=' '(' sql ')'
	{
		$keyword = $kv3.text;
		$stavek = new SqlWhere($sql.sql, $keyword);
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
	( 'complement' '(' cId=ID ')' {	complementImpl($cId.text); }
	| 'union' '(' uId1=ID ',' uId2=ID ')' { unionImpl($uId1.text, $uId2.text); }
	| 'intersection' '(' iId1=ID ',' iId2=ID ')' { intersectionImpl($iId1.text, $iId2.text); }
	| 'without' '(' wId1=ID ',' wId2=ID ')' { withoutImpl($wId1.text, $wId2.text); }
	| 'hitmiss' '(' hId1=ID ',' hId2=ID ')' { hitMissImpl($hId1.text, $hId2.text); }
	| 'boundary' '(' bId=ID ')' { boundaryImpl($bId.text); }
	);
	
operatorsGG : 
	( 'negate' '(' nId=ID ')' { negateImpl($nId.text); }
	| 'normalize' { normalizeImpl(); }
	| 'multiply' '(' mId=ID ',' mDbl=DOUBLENUMBER ')' { multiplyImpl($mId.text, toDouble($mDbl)); }
	| 'multiply' '(' mDbl2=DOUBLENUMBER ',' mId2=ID ')' { multiplyImpl(toDouble($mDbl2), $mId2.text); }
	| 'multiply' '(' mId3=ID ',' mId4=ID ')'  { multiplyImpl($mId3.text, $mId4.text); }
	| 'crop' '(' cId=ID ',' interval ')'  { cropImpl($cId.text, $interval.start, $interval.stop); }
	| 'subtract' '(' sId1=ID ',' sId2=ID ')'  { subtractImpl($sId1.text, $sId2.text); }
	| 'gradient' '(' 'INTERNAL' ',' giId=ID ')'  { gradientInternalImpl($giId.text); }
	| 'gradient' '(' 'EXTERNAL' ',' geId=ID ')'  { gradientExternalImpl($geId.text); }
	| 'diferentialProfiles' '(' 'MORPHOLOGICAL' ',' dpmId1=ID ',' dpmId2=ID ')'  { diferentialProfilesMorphologicalImpl($dpmId1.text, $dpmId2.text); }
	| 'diferentialProfiles' '(' 'ATTRIBUTE' ',' dpaId1=ID ',' dpaId2=ID ')'  { diferentialProfilesAttributeImpl($dpaId1.text, $dpaId2.text); }
	| 'mapping' '(' 'DMP' ',' dmpId1=ID ',' dmpId2=ID /*',' dmpId3=ID */ ')'  { }
	| 'mapping' '(' 'DAP' ',' dapId1=ID ',' dapId2=ID /*',' dapId3=ID */ ')'  { }
	| 'segmentation' '(' 'MSLS' ',' msls_1_Id1=ID ',' msls_1_Id2=ID ')'  { segmentationMsls1Impl($msls_1_Id1.text, $msls_1_Id2.text); }
	| 'segmentation' '(' 'MSLS' ',' msls_2_Id1=ID ',' msls_2_Id2=ID ')'  { segmentationMsls2Impl($msls_2_Id1.text, $msls_2_Id2.text); }
	| 'segmentation' '(' 'WATHERSHADE' ',' watershadeId=ID ')'  { segmentationWatershadeImpl($watershadeId.text); }
	/* //Spremenjeno v kodi, odstranjen marker in dodan še en ID
	| 'segmentation' '(' 'WATHERSHADE' ',' marker ',' watershadeMarkerId=ID ')' )
	*/
	| ('segmentation' '(' 'WATHERSHADE' ',' watershadeMarkerId2=ID ',' watershadeMarkerId1=ID ')' ) { segmentationWatershadeMarkerImpl($watershadeMarkerId1.text, $watershadeMarkerId2.text); })
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
	( 'erode' '(' 'BOX' '(' eNum=DOUBLENUMBER ')' ',' eId=ID ')'  { erodeBoxImpl(toDouble($eNum), $eId.text); }
	| 'dilate' '(' 'BOX' '(' dNum=DOUBLENUMBER ')' ',' dId=ID ')' { dilateBoxImpl(toDouble($dNum), $dId.text); }
	| 'open' '(' 'BOX' '(' oNum=DOUBLENUMBER ')' ',' oId=ID ')'   { openBoxImpl(toDouble($oNum), $oId.text); }
	| 'close' '(' 'BOX' '(' cNum=DOUBLENUMBER ')' ',' cId=ID ')'  { closeBoxImpl(toDouble($cNum), $cId.text); }
	);	
	
operatorsRECONSTRUCTION : 
    /*'erode' '(' 'RECONSTRUCTION' ',' marker ',' ID ')' //sprememba v kodi 'marker' zamenjan z še enim ID-jem */ 
	  'erode' '(' 'RECONSTRUCTION' ',' eId2=ID ',' eId1=ID ')' { erodeImpl($eId1.text, $eId2.text); }
	/*'dilate' '(' 'RECONSTRUCTION' ',' marker ',' ID ')' //sprememba v kodi 'marker' zamenjan z še enim ID-jem */
	| 'dilate' '(' 'RECONSTRUCTION' ',' dId2=ID ',' dId1=ID ')' { dilateImpl($dId1.text, $dId2.text); }
	| 'open' '(' 'RECONSTRUCTION' ',' 'BOX' '(' oDbl=DOUBLENUMBER ')' ',' oId=ID ')'  { openImpl(toDouble($oDbl), $oId.text); }
	| 'close' '(' 'RECONSTRUCTION' ',' 'BOX' '(' cDbl=DOUBLENUMBER ')' ',' cId=ID ')' { closeImpl(toDouble($cDbl), $cId.text); }
	;	
	
operatorsAREA : 
	( 'open' '(' 'AREA' ',' oDbl=DOUBLENUMBER ',' oId=ID ')' { openArea(toDouble($oDbl), $oId.text); }
	| 'close' '(' 'AREA' ',' cDbl=DOUBLENUMBER ',' cId=ID ')' { closeArea(toDouble($cDbl), $cId.text); }
	);

operatorsATTRIBUTE : 
	( 'open' '(' oId1=ID ',' oDbl=DOUBLENUMBER ',' oId2=ID ')' { openAttribute($oId1.text, toDouble($oDbl), $oId2.text); }
	| 'close' '(' cId1=ID ',' cDbl=DOUBLENUMBER ',' cId2=ID ')' { closeAttribute($cId1.text, toDouble($cDbl), $cId2.text); }
	);
	
operatorsBG : 'distanceTransform' '(' ID ')' { distanceTransformImpl($ID.text); };

operatorsGB : 'treshold' '(' DOUBLENUMBER ',' ID ')' { tresholdImpl(toDouble($DOUBLENUMBER), $ID.text); };

marker : 
	( ID 
	| DOUBLENUMBER 
	);
	
vector 
	@init{ std::vector<double> tmp; }
	@after {
		stringstream fNew;//create a stringstream
	//	cout<< "VECTOR: ";
		
		//fNew << currentFigure->getText()[0]-96;
		fNew << zadnjaSpremenljivka[0] - 96;


	//	cout<< currentFigure->getText();
	//	cout<< " ";
	//	cout<< fNew.str();
	//	cout<< endl;
		std::map<string, std::vector<double>>::iterator it = vect.begin();
		vect.insert (it, std::pair<string, std::vector<double>>(fNew.str(), tmp));
	}
	: 
	(st=DOUBLENUMBER ( ',' ) { tmp.push_back(toDouble($st)); } )*  (kncSt=DOUBLENUMBER { tmp.push_back(toDouble($kncSt)); });



//LEXER PRAVILA

ID: ( 'a' .. 'z' | 'A' .. 'Z' | '_' | '\\' | '.' | ':' )+ ( '[' NUMBER ']' )?;

DOUBLENUMBER: NUMBER ( '.' NUMBER )?;

fragment NUMBER: ( '0' .. '9' )+;

WS:	( ' ' | '\t' | '\n' | '\r' ) { skip(); };

COMMENT: '/' '/' (~ ( '\r' | '\n' ) )* { skip(); };
