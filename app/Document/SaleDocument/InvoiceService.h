#ifndef INVOICESERVICE_H
#define INVOICESERVICE_H

#include "Document/SaleDocument/InvoiceModel.h"
#include "Document/DocumentService.h"

class InvoiceService : public DocumentService
{
protected:
    InvoiceModel *model;
    Invoice invoice;

public:
    InvoiceService();
    ~InvoiceService();

    Invoice getInvoice(QString symbol);
    void addInvoice(Invoice invoice);
    void editInvoice(Invoice newInvoice);
    void removeInvoice(QString symbol, bool cancelStoreResult = true);
};

#endif // INVOICESERVICE_H
