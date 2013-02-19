#ifndef StorageManager_H
#define StorageManager_H

#include "Document/StoreDocument/StoreDocumentManager.h"

class StorageManager : public StoreDocumentManager
{
public:
    StorageManager();
    ~StorageManager();
    void setContractor(Contractor c);
    Contractor getContractor();
};

#endif // StorageManager_H
