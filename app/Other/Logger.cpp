#include "Logger.h"

Logger::Logger()
{
    mkDirIfNotExist();
    now = QDateTime::currentDateTime();

    QString fileName = "log_" + now.toString("yyyyMMdd_HHmmsszz") + ".log";
    logFilePath = Logger::PATH + QDir::separator() + fileName;
    file = new QFile(logFilePath);
    file->open(QIODevice::WriteOnly | QIODevice::Text);
}

Logger::~Logger() {
    file->close();
}

void Logger::mkDirIfNotExist() {
    QDir dir(Logger::PATH);

    if(!dir.exists(Logger::PATH))
        dir.mkdir(Logger::PATH);
}

const QString Logger::PATH = QDir::homePath() + QDir::separator() + ".agila";

void Logger::log(QString text) {
    QTextStream stream(file);
    stream << text << "\n";
}

QString Logger::getLogFilePath() {
    return logFilePath;
}
