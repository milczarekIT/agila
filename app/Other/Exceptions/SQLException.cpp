#include "SQLException.h"

SQLException::SQLException(QString sourceMethod, QSqlQuery *query) : Exception(sourceMethod, query->lastError().databaseText())
{
    logger = new Logger();
    logger->log("Method: " + sourceMethod);
    logger->log(query->lastError().databaseText());
}

SQLException::~SQLException() {
    delete logger;
}

QString SQLException::getLogFilePath() {
    return logger->getLogFilePath();
}
