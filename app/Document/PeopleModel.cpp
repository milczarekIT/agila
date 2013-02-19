#include "PeopleModel.h"

PeopleModel::PeopleModel()
{

}

PeopleModel::~PeopleModel() {

}

int PeopleModel::getPersonId(QString name)
{
    if(name.isEmpty())
        return 0;

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id FROM people WHERE name = ?");
    query->addBindValue(name);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("PeopleModel::getPersonId", query);

    if(query->size() == 0)
    {
        int insertedId = this->addPerson(name);
        return insertedId;
    }
    else {
        query->first();

        int id = query->value(0).toInt();
        delete query;

        return id;
    }

}

int PeopleModel::addPerson(QString name)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO people (id, name) VALUES(DEFAULT, ?) RETURNING id");
    query->addBindValue(name);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("PeopleModel::addPerson", query);

    query->next();
    int addedId = query->record().value("id").toInt();
    delete query;

    return addedId;
}

QString PeopleModel::getName(int id)
{
    QString name = "";
    if(id > 0)
    {
        query = new QSqlQuery(Database::getInstance().db);
        query->prepare("SELECT name FROM people WHERE id = ?");
        query->addBindValue(id);
        query->exec();

        if(query->size() > 0)
        {
            query->first();

            name = query->value(0).toString();
        }
    }

    return name;
}
