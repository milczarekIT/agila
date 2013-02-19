#include "GoodsCacheService.h"

GoodsCacheService::GoodsCacheService() : CacheService()
{
    initOccurence();
    this->query = new QSqlQuery(Database::getInstance().db);
    this->cacheGroup = "GOOD";
}


GoodsCacheService::~GoodsCacheService() {
    delete query;
}


bool GoodsCacheService::isUsed(int id) {
    this->id = id;

    return isOccurenceInDatabase();
}

void GoodsCacheService::initOccurence()
{
    tables << "documents_positions";
    fields << "good";
}

bool GoodsCacheService::isOccurenceInDatabase()
{
    for(int i = 0; i < tables.size(); i++)
    {
        query->prepare("SELECT " + fields.at(i) + " FROM " + tables.at(i) + " WHERE " + fields.at(i) + " = " + QString::number(id));
        query->exec();

        if(query->size() > 0)
            return true;
    }
    return false;
}
