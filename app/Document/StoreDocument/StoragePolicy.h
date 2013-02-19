#ifndef StoragePolicy_H
#define StoragePolicy_H

#include "Document/StoreDocument/StoreDocument.h"

class StoragePolicy
{
public:
    StoragePolicy();
    ~StoragePolicy();
    StoreDocument getStoreDocument();
    StoreDocument getOldStoreDocument();
    void setStoreDocument(StoreDocument storeDocument);
    void setOldStoreDocument(StoreDocument storeDocumentOld);
    void setContractor(Contractor c);
    Contractor getContractor();
    void setDocumentData(StoreDocument doc);

private:

    StoreDocument storeDocument,storeDocumentOld;
};

#endif // StoragePolicy_H
