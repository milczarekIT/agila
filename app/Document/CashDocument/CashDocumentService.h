#ifndef CASHDOCUMENTSERVICE_H
#define CASHDOCUMENTSERVICE_H

#include "Document/CashDocument/CashDocumentModel.h"
#include "Document/DocumentService.h"

class CashDocumentService : public DocumentService
{
private:
    CashDocumentModel *model;
    CashDocument document;
public:
    CashDocumentService();
    ~CashDocumentService();

    CashDocument getCashDocument(QString symbol);
    void addCashDocument(CashDocument document);
    void editCashDocument(CashDocument newDocument);
    void removeCashDocument(QString symbol);
};

#endif // CASHDOCUMENTSERVICE_H
