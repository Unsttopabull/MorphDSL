#include "stdafx.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

#define NEW

#ifdef NEW
    #include "ANTLRCompilerNew/MorphDSLLexer.hpp"
    #include "ANTLRCompilerNew/MorphDSLParser.hpp"    
#else
    #include "ANTLRCompiler/MorphDSL3Lexer.hpp"
    #include "ANTLRCompiler/MorphDSL3Parser.hpp"
#endif

#include "MorphDSL.h"
#include <antlr3.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;


int test_main(int argc, char* argv[]) {
    ANTLR_UINT8* fName;

    if (argc < 2 || argv[1] == NULL) {
        printf("NO ARGUMENT!\n");
        fName	= (ANTLR_UINT8*)"./DSLPrograms/MorphSQL.dsl"; // Note in VS2005 debug, working directory must be configured
    }
    else {
        printf("USING ARGUMENT!\n");
        printf(argv[1]);
        fName	= (ANTLR_UINT8*)argv[1];
    }

#ifdef NEW
    using namespace LPM_MorphDSL;

    MorphDSLLexer::InputStreamType input(fName, ANTLR_ENC_8BIT);
    MorphDSLLexer lxr(&input);	    // CLexerNew is generated by ANTLR

    //Testiranje lexerja
    //auto t = lxr.nextToken();
    //do{
    //    t = lxr.nextToken();
    //    auto str = t->getText();
    //}
    //while (t->getType() != t->TOKEN_EOF);

    MorphDSLParser::TokenStreamType tstream(ANTLR_SIZE_HINT, lxr.get_tokSource());
    MorphDSLParser psr(&tstream);  // CParserNew is generated by ANTLR3

#else
    using namespace User;

    MorphDSL3Lexer::InputStreamType input(fName, ANTLR_ENC_8BIT);
    MorphDSL3Lexer lxr(&input);	    // CLexerNew is generated by ANTLR
    MorphDSL3Parser::TokenStreamType tstream(ANTLR_SIZE_HINT, lxr.get_tokSource());
    MorphDSL3Parser psr(&tstream);  // CParserNew is generated by ANTLR3
#endif

    printf("INSIDE DSL!\n");
    psr.program();

    cout << "konec" << endl;
    char ch = getch();
    return 0;
}


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[]) {
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(NULL);

    if (hModule != NULL) {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0)) {
            // TODO: change error code to suit your needs
            _tprintf(_T("Fatal Error: MFC initialization failed\n"));
            nRetCode = 1;
        }
        else {
            // TODO: code your application's behavior here.
            test_main(argc, argv);
        }
    }
    else {
        // TODO: change error code to suit your needs
        _tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
        nRetCode = 1;
    }

    return nRetCode;
}
