#ifndef DOCUMENTFKPOLICY_H
#define DOCUMENTFKPOLICY_H

#include "Document/SaleDocument/DocumentFK.h"

class DocumentFKPolicy
{
public:
    DocumentFKPolicy();
    ~DocumentFKPolicy();

    DocumentFK getFK();
    DocumentFK getFKOld();
    void setFK(DocumentFK fk);
    void setFKOld(DocumentFK fkOld);
    void setFactureData(DocumentFK FK);
    void setContractor(Contractor c);
    Contractor getContractor();
    void setInvoice(Invoice fv);
    Invoice getInvoice();

private:

DocumentFK fk,fkOld;
};

#endif // DOCUMENTFKPOLICY_H
