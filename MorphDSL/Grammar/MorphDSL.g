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
  
}

@parser::includes
{
   #include "MorphDSLParser.hpp"
   #include "../ANTLRInterface/CompilerSemanticInterface.h"
   #include <string>
}

@lexer::namespace {	LPM.MorphDSL }

@parser::namespace{	LPM.MorphDSL }
@parser::header { using namespace std; }

//NE DELA
@parser::init{
	currentFigure = NULL;
	interval1 = NULL;
	interval2 = NULL;
	marker1 = NULL;
	marker2 = NULL;
	outputFigureName = "";
}

//dodano v telo razreda v headerju (*.hpp)
@parser::context {

private:
	CompilerSemanticInterface morphInterface;
	const CommonTokenType*    currentFigure;
	const CommonTokenType*    interval1;
	const CommonTokenType*    interval2;
	const CommonTokenType*    marker1;
	const CommonTokenType*    marker2;
	vector<vector<double>> img;
	map<string,vector<double>> vect;
	string outputFigureName;	
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


}

program
	@init { 
		currentFigure = NULL;
		interval1 = NULL;
		interval2 = NULL;
		marker1 = NULL;
		marker2 = NULL;
		outputFigureName = "";	
	}:
 	load assignment+;

load
	: currentFigure=ID '=' 'load' '(' '\"' id2=ID '\"' ')' 
	{
				cout<<"LOADING"<<endl;

				stringstream fLast;//create a stringstream
				fLast << $id1.text;
				cout<<"<--  "<<fLast.str()<<endl;

				int firstLetter = fLast.str().find_last_of("/\\")+1;
				int length = fLast.str().find_last_of(".")-firstLetter;
				outputFigureName = fLast.str().substr(firstLetter,length);
				//cout<<outputFigureName<<endl;

				stringstream fNew;//create a stringstream
				fNew << "./";
				fNew << outputFigureName;
//				fNew << currentFigure->getText()[0]-96;
				fNew << $currentFigure.text;
				fNew << ".bmp";
				cout<<"-->  "<<fNew.str()<<endl;

                cout<<"---END"<<endl;

				morphInterface.LoadImg(fLast.str(), img);
				morphInterface.StoreImg(fNew.str(), img);	 
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
	);

figurevector : ID;

operatorsBB : 
	( 'complement' '(' ID ')' 
	| 'union' '(' ID ',' ID ')' 
	| 'intersection' '(' ID ',' ID ')' 
	| 'without' '(' ID ',' ID ')' 
	| 'hitmiss' '(' ID ',' ID ')' 
	| 'boundary' '(' ID ')' 
	);
	
operatorsGG : 
	( 'negate' '(' ID ')' 
	| 'normalize' 
	| 'multiply' '(' ID ',' DOUBLENUMBER ')' 
	| 'multiply' '(' DOUBLENUMBER ',' ID ')' 
	| 'multiply' '(' ID ',' ID ')' 
	| 'crop' '(' ID ',' interval ')' 
	| 'subtract' '(' ID ',' ID ')' 
	| 'gradient' '(' 'INTERNAL' ',' ID ')' 
	| 'gradient' '(' 'EXTERNAL' ',' ID ')' 
	| 'diferentialProfiles' '(' 'MORPHOLOGICAL' ',' ID ',' ID ')' 
	| 'diferentialProfiles' '(' 'ATTRIBUTE' ',' ID ',' ID ')' 
	| 'mapping' '(' 'DMP' ',' ID ',' ID ',' ID ')' 
	| 'mapping' '(' 'DAP' ',' ID ',' ID ',' ID ')' 
	| 'segmentation' '(' 'MSLS' ',' ID ',' ID ')' 
	| 'segmentation' '(' 'MSLS' ',' ID ',' ID ')' 
	| 'segmentation' '(' 'WATHERSHADE' ',' ID ')' 
	| 'segmentation' '(' 'WATHERSHADE' ',' marker ',' ID ')' );
	
interval : DOUBLENUMBER ',' DOUBLENUMBER ;	

operatorsBBGG : 
	( operatorsBOX 
	| operatorsRECONSTRUCTION 
	| operatorsAREA 
	| operatorsATTRIBUTE 
	);
	
operatorsBOX : 
	( 'erode' '(' 'BOX' '(' DOUBLENUMBER ')' ',' ID ')' 
	| 'dilate' '(' 'BOX' '(' DOUBLENUMBER ')' ',' ID ')' 
	| 'open' '(' 'BOX' '(' DOUBLENUMBER ')' ',' ID ')' 
	| 'close' '(' 'BOX' '(' DOUBLENUMBER ')' ',' ID ')' 
	);	
	
operatorsRECONSTRUCTION : 
	( 'erode' '(' 'RECONSTRUCTION' ',' marker ',' ID ')' 
	| 'dilate' '(' 'RECONSTRUCTION' ',' marker ',' ID ')' 
	| 'open' '(' 'RECONSTRUCTION' ',' 'BOX' '(' DOUBLENUMBER ')' ',' ID ')' 
	| 'close' '(' 'RECONSTRUCTION' ',' 'BOX' '(' DOUBLENUMBER ')' ',' ID ')'
	);	
	
operatorsAREA : 
	( 'open' '(' 'AREA' ',' DOUBLENUMBER ',' ID ')' 
	| 'close' '(' 'AREA' ',' DOUBLENUMBER ',' ID ')' 
	);

operatorsATTRIBUTE : 
	( 'open' '(' ID ',' DOUBLENUMBER ',' ID ')' 
	| 'close' '(' ID ',' DOUBLENUMBER ',' ID ')' 
	);
	
operatorsBG : 'distanceTransform' '(' ID ')' ;

operatorsGB : 'treshold' '(' DOUBLENUMBER ',' ID ')' ;

marker : 
	( ID 
	| DOUBLENUMBER 
	);
	
vector : ( DOUBLENUMBER ( ',' ) )* DOUBLENUMBER ;


//LEXER PRAVILA

ID: ( 'a' .. 'z' | 'A' .. 'Z' | '_' | '\\\\' | '.' | ':' )+ ( '[' NUMBER ']' )?;

DOUBLENUMBER: NUMBER ( '.' NUMBER )?;

fragment NUMBER: ( '0' .. '9' )+;

WS:	( ' ' | '\t' | '\n' | '\r' ) { skip(); };

COMMENT: '/' '/' (~ ( '\r' | '\n' ) )* { skip(); };
