#include "PurchasePolicy.h"

PurchasePolicy::PurchasePolicy()
{
}

PurchasePolicy::~PurchasePolicy()
{

}

void PurchasePolicy::setPurchaseInvoiceData(PurchaseInvoice doc)
{
    purchaseInvoice.setDocumentType(doc.getDocumentType());//ustawiam rodzaj dokumentu PRO FMP documentRR PI
    purchaseInvoice.setSymbol(doc.getSymbol());
    purchaseInvoice.setContractor(this->getContractor());
    purchaseInvoice.setMethodOfPayment(doc.getMethodOfPayment());
    purchaseInvoice.setDocumentPlace(doc.getDocumentPlace());
    purchaseInvoice.setDocumentDate(doc.getDocumentDate());
    purchaseInvoice.setSaleDate(doc.getSaleDate());
    purchaseInvoice.setPaymentDate(doc.getPaymentDate());
    purchaseInvoice.setTotal(doc.getTotal());
    purchaseInvoice.setDiscount(doc.getDiscount());
    purchaseInvoice.setIssueName(doc.getIssueName());
    purchaseInvoice.setReceiveName(doc.getReceiveName());
    purchaseInvoice.setOrder(doc.getOrder());

    if(doc.getSymbol().contains("RR"))
         purchaseInvoice.setPurchaseDocument();
    else
         purchaseInvoice.setPurchaseDocument(doc.getPurchaseDocument());

    purchaseInvoice.setPaid(doc.isPaid());
    purchaseInvoice.setStoreResult(doc.getStoreResult());
    purchaseInvoice.setDocumentPositions(doc.getDocumentPositions());
}

PurchaseInvoice PurchasePolicy::getPurchaseInvoiceOld(){
return this->purchaseInvoiceOld;
}

PurchaseInvoice PurchasePolicy::getPurchaseInvoice(){
return this->purchaseInvoice;
}

void PurchasePolicy::setPurchaseInvoiceOld(PurchaseInvoice purchaseInvoiceOld)
{
this->purchaseInvoiceOld= purchaseInvoiceOld;
}

void PurchasePolicy::setPurchaseInvoice(PurchaseInvoice purchaseInvoice)
{
this->purchaseInvoice=purchaseInvoice;
}

void PurchasePolicy::setContractor(Contractor c)
{
    this->purchaseInvoice.setContractor(c);
}
Contractor PurchasePolicy::getContractor()
{
    return this->purchaseInvoice.getContractor();
};
