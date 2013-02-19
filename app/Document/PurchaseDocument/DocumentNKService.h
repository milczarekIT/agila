#ifndef DOCUMENTNKSERVICE_H
#define DOCUMENTNKSERVICE_H

#include "Document/PurchaseDocument/DocumentNKModel.h"
#include "Document/DocumentService.h"

class DocumentNKService : public DocumentService
{
private:
    DocumentNKModel *model;
    DocumentNK document;
public:
    DocumentNKService();
    ~DocumentNKService();

    DocumentNK getDocumentNK(QString symbol);
    void addDocumentNK(DocumentNK document);
    void editDocumentNK(DocumentNK newDocument);
    void removeDocumentNK(QString symbol);
};

#endif // DOCUMENTNKSERVICE_H
