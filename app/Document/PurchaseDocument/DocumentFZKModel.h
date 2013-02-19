#ifndef DOCUMENTFZKMODEL_H
#define DOCUMENTFZKMODEL_H

#include "Document/PurchaseDocument/DocumentFZK.h"
#include "Document/DocumentModel.h"
#include "Document/MOPModel.h"

class DocumentFZKModel : public DocumentModel
{
public:
    DocumentFZKModel();

    DocumentFZK getDocumentFZK(QString symbol);
    void addDocumentFZK(DocumentFZK document);
    void editDocumentFZK(DocumentFZK document);
    void removeDocumentFZK(QString symbol);
};

#endif // DOCUMENTFZKMODEL_H
