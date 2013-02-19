#ifndef PURCHASEINVOICE_H
#define PURCHASEINVOICE_H

#include "Document/SaleDocument/Invoice.h"

class PurchaseInvoice : public Invoice
{
protected:
    QString purchaseDocument;

public:
    PurchaseInvoice();

    void setPurchaseDocument(QString purchaseDocument = " ");

    QString getPurchaseDocument();
    int operator ==(PurchaseInvoice in);
};

#endif // PURCHASEINVOICE_H
