/** \file
 *  This C++ header file was generated by $ANTLR version 3.4
 *
 *     -  From the grammar source file : Java.g
 *     -                            On : 2012-02-26 10:38:15
 *     -                for the parser : JavaParserParser
 *
 * Editing it, at least manually, is not wise.
 *
 * C++ language generator and runtime by Gokulakannan Somasundaram ( heavy lifting from C Run-time by Jim Idle )
 *
 *
 * The parser 
JavaParser

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

#ifndef	_JavaParser_H
#define _JavaParser_H
/* =============================================================================
 * Standard antlr3 C++ runtime definitions
 */
#include    <antlr3.hpp>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */


	#include "JavaLexer.hpp"


// Include delegate definition header files
//
#include	<Java_JavaDecl.hpp>
#include	<Java_JavaAnnotations.hpp>
#include	<Java_JavaExpr.hpp>
#include	<Java_JavaStat.hpp>




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

	namespace  User  {


typedef JavaParserTraits JavaParserImplTraits;

 struct synpred1_Java {}; 

/** Context tracking structure for 
JavaParser

 */
class JavaParser : public 
JavaParserImplTraits::BaseParserType

{
public:
	typedef JavaParserImplTraits ImplTraits;
	typedef JavaParser ComponentType;
	typedef ComponentType::StreamType StreamType;
	typedef 
JavaParserImplTraits::BaseParserType
 BaseType;
	typedef ImplTraits::RecognizerSharedStateType<StreamType> RecognizerSharedStateType;
	typedef StreamType InputType;
	static const bool IsFiltered = false;

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
		EOF_TOKEN = JavaParserImplTraits::CommonTokenType::TOKEN_EOF
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
		, T__47 = 47 
		, T__48 = 48 
		, T__49 = 49 
		, T__50 = 50 
		, T__51 = 51 
		, T__52 = 52 
		, T__53 = 53 
		, T__54 = 54 
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
		, T__68 = 68 
		, T__69 = 69 
		, T__70 = 70 
		, T__71 = 71 
		, T__72 = 72 
		, T__73 = 73 
		, T__74 = 74 
		, T__75 = 75 
		, T__76 = 76 
		, T__77 = 77 
		, T__78 = 78 
		, T__79 = 79 
		, T__80 = 80 
		, T__81 = 81 
		, T__82 = 82 
		, T__83 = 83 
		, T__84 = 84 
		, T__85 = 85 
		, T__86 = 86 
		, T__87 = 87 
		, T__88 = 88 
		, T__89 = 89 
		, T__90 = 90 
		, T__91 = 91 
		, T__92 = 92 
		, T__93 = 93 
		, T__94 = 94 
		, T__95 = 95 
		, T__96 = 96 
		, T__97 = 97 
		, T__98 = 98 
		, T__99 = 99 
		, T__100 = 100 
		, T__101 = 101 
		, T__102 = 102 
		, T__103 = 103 
		, T__104 = 104 
		, T__105 = 105 
		, T__106 = 106 
		, T__107 = 107 
		, T__108 = 108 
		, T__109 = 109 
		, T__110 = 110 
		, T__111 = 111 
		, T__112 = 112 
		, T__113 = 113 
		, COMMENT = 4 
		, CharacterLiteral = 5 
		, DecimalLiteral = 6 
		, ENUM = 7 
		, EscapeSequence = 8 
		, Exponent = 9 
		, FloatTypeSuffix = 10 
		, FloatingPointLiteral = 11 
		, HexDigit = 12 
		, HexLiteral = 13 
		, Identifier = 14 
		, IntegerTypeSuffix = 15 
		, JavaIDDigit = 16 
		, LINE_COMMENT = 17 
		, Letter = 18 
		, OctalEscape = 19 
		, OctalLiteral = 20 
		, StringLiteral = 21 
		, UnicodeEscape = 22 
		, WS = 23 
	};


private:	
	Java_JavaDecl*	 m_gJavaDecl;
	Java_JavaAnnotations*	 m_gJavaAnnotations;
	Java_JavaExpr*	 m_gJavaExpr;
	Java_JavaStat*	 m_gJavaStat;
public:
    JavaParser(InputType* instream);
    JavaParser(InputType* instream, RecognizerSharedStateType* state);

    void init(InputType* instream  );

     
     void
     compilationUnit (); 

      
     bool
     msynpred( antlr3::ClassForwarder< synpred1_Java > );
        void msynpred1_Java_fragment ();
    // Delegated rules
     void
 memberDecl();

     void
 importDeclaration();

     void
 annotationMethodRest();

     void
 typeParameters();

     void
 creator();

     void
 variableModifier();

     void
 interfaceBody();

     void
 normalClassDeclaration();

     void
 enumDeclaration();

     void
 statementExpression();

     void
 modifier();

     void
 elementValuePair();

     void
 switchLabel();

     void
 qualifiedNameList();

     void
 genericMethodOrConstructorRest();

     void
 interfaceMethodOrFieldDecl();

     void
 interfaceMethodOrFieldRest();

     void
 classCreatorRest();

     void
 explicitGenericInvocation();

     void
 voidInterfaceMethodDeclaratorRest();

     void
 primary();

     void
 genericMethodOrConstructorDecl();

     void
 additiveExpression();

     void
 methodDeclaration();

     void
 inclusiveOrExpression();

     void
 classBodyDeclaration();

     void
 forUpdate();

     void
 parExpression();

     void
 arrayInitializer();

     void
 enumConstant();

     void
 classOrInterfaceDeclaration();

     void
 variableDeclarators();

     void
 qualifiedName();

     void
 methodBody();

     void
 variableInitializer();

     void
 block();

     void
 typeList();

     void
 multiplicativeExpression();

     void
 typeDeclaration();

     void
 annotation();

     void
 equalityExpression();

     void
 packageDeclaration();

     void
 castExpression();

     void
 type();

     void
 annotationTypeBody();

     void
 defaultValue();

     void
 unaryExpressionNotPlusMinus();

     void
 annotationMethodOrConstantRest();

     void
 annotationTypeElementDeclarations();

     void
 annotationName();

     void
 switchBlockStatementGroups();

     void
 enumBody();

     void
 blockStatement();

     void
 interfaceMemberDecl();

     void
 forControl();

     void
 innerCreator();

     void
 identifierSuffix();

     void
 relationalExpression();

     void
 typeArgument();

     void
 localVariableDeclaration();

     void
 typeName();

     void
 fieldDeclaration();

     void
 constantDeclaratorsRest();

     void
 annotationConstantRest();

     void
 typeParameter();

     void
 conditionalOrExpression();

     void
 interfaceDeclaration();

     void
 moreStatementExpressions();

     void
 statement();

     void
 shiftOp();

     void
 exclusiveOrExpression();

     void
 conditionalExpression();

     void
 formalParameterDeclsRest();

     void
 annotationTypeElementDeclaration();

     void
 relationalOp();

     void
 catchClause();

     void
 elementValue();

     void
 voidMethodDeclaratorRest();

     void
 arrayCreatorRest();

     void
 arguments();

     void
 forVarControl();

     void
 instanceOfExpression();

     void
 formalParameters();

     void
 forInit();

     void
 shiftExpression();

     void
 variableDeclarator();

     void
 unaryExpression();

     void
 enumConstantName();

     void
 elementValuePairs();

     void
 annotations();

     void
 interfaceGenericMethodDecl();

     void
 catches();

     void
 bound();

     void
 primitiveType();

     void
 constantDeclaratorRest();

     void
 constructorDeclaratorRest();

     void
 normalInterfaceDeclaration();

     void
 expressionList();

     void
 classBody();

     void
 variableDeclaratorRest();

     void
 superSuffix();

     void
 elementValueArrayInitializer();

     void
 constantDeclarator();

     void
 literal();

     void
 interfaceBodyDeclaration();

     void
 enumConstants();

     void
 formalParameter();

     void
 interfaceMethodDeclaratorRest();

     void
 typeArguments();

     void
 createdName();

     void
 conditionalAndExpression();

     void
 nonWildcardTypeArguments();

     void
 booleanLiteral();

     void
 switchBlockStatementGroup();

     void
 annotationTypeElementRest();

     void
 formalParameterDecls();

     void
 constantExpression();

     void
 selector();

     void
 classDeclaration();

     void
 packageOrTypeName();

     void
 enumBodyDeclarations();

     void
 variableDeclaratorId();

     void
 methodDeclaratorRest();

     void
 explicitGenericInvocationSuffix();

     void
 annotationTypeDeclaration();

     void
 expression();

     void
 andExpression();

     void
 assignmentOperator();

     void
 integerLiteral();

    const char *    getGrammarFileName();
    void            reset();
    ~JavaParser();

};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//

/* End of token definitions for JavaParser
 * =============================================================================
 */
/** } */

	}


#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
