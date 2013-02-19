#include "TransportModel.h"

TransportModel::TransportModel() {
}


QVector<SimpleStructure> TransportModel::getMeansOfTransport() {
    QVector<SimpleStructure> mot;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id_transport, name FROM means_of_transport WHERE is_active = true");
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("TransportModel::getMeansOfTransport", query);

    SimpleStructure ss;
    while(query->next())
    {
        ss.setId(query->value(0).toInt());
        ss.setName(query->value(1).toString());
        mot.push_back(ss);
    }
    delete query;

    return mot;
}


SimpleStructure TransportModel::getMeanOfTransport(int id) {
    SimpleStructure ss;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT name FROM means_of_transport WHERE id_transport = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("TransportModel::getMeanOfTransport", query);
    else if(query->size() > 0)
    {
        query->first();

        ss.setId(id);
        ss.setName(query->value(0).toString());
    }
    delete query;

    return ss;
}


void TransportModel::addMeanOfTransport(SimpleStructure transport)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO means_of_transport (name) VALUES (?)");
    query->addBindValue(transport.getName());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("TransportModel::addMeanOfTransport", query);

    delete query;
}

void TransportModel::editMeanOfTransport(SimpleStructure transport)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE means_of_transport SET name = ? WHERE id_transport = ?");
    query->addBindValue(transport.getName());
    query->addBindValue(transport.getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("TransportModel::editMeanOfTransport", query);

    delete query;
}

void TransportModel::removeMeanOfTransport(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE means_of_transport SET is_active = false WHERE id_transport = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("TransportModel::removeMeanOfTransport", query);

    delete query;
}
