#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

bool Model::isQueryError(QSqlQuery query)
{
    if(query.lastError().isValid()) return true;
    else return false;
}

bool Model::isQueryError(QSqlQuery *query)
{
    if(query->lastError().isValid()) return true;
    else return false;
}

void Model::debugQueryError(QSqlQuery query, QString metodName)
{
    if(Database::ECHO_ERROR)
        qDebug() << "Błąd query w  metodzie: " << metodName << "ErrorText: \n" << query.lastError().databaseText();

}

void Model::debugQueryError(QSqlQuery *query, QString metodName)
{
    if(Database::ECHO_ERROR)
        qDebug() << "Błąd query w  metodzie: " << metodName << "ErrorText: \n" << query->lastError().databaseText();

}
