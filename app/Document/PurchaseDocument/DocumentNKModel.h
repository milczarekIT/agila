#ifndef DOCUMENTNKMODEL_H
#define DOCUMENTNKMODEL_H

#include "Document/PurchaseDocument/DocumentNK.h"
#include "Contractor/ContractorService.h"

class DocumentNKModel : public DocumentModel
{
public:
    DocumentNKModel();

    DocumentNK getDocumentNK(QString symbol);
    void addDocumentNK(DocumentNK document);
    void editDocumentNK(DocumentNK newDocument);
    void removeDocumentNK(QString symbol);
};

#endif // DOCUMENTNKMODEL_H
