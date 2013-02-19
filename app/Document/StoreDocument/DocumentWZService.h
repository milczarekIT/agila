#ifndef DOCUMENTWZSERVICE_H
#define DOCUMENTWZSERVICE_H

#include "Document/StoreDocument/DocumentWZModel.h"
#include "Document/DocumentService.h"

class DocumentWZService : public DocumentService
{
private:
    DocumentWZModel *model;
    DocumentWZ document;
public:
    DocumentWZService();
    ~DocumentWZService();

    DocumentWZ getDocumentWZ(QString symbol);
    void addDocumentWZ(DocumentWZ document);
    void editDocumentWZ(DocumentWZ newDocument);
    void removeDocument(QString symbol, bool cancelStoreResult = true);
};

#endif // DOCUMENTWZSERVICE_H
