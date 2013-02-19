#ifndef OWNERCACHESERVICE_H
#define OWNERCACHESERVICE_H

#include "Database/CacheService.h"
#include "Other/Warehouse/WarehouseModel.h"

/**
  * Klasa odwowiedzialna za Cache'owanie Ownera
  * historia cache'owania znajduje się w magazynie aktualnie używanym a nie w pigstore conf
  *
  * @author Bartosz Milczarek
  */
class OwnerCacheService : public CacheService
{
private:
    void initOccurence();
    bool isOccurenceInDatabase();

public:
    OwnerCacheService();
    ~OwnerCacheService();

    bool isUsed(int id);
};

#endif // OWNERCACHESERVICE_H
