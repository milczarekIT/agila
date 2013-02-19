#ifndef OWNERMODEL_H
#define OWNERMODEL_H

#include "Other/Owner/Owner.h"
#include "Database/Model.h"

class OwnerModel : public Model
{
public:
    OwnerModel();

    bool isOwnerDefinied();
    Owner getOwner(int id);
    Owner getActualOwner();
    int addOwner(Owner o);
    void editOwner(Owner o);
    void deactivateOwnerInDb(int id);
};

#endif // OWNERMODEL_H
