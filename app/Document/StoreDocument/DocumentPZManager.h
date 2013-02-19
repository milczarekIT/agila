#ifndef DOCUMENTPZMANAGER_H
#define DOCUMENTPZMANAGER_H

#include "Document/StoreDocument/StoreDocumentManager.h"

class DocumentPZManager : public StoreDocumentManager
{
public:
    DocumentPZManager();
    ~DocumentPZManager();
    void setContractor(Contractor c);
    Contractor getContractor();
};

#endif // DOCUMENTPZMANAGER_H
