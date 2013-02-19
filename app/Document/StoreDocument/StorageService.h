#ifndef StorageService_H
#define StorageService_H

#include "Document/StoreDocument/StorageModel.h"
#include "Document/DocumentService.h"

class StorageService : public DocumentService
{
private:
    StorageModel *model;
    StoreDocument document;
public:
    StorageService();
    ~StorageService();

    StoreDocument getStoreDocument(QString symbol);
    void addStoreDocument(StoreDocument document);
    void editStoreDocument(StoreDocument newDocument);
    void removeDocument(QString symbol, bool cancelStoreResult = true);
};

#endif // StorageService_H
