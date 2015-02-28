#include "stdafx.h"
#include "MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::erodeImpl(std::string id1, std::string id2) {
    cout << "ERODE - RECONSTRUCTION MARKER" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << "./";
    fFirst << outputFigureName;
    fFirst << id1[0] - 96;
    fFirst << ".bmp";
    cout << "<--  " << fFirst.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    cout << "::::::::::::" << endl;
    //					if (marker1!=NULL)
    //					{
    //					   cout<<"???"<<endl;
    stringstream m1;//create a stringstream
    m1 << "./";
    m1 << outputFigureName;
    //m1 << marker1->getText()[0]-96;
    m1 << id2[0] - 96;
    m1 << ".bmp";
    cout << "<--  " << m1.str() << endl;

    morphInterface.erodeRECONSTRUCTION(m1.str(), fFirst.str(), fNew.str());
    /*					}
    else if (marker2 != NULL)
    {
    cout<<"!!!"<<endl;
    stringstream nss;//create a stringstream
    nss << marker2->getText();
    int number;
    istringstream(nss.str()) >> number;
    cout<<"<--  "<<number<<endl;

    morphInterface.erodeRECONSTRUCTION(number, fFirst.str(), fNew.str());
    }
    */
    cout << "---END" << endl;

    marker1 = NULL;
    marker2 = NULL;
}

void MorphDSLParser::dilateImpl(std::string id1, std::string id2) {
    cout << "DILATE - RECONSTRUCTION MARKER" << endl;

    stringstream fFirst;//create a stringstream
    fFirst << "./";
    fFirst << outputFigureName;
    fFirst << id1[0] - 96;
    fFirst << ".bmp";
    cout << "<--  " << fFirst.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    //					if (marker1!=NULL)
    //					{
    stringstream m1;//create a stringstream
    m1 << "./";
    m1 << outputFigureName;
    //m1 << marker1->getText()[0]-96;
    m1 << id2[0] - 96;
    m1 << ".bmp";
    cout << "<--  " << m1.str() << endl;

    morphInterface.dilateRECONSTRUCTION(m1.str(), fFirst.str(), fNew.str());
    //					}
    /*					else if (marker2 != NULL)
    {
    stringstream nss;//create a stringstream
    nss << marker2->getText();
    int number;
    istringstream(nss.str()) >> number;
    cout<<"<--  "<<number<<endl;

    morphInterface.dilateRECONSTRUCTION(number, fFirst.str(), fNew.str());
    }
    */
    cout << "---END" << endl;

    marker1 = NULL;
    marker2 = NULL;
}

void MorphDSLParser::openImpl(double number, std::string id) {
    cout << "OPEN RECONSTRUCTION BOX" << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << outputFigureName;
    fLast << id[0] - 96;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    morphInterface.openRECONSTRUCTION_BOX(number, fLast.str(), fNew.str());
    cout << "---END" << endl;
}

void MorphDSLParser::closeImpl(double number, std::string id) {

    cout << "CLOSE RECONSTRUCTION BOX" << endl;

    stringstream fLast;//create a stringstream
    fLast << "./";
    fLast << outputFigureName;
    fLast << id[0] - 96;
    fLast << ".bmp";
    cout << "<--  " << fLast.str() << endl;

    stringstream fNew;//create a stringstream
    fNew << "./";
    fNew << outputFigureName;
    fNew << currentFigure->getText()[0] - 96;
    fNew << ".bmp";
    cout << "-->  " << fNew.str() << endl;

    morphInterface.closeRECONSTRUCTION_BOX(number, fLast.str(), fNew.str());
    cout << "---END" << endl;
}
