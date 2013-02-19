#ifndef INVOICEMANAGER_H
#define INVOICEMANAGER_H

#include "Document/SaleDocument/SaleManager.h"

class InvoiceManager: public SaleManager  {

public:
    InvoiceManager();
    ~InvoiceManager();
};

#endif // INVOICEMANAGER_H
