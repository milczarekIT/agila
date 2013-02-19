#ifndef CACHESERVICE_H
#define CACHESERVICE_H

#include "Database/Database.h"
#include "Other/Exceptions/SQLException.h"
#include "Other/Application/ApplicationManager.h"

/**
  * Klasa odpowiadająca za 'cache'owanie' danych w bazie danych
  * @author Bartosz Milczarek
  */
class CacheService
{
protected:

    // cached ids
    int id;
    QString symbol;

    QStringList tables;
    QStringList fields;

    /** np. CON - contractor, GOOD - towary itp **/
    QString cacheGroup;

    QSqlQuery *query;
public:
    CacheService();
    ~CacheService();

    void saveHistory(int oldId, int newId);
    int getActualIdForId(int id);
};

#endif // CACHESERVICE_H
