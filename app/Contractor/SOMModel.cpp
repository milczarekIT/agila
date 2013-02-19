#include "SOMModel.h"

SOMModel::SOMModel()
{

}

SOMModel::~SOMModel()
{
}

QVector<SourceOfMember> SOMModel::getSourcesOfMember()
{
    QVector<SourceOfMember> sources;
    query = new QSqlQuery(Database::getInstance().db);
    query->exec("SELECT id_source, name FROM sources_of_member WHERE is_active = true");

    if(this->isQueryError(query))
        throw new SQLException("SOMModel::getSourcesOfMember", query);
    else if(query->size() > 0)
    {
        SourceOfMember *som = new SourceOfMember();
        while(query->next())
        {
            som->setId(query->value(0).toInt());
            som->setName(query->value(1).toString());
            sources.push_back(*som);
        }
        delete som;
    }
    delete query;

    return sources;
}

SourceOfMember SOMModel::getSourceOfMember(int id)
{
    SourceOfMember som;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT name FROM sources_of_member WHERE id_source = :id");
    query->bindValue(":id", id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("SOMModel::getSourceOfMember", query);
    else if(query->size() > 0)
    {
        query->first();

        som.setId(id);
        som.setName(query->value(0).toString());
    }
    delete query;

    return som;
}

void SOMModel::addSourceOfMember(SourceOfMember som)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO sources_of_member (name) VALUES (:name)");
    query->bindValue(":name", som.getName());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("SOMModel::addSourceOfMember", query);

    delete query;
}

void SOMModel::editSourceOfMember(SourceOfMember som)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE sources_of_member SET name = :name WHERE id_source = :id");
    query->bindValue(":name", som.getName());
    query->bindValue(":id", som.getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("SOMModel::editSourceOfMember", query);

    delete query;
}

void SOMModel::removeSourceOfMember(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE sources_of_member SET is_active = false WHERE id_source = :id");
    query->bindValue(":id", id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("SOMModel::removeSourceOfMember", query);

    delete query;
}
