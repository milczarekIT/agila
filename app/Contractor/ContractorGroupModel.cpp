#include "ContractorGroupModel.h"

ContractorGroupModel::ContractorGroupModel()
{
}

ContractorGroupModel::~ContractorGroupModel()
{
}

QVector<ContractorGroup> ContractorGroupModel::getContractorGroups()
{
    QVector<ContractorGroup> groups;
    query = new QSqlQuery(Database::getInstance().db);
    query->exec("SELECT id_group, name FROM contractors_groups WHERE is_active = true");

    if(this->isQueryError(query))
        throw new SQLException("ContractorGroupModel::getContractorGroups", query);
    else
    {
        ContractorGroup cg;
        while(query->next())
        {
            cg.setId(query->value(0).toInt());
            cg.setName(query->value(1).toString());
            groups.push_back(cg);
        }
    }

    delete query;

    return groups;
}

ContractorGroup ContractorGroupModel::getContractorGroup(int id)
{
    ContractorGroup cg;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT name FROM contractors_groups WHERE id_group = :id");
    query->bindValue(":id", id);
    query->exec();


    if(this->isQueryError(query))
        throw new SQLException("ContractorGroupModel::getContractorGroup", query);
    else if(query->size() > 0)
    {
        query->first();

        cg.setId(id);
        cg.setName(query->value(0).toString());
    }

    delete query;

    return cg;
}


void ContractorGroupModel::addContractorGroup(ContractorGroup cg)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO contractors_groups (name) VALUES (:name)");
    query->bindValue(":name", cg.getName());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("ContractorGroupModel::addContractorGroup", query);

    delete query;
}

void ContractorGroupModel::editContractorGroup(ContractorGroup cg)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE contractors_groups SET name = :name WHERE id_group = :id_group");
    query->bindValue(":name", cg.getName());
    query->bindValue(":id_group", cg.getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("ContractorGroupModel::editContractorGroup", query);

    delete query;
}

void ContractorGroupModel::removeContractorGroup(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE contractors_groups SET is_active = false WHERE id_group = :id");
    query->bindValue(":id", id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("ContractorGroupModel::removeContractorGroup", query);

    delete query;
}
