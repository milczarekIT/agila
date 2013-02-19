#ifndef PURCHASEINVOICEMANAGER_H
#define PURCHASEINVOICEMANAGER_H

#include "Document/SaleDocument/InvoiceManager.h"
#include "Document/PurchaseDocument/PurchaseInvoice.h"

class PurchaseInvoiceManager : public InvoiceManager
{

public:

    PurchaseInvoiceManager();
    ~PurchaseInvoiceManager();
    void setPurchaseInvoiceData(PurchaseInvoice doc);
    PurchaseInvoice getPurchaseInvoiceOld();
    PurchaseInvoice getPurchaseInvoice();
    void setPurchaseInvoiceOld(PurchaseInvoice purchaseInvoiceOld);
    void setPurchaseInvoice(PurchaseInvoice purchaseInvoice);
    void setContractor(Contractor c);
    Contractor getContractor();

protected:
    PurchaseInvoice purchaseInvoice,purchaseInvoiceOld;

};

#endif // PURCHASEINVOICEMANAGER_H
