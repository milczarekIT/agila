#include "DocumentFZKPolicy.h"

DocumentFZKPolicy::DocumentFZKPolicy()
{
}

DocumentFZKPolicy::~DocumentFZKPolicy()
{
}

void DocumentFZKPolicy::setFZK(DocumentFZK fzk)
{
    this->fzk=fzk;
};
void DocumentFZKPolicy::setFZKOld(DocumentFZK fzkOld)
{
    this->fzkOld=fzkOld;
};
DocumentFZK DocumentFZKPolicy::getFZK()
{
    return this->fzk;
};
DocumentFZK DocumentFZKPolicy::getFZKOld()
{
    return this->fzkOld;
};

void DocumentFZKPolicy::setFactureData(DocumentFZK FZK)
{

    fzk.setSymbol(FZK.getSymbol());
    fzk.setMethodOfPayment(FZK.getMethodOfPayment());
    fzk.setPurchaseDocument(FZK.getPurchaseDocument());
    fzk.setDocumentPlace(FZK.getDocumentPlace());
    fzk.setDocumentDate(FZK.getDocumentDate());
    fzk.setSaleDate(FZK.getSaleDate());
    fzk.setPaymentDate(FZK.getPaymentDate());
    fzk.setTotal(FZK.getTotal());
    fzk.setDiscount(FZK.getDiscount());
    fzk.setReceiveName(FZK.getReceiveName());
    fzk.setOrder("");
    fzk.setIssueName(FZK.getIssueName());
    fzk.setPaid(FZK.isPaid());
    fzk.setStoreResult(FZK.getStoreResult());
    fzk.setDocumentPositions(FZK.getDocumentPositions());
}

void DocumentFZKPolicy::setContractor(Contractor c)
{
    this->fzk.setContractor(c);
}

Contractor DocumentFZKPolicy::getContractor(){
return this->fzk.getContractor();
}

void DocumentFZKPolicy::setPurchaseInvoice(PurchaseInvoice fv)
{
    this->fzk.setInvoice(fv);
}

PurchaseInvoice DocumentFZKPolicy::getPurchaseInvoice()
{
    return this->fzk.getInvoice();
};
