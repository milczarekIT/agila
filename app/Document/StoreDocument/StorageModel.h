#ifndef StorageModel_H
#define StorageModel_H

#include "Document/StoreDocument/StoreDocument.h"
#include "Contractor/ContractorService.h"
#include "Document/StoreDocument/DepartmentModel.h"

class StorageModel : public DocumentModel
{
public:
    StorageModel();

    StoreDocument getStoreDocument(QString symbol);
    void addStoreDocument(StoreDocument document);
    void editStoreDocument(StoreDocument newDocument);
    void removeDocument(QString symbol);
};

#endif // StorageModel_H
