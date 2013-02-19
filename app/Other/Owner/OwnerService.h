#ifndef OWNERSERVICE_H
#define OWNERSERVICE_H

#include "Other/Service.h"
#include "Other/Owner/OwnerModel.h"
#include "Other/Owner/OwnerCacheService.h"

class OwnerService : public Service
{
    Owner owner;
    OwnerModel *model;
    OwnerCacheService *cacheService;

    int insertedId;
public:
    OwnerService();
    ~OwnerService();

    bool isOwnerDefinied();
    Owner getOwner(int id);
    Owner getActualOwner();
    int addOwner(Owner o);
    void editOwner(Owner o);

};

#endif // OWNERSERVICE_H
