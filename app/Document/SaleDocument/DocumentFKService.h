#ifndef DOCUMENTFKSERVICE_H
#define DOCUMENTFKSERVICE_H

#include "Document/DocumentService.h"
#include "Document/SaleDocument/DocumentFKModel.h"
#include "Document/DocumentPositionFKService.h"

class DocumentFKService : public DocumentService
{
private:
    DocumentFKModel *model;
    DocumentFK documentFK;
    DocumentPositionFKService *documentPositionFKService;
public:
    DocumentFKService();
    ~DocumentFKService();

    DocumentFK getDocumentFK(QString symbol);
    void addDocumentFK(DocumentFK fk);
    void editDocumentFK(DocumentFK newFk);
    void removeDocumentFK(QString symbol, bool cancelStoreResult = true);
};

#endif // DOCUMENTFKSERVICE_H
