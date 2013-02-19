#include "PurchaseInvoice.h"

PurchaseInvoice::PurchaseInvoice()
{
    purchaseDocument = "";
}

void PurchaseInvoice::setPurchaseDocument(QString purchaseDocument) {
    this->purchaseDocument = purchaseDocument;
}

QString PurchaseInvoice::getPurchaseDocument() {
    return purchaseDocument;
}

int PurchaseInvoice::operator ==(PurchaseInvoice in)
{
    if(this->methodOfPayment.getId() != in.getMethodOfPayment().getId())
        return 0;
   else if(!(this->contractor == in.getContractor()))
        return 0;
    else if(this->saleDate != in.getSaleDate())
        return 0;
    else if(this->paymentDate != in.getPaymentDate())
        return 0;
    else if(this->paid!= in.isPaid())
        return 0;
    else if(this->discount != in.getDiscount())
        return 0;
    else if(this->orderSymbol != in.getOrder())
        return 0;
    else if (this->documentSymbol !=in.getSymbol())
        return 0;
    else if(this->documentPositions != in.getDocumentPositions())
        return 0;
    else if(this->documentPlace != in.getDocumentPlace())
        return 0;
    else if(this->documentDate != in.getDocumentDate())
        return 0;
    else if(this->issueName != in.getIssueName())
        return 0;
    else if(this->receiveName != in.getReceiveName())
        return 0;
    else if(this->storeResult != in.getStoreResult())
        return 0;
     else if(!(this->total-in.getTotal()<=0.0001 && this->total - in.getTotal() >= -0.0001))
        return 0;
    else if(this->purchaseDocument != in.getPurchaseDocument())
        return 0;
    else
        return 1;
}
