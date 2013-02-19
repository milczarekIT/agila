#include "DocumentPlaceModel.h"

DocumentPlaceModel::DocumentPlaceModel()
{
}

SimpleStructure DocumentPlaceModel::getDocumentPlace(int id)
{
    SimpleStructure dp;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT name FROM document_places WHERE id_place = ?");
    query->addBindValue(id);
    query->exec();
    query->first();

    dp.setId(id);
    dp.setName(query->value(0).toString());

    if(this->isQueryError(query))
            throw new SQLException("DocumentPlaceModel::getDocumentPlace", query);

    delete query;

    return dp;
}

int DocumentPlaceModel::getDocumentPlaceId(QString name)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id_place FROM document_places WHERE name = ?");
    query->addBindValue(name);
    query->exec();


    if(this->isQueryError(query))
        throw new SQLException("DocumentPlaceModel::getDocumentPlaceId", query);

    if(query->size() == 0)
    {
        // brak wyników
        int newId = this->addDocumentPlace(name);
        return newId;
    }
    else
    {
        query->first();

        return query->value(0).toInt(); // id_place
    }

}

int DocumentPlaceModel::addDocumentPlace(QString name)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO document_places (id_place, name) VALUES(DEFAULT,?)");
    query->addBindValue(name);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentPlaceModel::addDocumentPlace", query);

    query->next();
    int insertedId = query->record().value("id_place").toInt();

    return insertedId;
}
