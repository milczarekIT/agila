#include "OwnerCacheService.h"

OwnerCacheService::OwnerCacheService()
{
    initOccurence();
    this->query = new QSqlQuery(Database::getInstance().db);
    this->cacheGroup = "OWNER";
}

OwnerCacheService::~OwnerCacheService()
{
    delete query;
}


bool OwnerCacheService::isUsed(int id) {
    this->id = id;

    return isOccurenceInDatabase();
}


void OwnerCacheService::initOccurence() {
    tables << "sale_documents";
    fields << "owner";

    tables << "store_documents";
    fields << "owner";

    tables << "documents_nk";
    fields << "owner";

    tables << "cash_documents";
    fields << "owner";

    tables << "purchase_documents";
    fields << "owner";

    tables << "orders";
    fields << "owner";
}

bool OwnerCacheService::isOccurenceInDatabase()
{
    for(int i = 0; i < tables.size(); i++)
    {
        query->prepare("SELECT " + fields.at(i) + " FROM " + tables.at(i) + " WHERE " + fields.at(i) + " = "
                       + QString::number(id));
        query->exec();

        if(query->size() > 0)
            return true;
    }
    return false;
}

