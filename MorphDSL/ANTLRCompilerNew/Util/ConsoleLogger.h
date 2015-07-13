#pragma once
#include "../Interfaces/ILogger.h"

namespace LPM_MorphDSL {
    using namespace std;

    class ConsoleLogger : public ILogger {
      public:

        void logLine(const string& message) override;

        void errorId(const string& id) override;
        void errorId(const Identifier& id) override;
        void errorNotVector(const Identifier& id) override;

        void startSection(const string& section) override;
        void endSection() override;

        void inputString(const string& string) override;
        void inputValue(const double value) override;
        void inputId(const string& id, const string& imageName) override;

        void outputId(const string& id, const string& imageName) override;
        void outputString(const string& string) override;
    };

}