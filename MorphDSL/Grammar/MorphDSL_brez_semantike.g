grammar MorphDSL_brez_semantike;

options {
	/*language=Cpp;*/
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
	T_STAR = '*';
}

program:
 	load assignment+;

load
	: currentFigure=ID '=' 'load' '(' '\"' id2=ID '\"' ')' 
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

figurevector : ID;

sql: 'SELECT' (operatorSql | '*' ) 'FROM' ID 'WHERE' sqlWhere ('AND' sqlWhere)*;

operatorSql
	: operatorName '(' selectKeyword ')'
	| selectKeyword
	;
	
selectKeyword
	: 'mask'
	| 'set'
	| 'attribute'
	| 'okroglost'
	| 'volument'
	| 'internal_gradient'
	| 'external_greadient'
	;

operatorName: 'normalize';

sqlWhere
	: DOUBLENUMBER relOp sqlWhereKeyword
	| sqlWhereKeyword relOp DOUBLENUMBER
	;
	
relOp
	: '>' 
	| '<' 
	| '=' 
	| '!='
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

operatorsBB : 
	( 'complement' '(' cId=ID ')' 
	| 'union' '(' uId1=ID ',' uId2=ID ')'
	| 'intersection' '(' iId1=ID ',' iId2=ID ')'
	| 'without' '(' wId1=ID ',' wId2=ID ')'
	| 'hitmiss' '(' hId1=ID ',' hId2=ID ')'
	| 'boundary' '(' bId=ID ')'
	);
	
operatorsGG : 
	( 'negate' '(' nId=ID ')'
	| 'normalize' 
	| 'multiply' '(' mId=ID ',' mDbl=DOUBLENUMBER ')'
	| 'multiply' '(' mDbl2=DOUBLENUMBER ',' mId2=ID ')'
	| 'multiply' '(' mId3=ID ',' mId4=ID ')' 
	| 'crop' '(' cId=ID ',' interval ')'
	| 'subtract' '(' sId1=ID ',' sId2=ID ')'
	| 'gradient' '(' 'INTERNAL' ',' giId=ID ')'
	| 'gradient' '(' 'EXTERNAL' ',' geId=ID ')'
	| 'diferentialProfiles' '(' 'MORPHOLOGICAL' ',' dpmId1=ID ',' dpmId2=ID ')'
	| 'diferentialProfiles' '(' 'ATTRIBUTE' ',' dpaId1=ID ',' dpaId2=ID ')'
	| 'mapping' '(' 'DMP' ',' dmpId1=ID ',' dmpId2=ID /*',' dmpId3=ID */ ')'
	| 'mapping' '(' 'DAP' ',' dapId1=ID ',' dapId2=ID /*',' dapId3=ID */ ')' 
	| 'segmentation' '(' 'MSLS' ',' msls_1_Id1=ID ',' msls_1_Id2=ID ')'
	| 'segmentation' '(' 'MSLS' ',' msls_2_Id1=ID ',' msls_2_Id2=ID ')'
	| 'segmentation' '(' 'WATHERSHADE' ',' watershadeId=ID ')'
	/* //Spremenjeno v kodi, odstranjen marker in dodan še en ID
	| 'segmentation' '(' 'WATHERSHADE' ',' marker ',' watershadeMarkerId=ID ')' )
	*/
	| ('segmentation' '(' 'WATHERSHADE' ',' watershadeMarkerId2=ID ',' watershadeMarkerId1=ID ')' ) 
	)
	;
	
interval:	
	dbl1=DOUBLENUMBER ',' dbl2=DOUBLENUMBER;

operatorsBBGG : 
	( operatorsBOX 
	| operatorsRECONSTRUCTION 
	| operatorsAREA 
	| operatorsATTRIBUTE 
	);
	
operatorsBOX : 
	( 'erode' '(' 'BOX' '(' eNum=DOUBLENUMBER ')' ',' eId=ID ')'
	| 'dilate' '(' 'BOX' '(' dNum=DOUBLENUMBER ')' ',' dId=ID ')'
	| 'open' '(' 'BOX' '(' oNum=DOUBLENUMBER ')' ',' oId=ID ')'
	| 'close' '(' 'BOX' '(' cNum=DOUBLENUMBER ')' ',' cId=ID ')'
	);	
	
operatorsRECONSTRUCTION : 
    /*'erode' '(' 'RECONSTRUCTION' ',' marker ',' ID ')' //sprememba v kodi 'marker' zamenjan z še enim ID-jem */ 
	  'erode' '(' 'RECONSTRUCTION' ',' eId2=ID ',' eId1=ID ')'
	/*'dilate' '(' 'RECONSTRUCTION' ',' marker ',' ID ')' //sprememba v kodi 'marker' zamenjan z še enim ID-jem */
	| 'dilate' '(' 'RECONSTRUCTION' ',' dId2=ID ',' dId1=ID ')'
	| 'open' '(' 'RECONSTRUCTION' ',' 'BOX' '(' oDbl=DOUBLENUMBER ')' ',' oId=ID ')' 
	| 'close' '(' 'RECONSTRUCTION' ',' 'BOX' '(' cDbl=DOUBLENUMBER ')' ',' cId=ID ')'
	;	
	
operatorsAREA : 
	( 'open' '(' 'AREA' ',' oDbl=DOUBLENUMBER ',' oId=ID ')'
	| 'close' '(' 'AREA' ',' cDbl=DOUBLENUMBER ',' cId=ID ')'
	);

operatorsATTRIBUTE : 
	( 'open' '(' oId1=ID ',' oDbl=DOUBLENUMBER ',' oId2=ID ')'
	| 'close' '(' cId1=ID ',' cDbl=DOUBLENUMBER ',' cId2=ID ')'
	);
	
operatorsBG : 'distanceTransform' '(' ID ')';

operatorsGB : 'treshold' '(' DOUBLENUMBER ',' ID ')';

marker : 
	( ID 
	| DOUBLENUMBER 
	);
	
vector : 
	(st=DOUBLENUMBER ( ',' ))*  (kncSt=DOUBLENUMBER);



//LEXER PRAVILA

ID: ( 'a' .. 'z' | 'A' .. 'Z' | '_' | '\\' | '.' | ':' )+ ( '[' NUMBER ']' )?;

DOUBLENUMBER: NUMBER ( '.' NUMBER )?;

fragment NUMBER: ( '0' .. '9' )+;

WS:	( ' ' | '\t' | '\n' | '\r' ) { $channel=HIDDEN; };

COMMENT: '/' '/' (~ ( '\r' | '\n' ) )* { skip(); };
