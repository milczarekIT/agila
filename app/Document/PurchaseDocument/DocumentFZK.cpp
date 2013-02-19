#include "DocumentFZK.h"

DocumentFZK::DocumentFZK()
{
    this->documentDate = QDate::currentDate();
    this->documentType = "FZK";
}


DocumentFZK::DocumentFZK(PurchaseInvoice invoice)
{
    this->invoice = invoice;
    this->copyInvoiceData();
}

void DocumentFZK::setInvoice(PurchaseInvoice invoice)
{
    this->invoice = invoice;
}

PurchaseInvoice DocumentFZK::getInvoice()
{
    return invoice;
}

void DocumentFZK::setPurchaseInvoiceCorrection(QString purchaseInvoiceCorrection) {
    this->purchaseInvoiceCorrection = purchaseInvoiceCorrection;
}

QString DocumentFZK::getPurchaseInvoiceCorrection() {
    return purchaseInvoiceCorrection;
}

void DocumentFZK::copyInvoiceData()
{
    this->contractor = invoice.getContractor();
    this->discount = invoice.getDiscount();
    this->saleDate = invoice.getSaleDate();
    this->paymentDate = invoice.getPaymentDate();
    this->documentPlace = invoice.getDocumentPlace();
    this->documentPositions = invoice.getDocumentPositions();
    this->methodOfPayment = invoice.getMethodOfPayment();
    this->total = invoice.getTotal();
    this->issueName = invoice.getIssueName();
    this->receiveName = invoice.getReceiveName();
    this->paid = invoice.isPaid();
}

int DocumentFZK::operator==(DocumentFZK doc)
{
    if(!(this->invoice == doc.getInvoice()))
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
    else if(this->orderSymbol != doc.getOrder())
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
    else if (this->purchaseDocument != doc.getPurchaseDocument())
        return 0;
    else
        return 1;
}

