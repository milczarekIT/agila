#ifndef DOCUMENTPAPOLICY_H
#define DOCUMENTPAPOLICY_H

#include "Document/SaleDocument/InvoicePolicy.h"

class DocumentPAPolicy : public InvoicePolicy
{
public:
    DocumentPAPolicy();
    void setDocumentData(Invoice doc);
};

#endif // DOCUMENTPAPOLICY_H
