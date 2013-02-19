#ifndef GOODSCACHESERVICE_H
#define GOODSCACHESERVICE_H

#include "Database/CacheService.h"

class GoodsCacheService : public CacheService
{
    void initOccurence();
    bool isOccurenceInDatabase();
public:
    GoodsCacheService();
    ~GoodsCacheService();

    /** sprawdza czy good o danym id jest używany np. na fakturze */
    bool isUsed(int id);
};

#endif // GOODSCACHESERVICE_H
