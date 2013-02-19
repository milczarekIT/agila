#ifndef ARGUMENTSANALYZER_H
#define ARGUMENTSANALYZER_H

#include <QString>
#include <QDebug>
#include "ApplicationInfo.h"

class ArgumentsAnalyzer
{
public:
    ArgumentsAnalyzer();

    void analyze(int argc, char *argv[]);
};

#endif // ARGUMENTSANALYZER_H
