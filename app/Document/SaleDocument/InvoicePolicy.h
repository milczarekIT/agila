#ifndef INVOICEPOLICY_H
#define INVOICEPOLICY_H

#include "Document/SaleDocument/Invoice.h"

class InvoicePolicy
{
public:
    InvoicePolicy();
    ~InvoicePolicy();
    Invoice getInvoice();
    Invoice getOldInvoice();
    void setInvoice(Invoice invoice);
    void setOldInvoice(Invoice invoiceOld);
    void setContractor(Contractor c);
    Contractor getContractor();
    virtual void setDocumentData(Invoice doc);

protected:

    Invoice invoice,oldInvoice;
};

#endif // INVOICEPOLICY_H
