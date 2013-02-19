#ifndef DOCUMENTPZSERVICE_H
#define DOCUMENTPZSERVICE_H

#include "Document/StoreDocument/DocumentPZModel.h"
#include "Document/DocumentService.h"

class DocumentPZService : public DocumentService
{
private:
    DocumentPZModel *model;
    DocumentPZ document;
public:
    DocumentPZService();
    ~DocumentPZService();

    DocumentPZ getDocumentPZ(QString symbol);
    void addDocumentPZ(DocumentPZ document);
    void editDocumentPZ(DocumentPZ newDocument);
    void removeDocument(QString symbol, bool cancelStoreResult = true);
};

#endif // DOCUMENTPZSERVICE_H
