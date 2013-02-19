#include "DocumentFK.h"

DocumentFK::DocumentFK()
{
    this->documentDate = QDate::currentDate();
    this->documentType = "FK";
}

DocumentFK::DocumentFK(Invoice fv)
{
    this->fv = fv;
    this->copyInvoiceData();
}

void DocumentFK::setInvoice(Invoice fv)
{
    this->fv = fv;
}

Invoice DocumentFK::getInvoice()
{
    return fv;
}

void DocumentFK::copyInvoiceData()
{
    this->contractor = fv.getContractor();
    this->discount = fv.getDiscount();
    this->saleDate = fv.getSaleDate();
    this->paymentDate = fv.getPaymentDate();
    this->documentPlace = fv.getDocumentPlace();
    this->documentPositions = fv.getDocumentPositions();
    this->methodOfPayment = fv.getMethodOfPayment();
    this->total = fv.getTotal();
    this->issueName = fv.getIssueName();
    this->receiveName = fv.getReceiveName();
    this->paid = fv.isPaid();
}

int DocumentFK::operator==(DocumentFK doc)
{
    if(!(this->fv == doc.getInvoice()))
        return 0;
    else if(this->methodOfPayment.getId() != doc.getMethodOfPayment().getId())
        return 0;
     else if(!(this->contractor == doc.getContractor()))
        return 0;
    else if(this->saleDate != doc.getSaleDate())
        return 0;
    else if(this->paymentDate != doc.getPaymentDate())
        return 0;
    else if(this->paid!= doc.isPaid())
        return 0;
    else if(this->discount != doc.getDiscount())
        return 0;
    else if (this->documentSymbol !=doc.getSymbol())
        return 0;
    else if(this->documentPositions != doc.getDocumentPositions())
        return 0;
    else if(this->documentPlace != doc.getDocumentPlace())
        return 0;
    else if(this->documentDate != doc.getDocumentDate())
        return 0;
    else if(this->issueName != doc.getIssueName())
        return 0;
    else if(this->receiveName != doc.getReceiveName())
        return 0;
    else if(this->storeResult != doc.getStoreResult())
        return 0;
    else if(!(this->total-doc.getTotal()<=0.0001 && this->total - doc.getTotal() >= -0.0001))
        return 0;
    else
        return 1;
}
