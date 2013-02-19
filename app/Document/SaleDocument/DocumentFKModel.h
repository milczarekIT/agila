#ifndef DocumentFKMODEL_H
#define DocumentFKMODEL_H

#include "Document/DocumentModel.h"
#include "Document/SaleDocument/DocumentFK.h"
#include "Contractor/ContractorModel.h"
#include "Document/SaleDocument/InvoiceService.h"

class DocumentFKModel : public DocumentModel
{
public:
    DocumentFKModel();

    DocumentFK getDocumentFK(QString symbol);
    QString getInvoiceSymbolByDocumentFK(QString documentFK);
    void addDocumentFK(DocumentFK fk);
    void editDocumentFK(DocumentFK newFk);
    void removeDocumentFK(QString symbol);

};

#endif // DocumentFKMODEL_H
