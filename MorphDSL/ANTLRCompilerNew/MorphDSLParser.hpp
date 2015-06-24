/** \file
 *  This C++ header file was generated by $ANTLR version 3.4
 *
 *     -  From the grammar source file : Grammar/MorphDSL.g
 *     -                            On : 2015-06-24 16:10:51
 *     -                for the parser : MorphDSLParserParser
 *
 * Editing it, at least manually, is not wise.
 *
 * C++ language generator and runtime by Gokulakannan Somasundaram ( heavy lifting from C Run-time by Jim Idle )
 *
 *
 * The parser 
MorphDSLParser

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

#ifndef	_MorphDSLParser_H
#define _MorphDSLParser_H
/* =============================================================================
 * Standard antlr3 C++ runtime definitions
 */
#include    <antlr3.hpp>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */


#include "MorphDSLLexer.hpp"
#include "Razredi/Enums.h"
#include "Razredi/SqlWhere.h"

namespace LPM_MorphDSL {
	class MorphDSLSemantics;
}



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

	namespace 	LPM_MorphDSL  {


typedef MorphDSLParserTraits MorphDSLParserImplTraits;

 struct synpred49_MorphDSL {}; 
 struct synpred50_MorphDSL {}; 

struct MorphDSLParser_figurevector_return : public MorphDSLParserImplTraits::RuleReturnValueType
{
public:
	typedef MorphDSLParserImplTraits::RuleReturnValueType BaseType;

    
    MorphDSLParser_figurevector_return()
    {
    }

    MorphDSLParser_figurevector_return( BaseParserType* parser )
        : BaseType(parser)
    {
    }

    MorphDSLParser_figurevector_return( const MorphDSLParser_figurevector_return& n )
    : BaseType(n)
    {
    }

    MorphDSLParser_figurevector_return&
    operator=( const MorphDSLParser_figurevector_return& n )
    {
    	BaseType::operator=( n );
    	return *this;
    }

};





struct MorphDSLParser_operatorSql_return : public MorphDSLParserImplTraits::RuleReturnValueType
{
public:
	typedef MorphDSLParserImplTraits::RuleReturnValueType BaseType;
    SelectKw::Keyword selectKw;
    std::string funkcija;

    
    MorphDSLParser_operatorSql_return()
    {
    }

    MorphDSLParser_operatorSql_return( BaseParserType* parser )
        : BaseType(parser)
    {
    }

    MorphDSLParser_operatorSql_return( const MorphDSLParser_operatorSql_return& n )
    : BaseType(n)
    , selectKw(n.selectKw) ,funkcija(n.funkcija) 
    {
    }

    MorphDSLParser_operatorSql_return&
    operator=( const MorphDSLParser_operatorSql_return& n )
    {
    	BaseType::operator=( n );
    	selectKw = n.selectKw; 
    	funkcija = n.funkcija; 
    	return *this;
    }

};





struct MorphDSLParser_operatorName_return : public MorphDSLParserImplTraits::RuleReturnValueType
{
public:
	typedef MorphDSLParserImplTraits::RuleReturnValueType BaseType;

    
    MorphDSLParser_operatorName_return()
    {
    }

    MorphDSLParser_operatorName_return( BaseParserType* parser )
        : BaseType(parser)
    {
    }

    MorphDSLParser_operatorName_return( const MorphDSLParser_operatorName_return& n )
    : BaseType(n)
    {
    }

    MorphDSLParser_operatorName_return&
    operator=( const MorphDSLParser_operatorName_return& n )
    {
    	BaseType::operator=( n );
    	return *this;
    }

};





struct MorphDSLParser_sqlWhere_return : public MorphDSLParserImplTraits::RuleReturnValueType
{
public:
	typedef MorphDSLParserImplTraits::RuleReturnValueType BaseType;
    std::string keyword;
    SqlWhere* stavek;

    
    MorphDSLParser_sqlWhere_return()
    {
    }

    MorphDSLParser_sqlWhere_return( BaseParserType* parser )
        : BaseType(parser)
    {
    }

    MorphDSLParser_sqlWhere_return( const MorphDSLParser_sqlWhere_return& n )
    : BaseType(n)
    , keyword(n.keyword) ,stavek(n.stavek) 
    {
    }

    MorphDSLParser_sqlWhere_return&
    operator=( const MorphDSLParser_sqlWhere_return& n )
    {
    	BaseType::operator=( n );
    	keyword = n.keyword; 
    	stavek = n.stavek; 
    	return *this;
    }

};





struct MorphDSLParser_sqlWhereKeyword_return : public MorphDSLParserImplTraits::RuleReturnValueType
{
public:
	typedef MorphDSLParserImplTraits::RuleReturnValueType BaseType;

    
    MorphDSLParser_sqlWhereKeyword_return()
    {
    }

    MorphDSLParser_sqlWhereKeyword_return( BaseParserType* parser )
        : BaseType(parser)
    {
    }

    MorphDSLParser_sqlWhereKeyword_return( const MorphDSLParser_sqlWhereKeyword_return& n )
    : BaseType(n)
    {
    }

    MorphDSLParser_sqlWhereKeyword_return&
    operator=( const MorphDSLParser_sqlWhereKeyword_return& n )
    {
    	BaseType::operator=( n );
    	return *this;
    }

};





struct MorphDSLParser_interval_return : public MorphDSLParserImplTraits::RuleReturnValueType
{
public:
	typedef MorphDSLParserImplTraits::RuleReturnValueType BaseType;
    double start;
    double stop;

    
    MorphDSLParser_interval_return()
    {
    }

    MorphDSLParser_interval_return( BaseParserType* parser )
        : BaseType(parser)
    {
    }

    MorphDSLParser_interval_return( const MorphDSLParser_interval_return& n )
    : BaseType(n)
    , start(n.start) ,stop(n.stop) 
    {
    }

    MorphDSLParser_interval_return&
    operator=( const MorphDSLParser_interval_return& n )
    {
    	BaseType::operator=( n );
    	start = n.start; 
    	stop = n.stop; 
    	return *this;
    }

};





struct MorphDSLParser_vector_return : public MorphDSLParserImplTraits::RuleReturnValueType
{
public:
	typedef MorphDSLParserImplTraits::RuleReturnValueType BaseType;

    
    MorphDSLParser_vector_return()
    {
    }

    MorphDSLParser_vector_return( BaseParserType* parser )
        : BaseType(parser)
    {
    }

    MorphDSLParser_vector_return( const MorphDSLParser_vector_return& n )
    : BaseType(n)
    {
    }

    MorphDSLParser_vector_return&
    operator=( const MorphDSLParser_vector_return& n )
    {
    	BaseType::operator=( n );
    	return *this;
    }

};





class MorphDSLParserTokens
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
		EOF_TOKEN = MorphDSLParserImplTraits::CommonTokenType::TOKEN_EOF
		, COMMENT = 4 
		, DOUBLENUMBER = 5 
		, ID = 6 
		, NUMBER = 7 
		, T_AND = 8 
		, T_AREA = 9 
		, T_AREA_SQL = 10 
		, T_ATRIBUTE = 11 
		, T_ATTRIBUTE = 12 
		, T_ATTRIBUTE_SQL = 13 
		, T_BOUNDARY = 14 
		, T_BOX = 15 
		, T_CLOSE = 16 
		, T_COMMA = 17 
		, T_COMPLEMENT = 18 
		, T_CROP = 19 
		, T_DAP = 20 
		, T_DIFERENTIALPROFILES = 21 
		, T_DILATE = 22 
		, T_DISTANCETRANSFORM = 23 
		, T_DMP = 24 
		, T_DOUBLE_QUOTE = 25 
		, T_EQUALS = 26 
		, T_ERODE = 27 
		, T_EXTERNAL = 28 
		, T_EXTERNAL_GRADIENT = 29 
		, T_FROM = 30 
		, T_GRADIENT = 31 
		, T_HITMISS = 32 
		, T_INTERNAL = 33 
		, T_INTERNAL_GRADIENT = 34 
		, T_INTERSECTION = 35 
		, T_LESS_THAN = 36 
		, T_LESS_THAN_OR_EQ = 37 
		, T_LOAD = 38 
		, T_LPAREN = 39 
		, T_MAPPING = 40 
		, T_MASK = 41 
		, T_MORE_THAN = 42 
		, T_MORE_THAN_OR_EQ = 43 
		, T_MORPHOLOGICAL = 44 
		, T_MSLS = 45 
		, T_MULTIPLY = 46 
		, T_NEGATE = 47 
		, T_NORMALIZE = 48 
		, T_NOT_EQUAL = 49 
		, T_OKROGLOST = 50 
		, T_OPEN = 51 
		, T_RECONSTRUCTION = 52 
		, T_RESPONSE = 53 
		, T_RPAREN = 54 
		, T_SEGMENTATION = 55 
		, T_SELECT = 56 
		, T_SET = 57 
		, T_STAR = 58 
		, T_SUBTRACT = 59 
		, T_TRESHOLD = 60 
		, T_UNION = 61 
		, T_VOLUMENT = 62 
		, T_WATHERSHADE = 63 
		, T_WHERE = 64 
		, T_WITHOUT = 65 
		, WS = 66 
	};

};

/** Context tracking structure for 
MorphDSLParser

 */
class MorphDSLParser : public 
MorphDSLParserImplTraits::BaseParserType
, public MorphDSLParserTokens
{
public:
	typedef MorphDSLParserImplTraits ImplTraits;
	typedef MorphDSLParser ComponentType;
	typedef ComponentType::StreamType StreamType;
	typedef 
MorphDSLParserImplTraits::BaseParserType
 BaseType;
	typedef ImplTraits::RecognizerSharedStateType<StreamType> RecognizerSharedStateType;
	typedef StreamType InputType;
	static const bool IsFiltered = false;


private:	
public:
    MorphDSLParser(InputType* instream);
    MorphDSLParser(InputType* instream, RecognizerSharedStateType* state);

    void init(InputType* instream  );

     
     void
     program (); 
     
     void
     load (); 
     
     void
     assignment (); 
     
     MorphDSLParser_figurevector_return
     figurevector (); 
     
     Sql*
     sql (std::string spremenljivka); 
     
     MorphDSLParser_operatorSql_return
     operatorSql (); 
     
     SelectKw::Keyword
     selectKeyword (); 
     
     MorphDSLParser_operatorName_return
     operatorName (); 
     
     MorphDSLParser_sqlWhere_return
     sqlWhere (); 
     
     MorphDSLParser_sqlWhereKeyword_return
     sqlWhereKeyword (); 
     
     RelOp::RelacijskiOperatorji
     relOp (); 
     
     void
     operatorsBB (); 
     
     void
     operatorsGG (); 
     
     MorphDSLParser_interval_return
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
     
     MorphDSLParser_vector_return
     vector (); 


      
     bool
     msynpred( antlr3::ClassForwarder< synpred49_MorphDSL > );
        void msynpred49_MorphDSL_fragment ();
      
     bool
     msynpred( antlr3::ClassForwarder< synpred50_MorphDSL > );
        void msynpred50_MorphDSL_fragment ();
    // Delegated rules

    const char *    getGrammarFileName();
    void            reset();
    ~MorphDSLParser();



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

};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//

/* End of token definitions for MorphDSLParser
 * =============================================================================
 */
/** } */

	}


#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
