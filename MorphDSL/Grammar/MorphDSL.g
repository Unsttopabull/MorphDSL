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

//@rulecatch{
//  catch(ANTLR_Exception< MorphDSLLexerImplTraits, RECOGNITION_EXCEPTION, StreamType> rex) {
//    rex.print();
//	set_failedflag(true);
//  }
//}

@parser::namespace{	LPM_MorphDSL }

//header za .hpp in .cpp
@parser::header {using namespace std;}

//include za .hpp
@parser::includes {
#include "MorphDSLLexer.hpp"
#include "Razredi/Enums.h"
#include "Razredi/SqlWhere.h"

namespace LPM_MorphDSL {
	class MorphDSLSemantics;
	class Identifier;
}
}

//Include za .cpp
@parser::postinclude {#include    "stdafx.h"
/* Stdafx.h mora vedno biti na vrhu (prvi definiran) */
#include	"Razredi/SqlWhere.h"
#include "Semantika/MorphDSLSemantics.h"
}

//dodano v telo razreda v headerju (*.hpp)
@parser::context {

private:
	MorphDSLSemantics* s;

    int MorphDSLParser::toInt(const CommonTokenType* token) {
        int number;
        istringstream(token->getText()) >> number;

        return number;
    }

    double MorphDSLParser::toDouble(const CommonTokenType* token) {
        double number;
        istringstream(token->getText()) >> number;

        return number;
    }
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
	@init{ s = new MorphDSLSemantics(this); }
	: load (assignment | COMMENT)+
	;

load
	: imeSpremenljivke=ID '=' 'load' '(' imeSlike=STRING ')' 
	{
		s->setZadnjaSpremenljivka($imeSpremenljivke.text);
		s->loadImpl($imeSlike.text, $imeSpremenljivke.text);
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

figurevector 
	: ID 
	{ 
		s->setZadnjaSpremenljivka($ID.text); 
		s->initNovaSpremenljivka(s->getZadnjaSpremenljivka());
	}
	;

var returns [Identifier* id]
	@init { id = NULL; }
	: ID  { $id = new Identifier($ID); }
	('.' subId { $id->setSubId($subId.id); })?
	;

subId returns [SubId::SubIdentifier id]
	@init{ id = SubId::NONE; }
	: 'mask' { $id = SubId::MASK; }
	| 'set' { $id = SubId::SET; }
	| 'attribute' { $id = SubId::ATTRIBUTE; }
	| 'okroglost' { $id = SubId::OKROGLOST; }
	| 'volument' { $id = SubId::VOLUMENT; }
	;

sql [std::string spremenljivka] returns [Sql* sql]
	@init {
		$sql = new Sql(); 
	} 
	@after {
		s->sqlImpl($sql, spremenljivka); delete $sql;
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
	@init { bool isVar = false; }
	: val1=DOUBLENUMBER op1=relOp 
	  (kv1=sqlWhereKeyword | var1=var { isVar = true; })
	  	{ 
			if(!isVar){
	  			$keyword = $kv1.text;
	  			$stavek = new SqlWhere($op1.relOperator, toDouble($val1), $kv1.text);
			}
			else{
				//TODO SQL WHERE 1
				$stavek = NULL;
			}
	  	}
	| 
	(kv2=sqlWhereKeyword | var2=var { isVar = true; }) op2=relOp val2=DOUBLENUMBER
		{ 
			if(!isVar){
				$keyword = $kv2.text;
				$stavek = new SqlWhere($op2.relOperator, toDouble($val2), $kv2.text);
			}
			else{
				//TODO SQL WHERE 2
				$stavek = NULL;
			}
		}
	|
	kv3=sqlWhereKeyword '=' '(' sql[""] ')'
		{
			$keyword = $kv3.text;
			$stavek = new SqlWhere($sql.sql, $kv3.text);
		}
	;

sqlWhereKeyword
	: 'area'  // < 100 ali > 100
	| 'response' // < 5 ali > 5
	| 'internal_gradient' // > 1
	| 'external_gradient' // > 2
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
	( 'complement' '(' cId=var ')' {	s->complementImpl(*$cId.id); }
	| 'union' '(' uId1=var ',' uId2=var ')' { s->unionImpl(*$uId1.id, *$uId2.id); }
	| 'intersection' '(' iId1=var ',' iId2=var ')' { s->intersectionImpl(*$iId1.id, *$iId2.id); }
	| 'without' '(' wId1=var ',' wId2=var ')' { s->withoutImpl(*$wId1.id, *$wId2.id); }
	| 'hitmiss' '(' hId1=var ',' hId2=var ')' { s->hitMissImpl(*$hId1.id, *$hId2.id); }
	| 'boundary' '(' bId=var ')' { s->boundaryImpl(*$bId.id); }
	);
	
operatorsGG : 
	( 'negate' '(' nId=var ')' { s->negateImpl(*$nId.id); }
	| 'normalize' { s->normalizeImpl(); }
	| 'multiply' '(' mId=var ',' mDbl=DOUBLENUMBER ')' { s->multiplyImpl(*$mId.id, toDouble($mDbl)); }
	| 'multiply' '(' mDbl2=DOUBLENUMBER ',' mId2=var ')'{ s->multiplyImpl(toDouble($mDbl2), *$mId2.id); }
	| 'multiply' '(' mId3=var ',' mId4=var ')' { s->multiplyImpl(*$mId3.id, *$mId4.id); }
	| 'crop' '(' cId=var ',' interval ')' { s->cropImpl(*$cId.id, $interval.start, $interval.stop); }
	| 'subtract' '(' sId1=var ',' sId2=var ')' { s->subtractImpl(*$sId1.id, *$sId2.id); }
	| 'gradient' '(' 'INTERNAL' ',' giId=var ')' { s->gradientInternalImpl(*$giId.id); }
	| 'gradient' '(' 'EXTERNAL' ',' geId=var ')' { s->gradientExternalImpl(*$geId.id); }
	| 'diferentialProfiles' '(' 'MORPHOLOGICAL' ',' dpmId1=var ',' dpmId2=var ')' { s->diferentialProfilesMorphologicalImpl(*$dpmId1.id, *$dpmId2.id); }
	| 'diferentialProfiles' '(' 'ATTRIBUTE' ',' dpaId1=var ',' dpaId2=var ')' { s->diferentialProfilesAttributeImpl(*$dpaId1.id, *$dpaId2.id); }
	| 'mapping' '(' 'DMP' ',' dmpId1=var ',' dmpId2=var /*',' dmpId3=ID */ ')'  { }
	| 'mapping' '(' 'DAP' ',' dapId1=var ',' dapId2=var /*',' dapId3=ID */ ')'  { }
	| 'segmentation' '(' 'MSLS' ',' msls_1_Id1=var ',' msls_1_Id2=var ')' { s->segmentationMsls1Impl(*$msls_1_Id1.id, *$msls_1_Id2.id); }
	| 'segmentation' '(' 'MSLS' ',' msls_2_Id1=var ',' msls_2_Id2=var ')' { s->segmentationMsls2Impl(*$msls_2_Id1.id, *$msls_2_Id2.id); }
	| 'segmentation' '(' 'WATHERSHADE' ',' watershadeId=var ')' { s->segmentationWatershadeImpl(*$watershadeId.id); }
	/*Spremenjeno v kodi, odstranjen marker in dodan še en ID
	| 'segmentation' '(' 'WATHERSHADE' ',' marker ',' watershadeMarkerId=ID ')' )
	*/
	| ('segmentation' '(' 'WATHERSHADE' ',' watershadeMarkerId2=var ',' watershadeMarkerId1=var ')' ) { s->segmentationWatershadeMarkerImpl(*$watershadeMarkerId1.id, *$watershadeMarkerId2.id); })
	;
	
interval returns[double start, double stop]
    : dbl1=DOUBLENUMBER ',' dbl2=DOUBLENUMBER
	{
		istringstream($dbl1.text) >> $start;
		istringstream($dbl2.text) >> $stop;
	}
	;

operatorsBBGG : 
	( operatorsBOX 
	| operatorsRECONSTRUCTION 
	| operatorsAREA 
	| operatorsATTRIBUTE 
	)
	;
	
operatorsBOX : 
	( 'erode' '(' 'BOX' '(' eNum=DOUBLENUMBER ')' ',' eId=var ')'  { s->erodeBoxImpl(toDouble($eNum), *$eId.id); }
	| 'dilate' '(' 'BOX' '(' dNum=DOUBLENUMBER ')' ',' dId=var ')' { s->dilateBoxImpl(toDouble($dNum), *$dId.id); }
	| 'open' '(' 'BOX' '(' oNum=DOUBLENUMBER ')' ',' oId=var ')'   { s->openBoxImpl(toDouble($oNum), *$oId.id); }
	| 'close' '(' 'BOX' '(' cNum=DOUBLENUMBER ')' ',' cId=var ')'  { s->closeBoxImpl(toDouble($cNum), *$cId.id); }
	)
	;	
	
operatorsRECONSTRUCTION : 
    //'erode' '(' 'RECONSTRUCTION' ',' marker ',' ID ')' //sprememba v kodi 'marker' zamenjan z še enim ID-jem
	  'erode' '(' 'RECONSTRUCTION' ',' eId2=var ',' eId1=var ')' { s->erodeImpl(*$eId1.id, *$eId2.id); }
	//'dilate' '(' 'RECONSTRUCTION' ',' marker ',' ID ')' //sprememba v kodi 'marker' zamenjan z še enim ID-jem
	| 'dilate' '(' 'RECONSTRUCTION' ',' dId2=var ',' dId1=var ')' { s->dilateImpl(*$dId1.id, *$dId2.id); }
	| 'open' '(' 'RECONSTRUCTION' ',' 'BOX' '(' oDbl=DOUBLENUMBER ')' ',' oId=var ')'  { s->openImpl(toDouble($oDbl), *$oId.id); }
	| 'close' '(' 'RECONSTRUCTION' ',' 'BOX' '(' cDbl=DOUBLENUMBER ')' ',' cId=var ')' { s->closeImpl(toDouble($cDbl), *$cId.id); }
	;	
	
operatorsAREA : 
	( 'open' '(' 'AREA' ',' oDbl=DOUBLENUMBER ',' oId=var ')'  { s->openArea(toDouble($oDbl), *$oId.id); }
	| 'close' '(' 'AREA' ',' cDbl=DOUBLENUMBER ',' cId=var ')' { s->closeArea(toDouble($cDbl), *$cId.id); }
	)
	;

operatorsATTRIBUTE : 
	( 'open' '(' attr1=ID ',' oDbl=DOUBLENUMBER ',' oId2=var ')'  { s->openAttribute($attr1.text, toDouble($oDbl), *$oId2.id); }
	| 'close' '(' attr2=ID ',' cDbl=DOUBLENUMBER ',' cId2=var ')' { s->closeAttribute($attr2.text, toDouble($cDbl), *$cId2.id); }
	)
	;
	
operatorsBG : 'distanceTransform' '(' var ')' { s->distanceTransformImpl(*$var.id); };

operatorsGB : 'treshold' '(' DOUBLENUMBER ',' var ')' { s->tresholdImpl(toDouble($DOUBLENUMBER), *$var.id); };

marker : 
	( ID 
	| DOUBLENUMBER 
	)
	;
	
vector
	@init{ std::vector<double> tmp; }
	@after {
		std::string fNew = s->getZadnjaSpremenljivka();
		s->insertToVect(std::pair<string, std::vector<double>>(fNew, tmp));
	}
	: 
	(st=DOUBLENUMBER ( ',' ) { tmp.push_back(toDouble($st)); })*  (kncSt=DOUBLENUMBER { tmp.push_back(toDouble($kncSt)); });



//LEXER PRAVILA

STRING
    :  '"' ( ESC_SEQ | ~('.\\'| '\\'|'"') )* '"'
    ;

ID: ('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*;

DOUBLENUMBER: NUMBER ( '.' NUMBER )?;

fragment NUMBER: ( '0' .. '9' )+;

WS:	( ' ' | '\t' | '\n' | '\r' ) {$channel = HIDDEN;};

COMMENT: '//' (~ ( '\r' | '\n' ) )* { $channel = HIDDEN; };

fragment
HEX_DIGIT : ('0'..'9'|'a'..'f'|'A'..'F') ;

fragment
ESC_SEQ
    :   '\\' ('b'|'t'|'n'|'f'|'r'|'\"'|'\''|'\\'|)
    |   UNICODE_ESC
    |   OCTAL_ESC
    ;

fragment
OCTAL_ESC
    :   '\\' ('0'..'3') ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7')
    ;

fragment
UNICODE_ESC
    :   '\\' 'u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
    ;