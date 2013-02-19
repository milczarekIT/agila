#ifndef PURCHASEINVOICESERVICE_H
#define PURCHASEINVOICESERVICE_H

#include "Document/PurchaseDocument/PurchaseInvoiceModel.h"
#include "Document/DocumentService.h"

class PurchaseInvoiceService : public DocumentService
{
private:
    PurchaseInvoiceModel *model;
    PurchaseInvoice invoice;
public:
    PurchaseInvoiceService();
    ~PurchaseInvoiceService();

    PurchaseInvoice getPurchaseInvoice(QString symbol);
    void addPurchaseInvoice(PurchaseInvoice invoice);
    void editPurchaseInvoice(PurchaseInvoice newInvoice);
    void removePurchaseInvoice(QString symbol, bool cancelStoreResult = true);
};

#endif // PURCHASEINVOICESERVICE_H
