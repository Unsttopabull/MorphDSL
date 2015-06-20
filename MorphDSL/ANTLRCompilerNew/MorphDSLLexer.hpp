/** \file
 *  This C++ header file was generated by $ANTLR version 3.4
 *
 *     -  From the grammar source file : Grammar/MorphDSL.g
 *     -                            On : 2015-06-20 15:17:01
 *     -                 for the lexer : MorphDSLLexerLexer
 *
 * Editing it, at least manually, is not wise.
 *
 * C++ language generator and runtime by Gokulakannan Somasundaram ( heavy lifting from C Run-time by Jim Idle )
 *
 *
 * The lexer 
MorphDSLLexer

has the callable functions (rules) shown below,
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

#ifndef	_MorphDSLLexer_H
#define _MorphDSLLexer_H
/* =============================================================================
 * Standard antlr3 C++ runtime definitions
 */
#include    <antlr3.hpp>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */




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
	namespace 	LPM_MorphDSL  {



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

typedef MorphDSLLexerTraits MorphDSLLexerImplTraits;


class MorphDSLLexerTokens
{
public:
	/** Symbolic definitions of all the tokens that the 
lexer
 will work with.
	 * \{
	 *
	 * Antlr will define EOF, but we can't use that as it it is too common in
	 * in C header files and that would be confusing. There is no way to filter this out at the moment
	 * so we just undef it here for now. That isn't the value we get back from C recognizers
	 * anyway. We are looking for ANTLR_TOKEN_EOF.
	 */
	enum Tokens 
	{
		EOF_TOKEN = MorphDSLLexerImplTraits::CommonTokenType::TOKEN_EOF
		, T__55 = 55 
		, T__56 = 56 
		, T__57 = 57 
		, T__58 = 58 
		, T__59 = 59 
		, T__60 = 60 
		, T__61 = 61 
		, T__62 = 62 
		, T__63 = 63 
		, T__64 = 64 
		, T__65 = 65 
		, T__66 = 66 
		, T__67 = 67 
		, COMMENT = 4 
		, DOUBLENUMBER = 5 
		, ID = 6 
		, NUMBER = 7 
		, T_AND = 8 
		, T_AREA = 9 
		, T_ATTRIBUTE = 10 
		, T_BOUNDARY = 11 
		, T_BOX = 12 
		, T_CLOSE = 13 
		, T_COMMA = 14 
		, T_COMPLEMENT = 15 
		, T_CROP = 16 
		, T_DAP = 17 
		, T_DIFERENTIALPROFILES = 18 
		, T_DILATE = 19 
		, T_DISTANCETRANSFORM = 20 
		, T_DMP = 21 
		, T_DOUBLE_QUOTE = 22 
		, T_EQUALS = 23 
		, T_ERODE = 24 
		, T_EXTERNAL = 25 
		, T_FROM = 26 
		, T_GRADIENT = 27 
		, T_HITMISS = 28 
		, T_INTERNAL = 29 
		, T_INTERSECTION = 30 
		, T_LESS_THAN = 31 
		, T_LOAD = 32 
		, T_LPAREN = 33 
		, T_MAPPING = 34 
		, T_MORE_THAN = 35 
		, T_MORPHOLOGICAL = 36 
		, T_MSLS = 37 
		, T_MULTIPLY = 38 
		, T_NEGATE = 39 
		, T_NORMALIZE = 40 
		, T_NOT_EQUAL = 41 
		, T_OPEN = 42 
		, T_RECONSTRUCTION = 43 
		, T_RPAREN = 44 
		, T_SEGMENTATION = 45 
		, T_SELECT = 46 
		, T_STAR = 47 
		, T_SUBTRACT = 48 
		, T_TRESHOLD = 49 
		, T_UNION = 50 
		, T_WATHERSHADE = 51 
		, T_WHERE = 52 
		, T_WITHOUT = 53 
		, WS = 54 
	};

};

/** Context tracking structure for 
MorphDSLLexer

 */
class MorphDSLLexer : public 
MorphDSLLexerImplTraits::BaseLexerType
, public MorphDSLLexerTokens
{
public:
	typedef MorphDSLLexerImplTraits ImplTraits;
	typedef MorphDSLLexer ComponentType;
	typedef ComponentType::StreamType StreamType;
	typedef 
MorphDSLLexerImplTraits::BaseLexerType
 BaseType;
	typedef ImplTraits::RecognizerSharedStateType<StreamType> RecognizerSharedStateType;
	typedef StreamType InputType;
	static const bool IsFiltered = false;


private:	
public:
    MorphDSLLexer(InputType* instream);
    MorphDSLLexer(InputType* instream, RecognizerSharedStateType* state);

    void init(InputType* instream  );

    
     void
      mT_AND( );

     void
      mT_AREA( );

     void
      mT_ATTRIBUTE( );

     void
      mT_BOUNDARY( );

     void
      mT_BOX( );

     void
      mT_CLOSE( );

     void
      mT_COMMA( );

     void
      mT_COMPLEMENT( );

     void
      mT_CROP( );

     void
      mT_DAP( );

     void
      mT_DIFERENTIALPROFILES( );

     void
      mT_DILATE( );

     void
      mT_DISTANCETRANSFORM( );

     void
      mT_DMP( );

     void
      mT_DOUBLE_QUOTE( );

     void
      mT_EQUALS( );

     void
      mT_ERODE( );

     void
      mT_EXTERNAL( );

     void
      mT_FROM( );

     void
      mT_GRADIENT( );

     void
      mT_HITMISS( );

     void
      mT_INTERNAL( );

     void
      mT_INTERSECTION( );

     void
      mT_LESS_THAN( );

     void
      mT_LOAD( );

     void
      mT_LPAREN( );

     void
      mT_MAPPING( );

     void
      mT_MORE_THAN( );

     void
      mT_MORPHOLOGICAL( );

     void
      mT_MSLS( );

     void
      mT_MULTIPLY( );

     void
      mT_NEGATE( );

     void
      mT_NORMALIZE( );

     void
      mT_NOT_EQUAL( );

     void
      mT_OPEN( );

     void
      mT_RECONSTRUCTION( );

     void
      mT_RPAREN( );

     void
      mT_SEGMENTATION( );

     void
      mT_SELECT( );

     void
      mT_STAR( );

     void
      mT_SUBTRACT( );

     void
      mT_TRESHOLD( );

     void
      mT_UNION( );

     void
      mT_WATHERSHADE( );

     void
      mT_WHERE( );

     void
      mT_WITHOUT( );

     void
      mT__55( );

     void
      mT__56( );

     void
      mT__57( );

     void
      mT__58( );

     void
      mT__59( );

     void
      mT__60( );

     void
      mT__61( );

     void
      mT__62( );

     void
      mT__63( );

     void
      mT__64( );

     void
      mT__65( );

     void
      mT__66( );

     void
      mT__67( );

     void
      mID( );

     void
      mDOUBLENUMBER( );

     void
      mNUMBER( );

     void
      mWS( );

     void
      mCOMMENT( );

     void
      mTokens( );
    const char *    getGrammarFileName();
    void            reset();
    ~MorphDSLLexer();

};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//

/* End of token definitions for MorphDSLLexer
 * =============================================================================
 */
/** } */

	}


#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
