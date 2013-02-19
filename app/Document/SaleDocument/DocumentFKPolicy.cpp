#include "DocumentFKPolicy.h"

DocumentFKPolicy::DocumentFKPolicy()
{
}
DocumentFKPolicy::~DocumentFKPolicy()
{
}

void DocumentFKPolicy::setFK(DocumentFK fk)
{
    this->fk=fk;
};
void DocumentFKPolicy::setFKOld(DocumentFK fkOld)
{
    this->fkOld=fkOld;
};
DocumentFK DocumentFKPolicy::getFK()
{
    return this->fk;
};
DocumentFK DocumentFKPolicy::getFKOld()
{
    return this->fkOld;
};

void DocumentFKPolicy::setFactureData(DocumentFK FK)
{

    fk.setSymbol(FK.getSymbol());
    fk.setMethodOfPayment(FK.getMethodOfPayment());
    fk.setDocumentPlace(FK.getDocumentPlace());
    fk.setDocumentDate(FK.getDocumentDate());
    fk.setSaleDate(FK.getSaleDate());
    fk.setPaymentDate(FK.getPaymentDate());
    fk.setTotal(FK.getTotal());
    fk.setDiscount(FK.getDiscount());
    fk.setReceiveName(FK.getReceiveName());
    fk.setOrder("");
    fk.setIssueName(FK.getIssueName());
    fk.setPaid(FK.isPaid());
    fk.setStoreResult(FK.getStoreResult());
    fk.setDocumentPositions(FK.getDocumentPositions());
}

void DocumentFKPolicy::setContractor(Contractor c)
{
    this->fk.setContractor(c);
}

Contractor DocumentFKPolicy::getContractor(){
return this->fk.getContractor();
}

void DocumentFKPolicy::setInvoice(Invoice fv)
{
    this->fk.setInvoice(fv);
}

Invoice DocumentFKPolicy::getInvoice()
{
    return this->fk.getInvoice();
};
