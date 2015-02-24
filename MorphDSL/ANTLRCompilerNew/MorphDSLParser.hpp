/** \file
 *  This C++ header file was generated by $ANTLR version 3.5.2
 *
 *     -  From the grammar source file : Grammar/MorphDSL.g
 *     -                            On : 2015-02-24 17:55:58
 *     -                for the parser : MorphDSLParserParser
 *
 * Editing it, at least manually, is not wise.
 *
 * C++ language generator and runtime by Gokulakannan Somasundaram ( heavy lifting from C Run-time by Jim Idle )
 *
 *
 * The parser MorphDSLParser has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 *
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 */
// [The "BSD license"]
// Copyright (c) 2005-2009 Gokulakannan Somasundaram. 
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_MorphDSLParser_H
#define _MorphDSLParser_H
/* =============================================================================
 * Standard antlr3 C++ runtime definitions
 */
#include <antlr3.hpp>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */


   #include "MorphDSLParser.hpp"
   #include "../ANTLRInterface/CompilerSemanticInterface.h"
   #include <string>



 using namespace std; 

#ifdef	WIN32
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif

/* ========================
 * BACKTRACKING IS ENABLED
 * ========================
 */

namespace 	LPM.MorphDSL  {

typedef MorphDSLParserTraits MorphDSLParserImplTraits;

 struct synpred25_MorphDSL {}; 
 struct synpred26_MorphDSL {}; 

class MorphDSLParserTokens
{
public:
	/** Symbolic definitions of all the tokens that the parser will work with.
	 *
	 * Antlr will define EOF, but we can't use that as it it is too common in
	 * in C header files and that would be confusing. There is no way to filter this out at the moment
	 * so we just undef it here for now. That isn't the value we get back from C recognizers
	 * anyway. We are looking for ANTLR_TOKEN_EOF.
	 */
	enum Tokens 
	{
		EOF_TOKEN = MorphDSLParserImplTraits::CommonTokenType::TOKEN_EOF
		, COMMENT = 4 
		, DOUBLENUMBER = 5 
		, ID = 6 
		, NUMBER = 7 
		, T_AREA = 8 
		, T_ATTRIBUTE = 9 
		, T_BOUNDARY = 10 
		, T_BOX = 11 
		, T_CLOSE = 12 
		, T_COMMA = 13 
		, T_COMPLEMENT = 14 
		, T_CROP = 15 
		, T_DAP = 16 
		, T_DIFERENTIALPROFILES = 17 
		, T_DILATE = 18 
		, T_DISTANCETRANSFORM = 19 
		, T_DMP = 20 
		, T_DOUBLE_QUOTE = 21 
		, T_EQUALS = 22 
		, T_ERODE = 23 
		, T_EXTERNAL = 24 
		, T_GRADIENT = 25 
		, T_HITMISS = 26 
		, T_INTERNAL = 27 
		, T_INTERSECTION = 28 
		, T_LOAD = 29 
		, T_LPAREN = 30 
		, T_MAPPING = 31 
		, T_MORPHOLOGICAL = 32 
		, T_MSLS = 33 
		, T_MULTIPLY = 34 
		, T_NEGATE = 35 
		, T_NORMALIZE = 36 
		, T_OPEN = 37 
		, T_RECONSTRUCTION = 38 
		, T_RPAREN = 39 
		, T_SEGMENTATION = 40 
		, T_SUBTRACT = 41 
		, T_TRESHOLD = 42 
		, T_UNION = 43 
		, T_WATHERSHADE = 44 
		, T_WITHOUT = 45 
		, WS = 46 
	};

};

/** Context tracking structure for MorphDSLParser
 */
class MorphDSLParser : public MorphDSLParserImplTraits::BaseParserType, public MorphDSLParserTokens
{
public:
	typedef MorphDSLParserImplTraits ImplTraits;
	typedef MorphDSLParser ComponentType;
	typedef ComponentType::StreamType StreamType;
	typedef MorphDSLParserImplTraits::BaseParserType BaseType;
	typedef ImplTraits::RecognizerSharedStateType<StreamType> RecognizerSharedStateType;
	typedef StreamType InputType;
	static const bool IsFiltered = false;


private:	
public:
    MorphDSLParser(InputType* instream);
    MorphDSLParser(InputType* instream, RecognizerSharedStateType* state);

    void init(InputType* instream  );



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


     void program (); 
     void load (); 
     void assignment (); 
     void figurevector (); 
     void operatorsBB (); 
     void operatorsGG (); 
     void interval (); 
     void operatorsBBGG (); 
     void operatorsBOX (); 
     void operatorsRECONSTRUCTION (); 
     void operatorsAREA (); 
     void operatorsATTRIBUTE (); 
     void operatorsBG (); 
     void operatorsGB (); 
     void marker (); 
     void vector (); 


      bool msynpred( antlr3::ClassForwarder< synpred25_MorphDSL > );
        void msynpred25_MorphDSL_fragment ();
      bool msynpred( antlr3::ClassForwarder< synpred26_MorphDSL > );
        void msynpred26_MorphDSL_fragment ();
    // Delegated rules

    const char *    getGrammarFileName();
    void            reset();
    ~MorphDSLParser();

};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//

/* End of token definitions for MorphDSLParser
 * =============================================================================
 */

}

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
