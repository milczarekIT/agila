#ifndef SALEMANAGER_H
#define SALEMANAGER_H

#include "Document/DocumentManager.h"
#include "Document/SaleDocument/Invoice.h"

class SaleManager : public DocumentManager
{

public:
    SaleManager();
    ~SaleManager();

    void setContractor(Contractor c);
    Contractor getContractor();
};

#endif // SALEMANAGER_H
