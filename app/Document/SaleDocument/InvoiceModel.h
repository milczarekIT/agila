#ifndef InvoiceMODEL_H
#define InvoiceMODEL_H

#include "Contractor/Contractor.h"
#include "Contractor/ContractorService.h"
#include "Settings/SettingsModel.h"
#include "Document/DocumentModel.h"
#include "Document/MOPModel.h"
#include "Document/SaleDocument/Invoice.h"

class InvoiceModel : public DocumentModel
{
public:
    InvoiceModel();
    ~InvoiceModel();

    Invoice getInvoice(QString symbol);
    void addInvoice(Invoice fv);
    void editInvoice(Invoice newInvoice);
    void removeInvoice(QString symbol);
};

#endif // InvoiceMODEL_H
