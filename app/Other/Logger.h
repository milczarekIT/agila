#ifndef LOGGER_H
#define LOGGER_H

#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>
//#include "ApplicationManager.h"

class Logger
{
private:
    QDateTime now;
    QFile *file;
    QString logFilePath;

    void mkDirIfNotExist();
public:
    Logger();
    ~Logger();

    static const QString PATH;

    void log(QString text);

    QString getLogFilePath();
};

#endif // LOGGER_H
