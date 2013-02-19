#ifndef DOCUMENTFZKPOLICY_H
#define DOCUMENTFZKPOLICY_H

#include "Document/PurchaseDocument/DocumentFZK.h"

class DocumentFZKPolicy
{
public:
    DocumentFZKPolicy();
    ~DocumentFZKPolicy();

    DocumentFZK getFZK();
    DocumentFZK getFZKOld();
    void setFZK(DocumentFZK fzk);
    void setFZKOld(DocumentFZK fzkOld);
    void setFactureData(DocumentFZK FZK);
    void setContractor(Contractor c);
    Contractor getContractor();
    void setPurchaseInvoice(PurchaseInvoice fv);
    PurchaseInvoice getPurchaseInvoice();

private:

DocumentFZK fzk,fzkOld;
};

#endif // DOCUMENTFZKPOLICY_H
