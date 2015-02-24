/** \file
 *  This C++ header file was generated by $ANTLR version 3.4.1-SNAPSHOT
 *
 *     -  From the grammar source file : T.g
 *     -                            On : 2012-09-17 18:17:42
 *     -                for the parser : MorphDSL3ParserParser
 *
 * Editing it, at least manually, is not wise.
 *
 * C++ language generator and runtime by Gokulakannan Somasundaram ( heavy lifting from C Run-time by Jim Idle )
 *
 *
 * The parser 
MorphDSL3Parser

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

#ifndef	_MorphDSL3Parser_H
#define _MorphDSL3Parser_H
/* =============================================================================
 * Standard antlr3 C++ runtime definitions
 */
#include "..\stdafx.h"
#include    <antlr3.hpp>
#include <string>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */


   #include "MorphDSL3Lexer.hpp"
   #include "../ANTLRInterface/CompilerSemanticInterface.h"




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
	namespace 	User  {


typedef MorphDSL3ParserTraits MorphDSL3ParserImplTraits;

struct synpred26_MorphDSL3 {};
struct synpred25_MorphDSL3 {};
struct synpred30_MorphDSL3 {};


class MorphDSL3ParserTokens
{
public:
	/** Symbolic definitions of all the tokens that the 
parser
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
		EOF_TOKEN = MorphDSL3ParserImplTraits::CommonTokenType::TOKEN_EOF
		, T__9 = 9 
		, T__10 = 10 
		, T__11 = 11 
		, T__12 = 12 
		, T__13 = 13 
		, T__14 = 14 
		, T__15 = 15 
		, T__16 = 16
		, T__17 = 17
		, T__18 = 18
		, T__19 = 19
		, T__20 = 20
		, T__21 = 21
		, T__22 = 22
		, T__23 = 23
		, T__24 = 24
		, T__25 = 25
		, T__26 = 26
		, T__27 = 27
		, T__28 = 28
		, T__29 = 29
		, T__30 = 30
		, T__31 = 31
		, T__32 = 32
		, T__33 = 33
		, T__34 = 34
		, T__35 = 35
		, T__36 = 36
		, T__37 = 37
		, T__38 = 38
		, T__39 = 39
		, T__40 = 40
		, T__41 = 41
		, T__42 = 42
		, T__43 = 43
		, T__44 = 44
		, T__45 = 45
		, T__46 = 46
		, ID = 4 
		, DOUBLENUMBER = 5
		, NUMBER = 6
		, WS = 7
		, COMMENT = 8
	};

};

/** Context tracking structure for 
MorphDSL3Parser

 */
class MorphDSL3Parser : public
MorphDSL3ParserImplTraits::BaseParserType
, public MorphDSL3ParserTokens
{
public:
	typedef MorphDSL3ParserImplTraits ImplTraits;
	typedef MorphDSL3Parser ComponentType;
	typedef ComponentType::StreamType StreamType;
	typedef 
MorphDSL3ParserImplTraits::BaseParserType
 BaseType;
	typedef ImplTraits::RecognizerSharedStateType<StreamType> RecognizerSharedStateType;
	typedef StreamType InputType;
	static const bool IsFiltered = false;

	/* ruleAttributeScopeDecl(scope)
	 */
	/* makeScopeSet()
	 */
	 /** Definition of the method scope variable tracking
	 *  structure. An instance of this structure is created by calling
	 *  MorphDSL3Parser_methodPush().
	 */
	struct  methodScope
	{
	    /* =============================================================================
	     * Programmer defined variables...
	     */
	    /** name is visible to any rule called by method directly or indirectly.
	           *  There is also a stack of these names, one slot for each nested
	           *  invocation of method.  If you have a method nested within another
	           *  method then you have name strings on the stack.  Referencing
	           *  $method.name access the topmost always.  I have no way at the moment
	           *  to access earlier elements on the stack.
	           */
	          std::string name;

	    /* End of programmer defined variables
	     * =============================================================================
	     */
	};



private:	
    /* ruleAttributeScopeDef(scope)
     */
    StackType< methodScope >  m_method_stack;

	CompilerSemanticInterface morphInterface;
	const CommonTokenType*    currentFigure;
	const CommonTokenType*    interval1;
	const CommonTokenType*    interval2;
	const CommonTokenType*    marker1;
	const CommonTokenType*    marker2;
	vector<vector<double>> img;
	map<string,vector<double>> vect;
	string outputFigureName;

public:
    MorphDSL3Parser(InputType* instream);
    MorphDSL3Parser(InputType* instream, RecognizerSharedStateType* state);

    void init(InputType* instream  );

     
     void
     program (); 
     
     void
     load ();

     void
     assignment ();

     void
     figurevector ();

     void
     operatorsBB ();

     void
     operatorsGG ();

     void
     interval ();

     void
     operatorsBBGG ();

     void
     operatorsBOX ();

     void
     operatorsRECONSTRUCTION ();

     void
     operatorsAREA ();

     void
     operatorsATTRIBUTE ();

     void
     operatorsBG ();

     void
     operatorsGB ();

     void
     marker ();

     void
     vector ();





     bool
     msynpred( antlr3::ClassForwarder< synpred26_MorphDSL3 >  );
     void
     msynpred25_MorphDSL3_fragment ();

     bool
     msynpred( antlr3::ClassForwarder< synpred25_MorphDSL3 >  );
     void
     msynpred26_MorphDSL3_fragment ();

     bool
     msynpred( antlr3::ClassForwarder< synpred30_MorphDSL3 >  );
     void
     msynpred30_MorphDSL3_fragment ();

     // Delegated rules

	string convertLetterToNumber(char letter);

    const char *    getGrammarFileName();
    void            reset();
    ~MorphDSL3Parser();

};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//

/* End of token definitions for MorphDSL3Parser
 * =============================================================================
 */
/** } */

	}


#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
