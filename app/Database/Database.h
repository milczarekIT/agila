#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSettings>
#include <QSqlDatabase>
#include "Other/Warehouse/Warehouse.h"

/**
  * Klasa odpowiadająca za połączenie z bazą danych
  * @author Bartosz Milczarek, Jan Krajewski
  */
class Database : public QSqlDatabase
{
    QSettings settings;
    void initConnection();

public:

    static Database& getInstance();
    /**
      * Stała statyczna, która określa czy błedy w zapytaniach SQL mają być wyswietlane w qDebug()
      */
    static const bool ECHO_ERROR = true;
    QSqlDatabase db;

    /**
      * W konstruktorze wywoływana jest metoda setDatabaseConnection() oraz otwierane połączenie z bazą danych
      */
    Database();
    ~Database();

};

#endif // DATABASE_H

