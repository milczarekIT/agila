#ifndef DOCUMENTWZMODEL_H
#define DOCUMENTWZMODEL_H

#include "Document/StoreDocument/DocumentWZ.h"
#include "Document/DocumentModel.h"
#include "Document/StoreDocument/TransportModel.h"

class DocumentWZModel : public DocumentModel
{
public:
    DocumentWZModel();

    DocumentWZ getDocumentWZ(QString symbol);
    void addDocumentWZ(DocumentWZ document);
    void editDocumentWZ(DocumentWZ newDocument);
    void removeDocument(QString symbol);
};

#endif // DOCUMENTWZMODEL_H
