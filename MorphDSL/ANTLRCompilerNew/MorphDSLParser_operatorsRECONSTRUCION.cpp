#include "stdafx.h"
#include "MorphDSLParser.hpp"

using namespace LPM_MorphDSL;
using namespace std;

void MorphDSLParser::erodeImpl(std::string id1, std::string id2) {
    cout << "ERODE - RECONSTRUCTION MARKER" << endl;

    string fFirst = getNewImageNameFromId(id1);
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    cout << "::::::::::::" << endl;
    //					if (marker1!=NULL)
    //					{
    //					   cout<<"???"<<endl;
    stringstream m1;//create a stringstream
    m1 << "./";
    m1 << imeIzhodneSlike;
    //m1 << marker1->getText()[0]-96;
    m1 << id2[0] - 96;
    m1 << ".bmp";
    cout << "<--  " << m1.str() << endl;

    morphInterface.erodeRECONSTRUCTION(m1.str(), fFirst, fNew);
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

    //marker1 = NULL;
    //marker2 = NULL;
}

void MorphDSLParser::dilateImpl(std::string id1, std::string id2) {
    cout << "DILATE - RECONSTRUCTION MARKER" << endl;

    string fFirst = getNewImageNameFromId(id1);
    cout << "<--  " << fFirst << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    //					if (marker1!=NULL)
    //					{
    stringstream m1; //create a stringstream
    m1 << "./";
    m1 << imeIzhodneSlike;
    //m1 << marker1->getText()[0]-96;
    m1 << id2[0] - 96;
    m1 << ".bmp";
    cout << "<--  " << m1.str() << endl;

    morphInterface.dilateRECONSTRUCTION(m1.str(), fFirst, fNew);
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

    //marker1 = NULL;
    //marker2 = NULL;
}

void MorphDSLParser::openImpl(double number, std::string id) {
    cout << "OPEN RECONSTRUCTION BOX" << endl;

    string fLast = getNewImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.openRECONSTRUCTION_BOX(number, fLast, fNew);
    cout << "---END" << endl;
}

void MorphDSLParser::closeImpl(double number, std::string id) {

    cout << "CLOSE RECONSTRUCTION BOX" << endl;

    string fLast = getNewImageNameFromId(id);
    cout << "<--  " << fLast << endl;

    string fNew = getNewImageName();
    cout << "-->  " << fNew << endl;

    morphInterface.closeRECONSTRUCTION_BOX(number, fLast, fNew);
    cout << "---END" << endl;
}
