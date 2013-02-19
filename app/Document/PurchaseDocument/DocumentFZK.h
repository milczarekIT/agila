#ifndef DOCUMENTFZK_H
#define DOCUMENTFZK_H

#include "Document/PurchaseDocument/PurchaseInvoice.h"

class DocumentFZK : public PurchaseInvoice
{
private:
    PurchaseInvoice invoice;
    QString purchaseInvoiceCorrection; // nr faktury korekty rzeczywistej

    void copyInvoiceData();

public:
    DocumentFZK();
    DocumentFZK(PurchaseInvoice invoice);

    void setInvoice(PurchaseInvoice invoice);

    void setPurchaseInvoiceCorrection(QString purchaseInvoiceCorrection);
    QString getPurchaseInvoiceCorrection();

    PurchaseInvoice getInvoice();
    int operator == (DocumentFZK doc);
};

#endif // DOCUMENTFZK_H
