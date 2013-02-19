#include "ContractorCacheService.h"

ContractorCacheService::ContractorCacheService() : CacheService()
{
    initOccurence();
    this->cacheGroup = "CON";
}


ContractorCacheService::~ContractorCacheService() {}


bool ContractorCacheService::isUsed(int id) {
    this->id = id;

    return isOccurenceInDatabase();
}

void ContractorCacheService::initOccurence()
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Sale))
    {
        tables << "sale_documents";
        fields << "contractor";
    }

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        tables << "store_documents";
        fields << "contractor";
    }

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Purchase))
    {
        tables << "documents_nk";
        fields << "receiver";
    }

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Cash))
    {
        tables << "cash_documents";
        fields << "contractor";
    }

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Purchase))
    {
        tables << "purchase_documents";
        fields << "contractor";
    }

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    {
        tables << "orders";
        fields << "contractor";
    }
}

bool ContractorCacheService::isOccurenceInDatabase()
{
    for(int i = 0; i < tables.size(); i++)
    {
        query = new QSqlQuery(Database::getInstance().db);
        query->prepare("SELECT " + fields.at(i) + " FROM " + tables.at(i) + " WHERE " + fields.at(i) + " = " + QString::number(id));
        query->exec();

        int querySize = query->size();
        if(querySize > 0)
        {
            delete query;
            return true;
        }
    }
    delete query;
    return false;
}
