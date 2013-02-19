#ifndef STOREDOCUMENTMANAGER_H
#define STOREDOCUMENTMANAGER_H

#include "Document/DocumentManager.h"

class StoreDocumentManager : public DocumentManager
{
public:
    StoreDocumentManager();
    ~StoreDocumentManager();
    void itIsTheSamePosition(DocumentPosition dp,int i);
};

#endif // STOREDOCUMENTMANAGER_H
