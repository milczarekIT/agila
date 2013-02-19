#ifndef CASHDOCUMENTMODEL_H
#define CASHDOCUMENTMODEL_H

#include "Document/DocumentModel.h"
#include "Contractor/ContractorService.h"
#include "Document/CashDocument/CashDocument.h"

class CashDocumentModel : public DocumentModel
{
public:
    CashDocumentModel();

    CashDocument getCashDocument(QString symbol);
    void addCashDocument(CashDocument document);
    void editCashDocument(CashDocument newDocument);
    void removeCashDocument(QString symbol);
};

#endif // CASHDOCUMENTMODEL_H
