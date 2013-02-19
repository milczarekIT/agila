#include "ContractorAdditionalTypeIdModel.h"

ContractorAdditionalTypeIdModel::ContractorAdditionalTypeIdModel()
{
}

ContractorAdditionalTypeIdModel::~ContractorAdditionalTypeIdModel()
{
}


QVector<SimpleStructure> ContractorAdditionalTypeIdModel::getTypeIds()
{
    QVector<SimpleStructure> typeIds;
    query = new QSqlQuery(Database::getInstance().db);
    query->exec("SELECT id, name FROM contractors_additional_ids");

    if(this->isQueryError(query))
        throw new SQLException("ContractorAdditionalTypeIdModel::getTypeIds", query);
    else if(query->size() > 0)
    {
        SimpleStructure ss;
        while(query->next())
        {
            ss.setId(query->value(0).toInt());
            ss.setName(query->value(1).toString());
            typeIds.push_back(ss);
        }
    }

    delete query;

    return typeIds;
}

SimpleStructure ContractorAdditionalTypeIdModel::getTypeId(int id)
{
    SimpleStructure ss;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT name FROM contractors_additional_ids WHERE id = :id");
    query->bindValue(":id", id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("ContractorAdditionalTypeIdModel::getTypeId", query);
    else if(query->size())
    {
        query->first();

        ss.setId(id);
        ss.setName(query->value(0).toString());
    }

    delete query;

    return ss;
}



