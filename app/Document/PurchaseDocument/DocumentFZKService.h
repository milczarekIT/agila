#ifndef DOCUMENTFZKSERVICE_H
#define DOCUMENTFZKSERVICE_H

#include "Document/DocumentService.h"
#include "Document/PurchaseDocument/DocumentFZKModel.h"
#include "Document/DocumentPositionFKService.h"

class DocumentFZKService : public DocumentService
{
private:
    DocumentFZKModel *model;
    DocumentFZK documentFZK;
    DocumentPositionFKService *documentPositionFKService;
public:
    DocumentFZKService();
    ~DocumentFZKService();

    DocumentFZK getDocumentFZK(QString symbol);
    void addDocumentFZK(DocumentFZK document);
    void editDocumentFZK(DocumentFZK newDocument);
    void removeDocumentFZK(QString symbol, bool cancelStoreResult = true);
};

#endif // DOCUMENTFZKSERVICE_H
