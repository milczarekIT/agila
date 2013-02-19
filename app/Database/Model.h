#ifndef MODEL_H
#define MODEL_H

#include <QtSql>
#include "Database.h"
#include "Other/Exceptions/SQLException.h"

/**
  * Klasa bazowa dla wszystkich klas pełniących rolę Modelu
  * @author Bartosz Milczarek
  */
class Model
{
protected:
    Database *database;
    QSqlQuery *query;
    bool isQueryError(QSqlQuery query);
    bool isQueryError(QSqlQuery *query);
    void debugQueryError(QSqlQuery query, QString metodName);
    void debugQueryError(QSqlQuery *query, QString metodName);

public:
    Model();
    ~Model();

};

#endif // MODEL_H
