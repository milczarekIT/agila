#ifndef PURCHASEMANAGER_H
#define PURCHASEMANAGER_H

#include "Document/DocumentManager.h"

class PurchaseManager : public DocumentManager
{
public:
    PurchaseManager();

    void setContractor(Contractor c);
    Contractor getContractor();
};

#endif // PURCHASEMANAGER_H
