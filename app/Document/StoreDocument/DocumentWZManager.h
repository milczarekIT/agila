#ifndef DOCUMENTWZMANAGER_H
#define DOCUMENTPZMANAGER_H

#include "Document/StoreDocument/StoreDocumentManager.h"

class DocumentWZManager : public StoreDocumentManager
{
public:
    DocumentWZManager();
    ~DocumentWZManager();
    void setContractor(Contractor c);
    Contractor getContractor();
};

#endif // DOCUMENTWZMANAGER_H
