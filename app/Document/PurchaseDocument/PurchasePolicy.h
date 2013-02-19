#ifndef PURCHASEPOLICY_H
#define PURCHASEPOLICY_H

#include "Document/PurchaseDocument/PurchaseInvoice.h"

class PurchasePolicy
{
public:
    PurchasePolicy();
    ~PurchasePolicy();
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

#endif // PURCHASEPOLICY_H
