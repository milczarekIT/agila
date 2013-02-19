#ifndef DocumentFK_H
#define DocumentFK_H

#include "Document/SaleDocument/Invoice.h"

class DocumentFK : public Invoice
{
    Invoice fv;

    void copyInvoiceData();

public:
    DocumentFK();
    DocumentFK(Invoice fv);

    void setInvoice(Invoice fv);

    Invoice getInvoice();
    int operator == (DocumentFK doc);
};

#endif // DocumentFK_H
