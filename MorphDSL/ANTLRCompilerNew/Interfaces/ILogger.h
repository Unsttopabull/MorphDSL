#pragma once
#include <string>

namespace LPM_MorphDSL {
    class Identifier;
    using namespace std;

    class ILogger {
    public:
        virtual ~ILogger() {
        }

        virtual void errorId(const string& id) = 0;
        virtual void errorId(const Identifier& id) = 0;
        virtual void errorNotVector(const Identifier& id) = 0;

        virtual void startSection(const string& section) = 0;
        virtual void endSection() = 0;

        virtual void inputString(const string& string) = 0;
        virtual void inputValue(const double value) = 0;
        virtual void inputId(const string& id, const string& imageName) = 0;

        virtual void outputId(const string& id, const string& imageName) = 0;
        virtual void outputString(const string& string) = 0;

        virtual void logLine(const string& message) = 0;
    };
}
