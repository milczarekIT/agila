#ifndef DOCUMENTRRMANAGER_H
#define DOCUMENTRRMANAGER_H

#include "Document/PurchaseDocument/PurchaseInvoiceManager.h"

class DocumentRRManager : public PurchaseInvoiceManager
{
public:
    DocumentRRManager();
    ~DocumentRRManager();
    void setDocumentRRData(PurchaseInvoice doc);

};

#endif // DOCUMENTRRMANAGER_H
