#ifndef CONTRACTORCACHESERVICE_H
#define CONTRACTORCACHESERVICE_H

#include "Database/CacheService.h"

class ContractorCacheService : public CacheService
{
private:
    void initOccurence();
    bool isOccurenceInDatabase();
public:
    ContractorCacheService();
    ~ContractorCacheService();

    bool isUsed(int id);    
};

#endif // CONTRACTORCACHESERVICE_H
