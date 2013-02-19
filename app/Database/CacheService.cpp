#include "CacheService.h"

CacheService::CacheService()
{
    this->cacheGroup = "NN";
}

CacheService::~CacheService()
{
}

void CacheService::saveHistory(int oldId, int newId)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO cache_history (type, old_id, new_id) VALUES (?, ?, ?)");
    query->addBindValue(cacheGroup);
    query->addBindValue(oldId);
    query->addBindValue(newId);
    query->exec();

    if(query->lastError().isValid())
        throw new SQLException("CacheService::saveHistory", query);
}

int CacheService::getActualIdForId(int id) {
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT new_id FROM cache_history WHERE old_id = ? AND type = ?");
    query->addBindValue(id);
    query->addBindValue(cacheGroup);
    query->exec();
    if(query->size() == 0)
        return id;
    else if(query->size() > 0) {
        query->first();
        int nextId = query->value(0).toInt();
        delete query;

        return this->getActualIdForId(nextId);
    }
    else
        return -1;

}
