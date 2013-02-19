#ifndef SQLEXCEPTION_H
#define SQLEXCEPTION_H

#include <QSqlQuery>
#include <QSqlError>
#include "Other/Exceptions/Exception.h"
#include "Other/Logger.h"

class SQLException : public Exception
{
    Logger *logger;
public:
    SQLException(QString sourceMethod, QSqlQuery *query);
    ~SQLException();

    QString getLogFilePath();
};

#endif // SQLEXCEPTION_H
