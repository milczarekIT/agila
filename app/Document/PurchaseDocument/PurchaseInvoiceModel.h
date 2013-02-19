#ifndef PURCHASEINVOICEMODEL_H
#define PURCHASEINVOICEMODEL_H

#include "Document/PurchaseDocument/PurchaseInvoice.h"
#include "Document/DocumentModel.h"
#include "Contractor/ContractorService.h"
#include "Document/MOPModel.h"

class PurchaseInvoiceModel : DocumentModel
{
public:
    PurchaseInvoiceModel();
    ~PurchaseInvoiceModel();

    PurchaseInvoice getPurchaseInvoice(QString symbol);
    void addPurchaseInvoice(PurchaseInvoice invoice);
    void editPurchaseInvoice(PurchaseInvoice newInvoice);
    void removePurchaseInvoice(QString symbol);
};

#endif // PURCHASEINVOICEMODEL_H
