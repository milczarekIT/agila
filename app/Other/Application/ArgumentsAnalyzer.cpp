#include "ArgumentsAnalyzer.h"

ArgumentsAnalyzer::ArgumentsAnalyzer()
{
}

void ArgumentsAnalyzer::analyze(int argc, char *argv[])
{
    for(int i = 1; i < argc; i++)
    {
        QString arg = argv[i];
        if(arg == "-v" || arg == "--version")
        {
            qDebug() << "Wersja: " << ApplicationInfo::getVersionName();
        }
    }
}
