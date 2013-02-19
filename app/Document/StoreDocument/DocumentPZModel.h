#ifndef DOCUMENTPZMODEL_H
#define DOCUMENTPZMODEL_H

#include "Document/StoreDocument/DocumentPZ.h"
#include "Contractor/ContractorService.h"
#include "Document/StoreDocument/TransportModel.h"

class DocumentPZModel : public DocumentModel
{

public:
    DocumentPZModel();

    DocumentPZ getDocumentPZ(QString symbol);
    void addDocumentPZ(DocumentPZ document);
    void editDocumentPZ(DocumentPZ newDocument);
    void removeDocument(QString symbol);
};

#endif // DOCUMENTPZMODEL_H
