#include "stdafx.h"
#include "ConsoleLogger.h"
#include <iostream>
#include "Identifier.h"

using namespace LPM_MorphDSL;
using namespace std;

void ConsoleLogger::logLine(const string& message) {
    cout << message << endl;
}

void ConsoleLogger::errorId(const string& id) {
    cerr << "ERROR: Spremenljivka '" << id << "' ne obstaja." << endl;
}

void ConsoleLogger::errorId(const Identifier& id) {
    cerr << "ERROR: Spremenljivka '" << id.getText() << "' ne obstaja. (" << id.getToken()->get_line() << ", " << id.getToken()->getCharPositionInLine() << ")" << endl;
}

void ConsoleLogger::errorNotVector(const Identifier& id) {
    cerr << "ERROR: Spremenljivka '" << id.getText() << "' ni vektor." << endl;
}

void ConsoleLogger::startSection(const string& section) {
    cout << section << endl;
}

void ConsoleLogger::endSection() {
    cout << "---END" << endl;
}

void ConsoleLogger::inputString(const string& string) {
    cout << "<--  " << string << endl;
}

void ConsoleLogger::inputValue(const double value) {
    cout << "<--   " << value << endl;
}

void ConsoleLogger::inputId(const string& id, const string& imageName) {
    cout << "<--  " << imageName << " (" << id << ")" << endl;
}

void ConsoleLogger::outputId(const string& id, const string& imageName) {
    cout << "-->  " << imageName << " (" << id << ")" << endl;
}

void ConsoleLogger::outputString(const string& string) {
    cout << "-->  " << string << endl;
}