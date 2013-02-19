#include "PurchaseInvoiceManager.h"

PurchaseInvoiceManager::PurchaseInvoiceManager()
{

}

PurchaseInvoiceManager::~PurchaseInvoiceManager(){}


void PurchaseInvoiceManager::setPurchaseInvoiceData(PurchaseInvoice doc)
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
    purchaseInvoice.setPurchaseDocument(doc.getPurchaseDocument());
    purchaseInvoice.setPaid(doc.isPaid());
    purchaseInvoice.setStoreResult(doc.getStoreResult());
    purchaseInvoice.setDocumentPositions(this->getDocumentPosition());
}

PurchaseInvoice PurchaseInvoiceManager::getPurchaseInvoiceOld(){
return this->purchaseInvoiceOld;
}

PurchaseInvoice PurchaseInvoiceManager::getPurchaseInvoice(){
return this->purchaseInvoice;
}

void PurchaseInvoiceManager::setPurchaseInvoiceOld(PurchaseInvoice purchaseInvoiceOld)
{
this->purchaseInvoiceOld= purchaseInvoiceOld;
}

void PurchaseInvoiceManager::setPurchaseInvoice(PurchaseInvoice purchaseInvoice)
{
this->purchaseInvoice=purchaseInvoice;
}

void PurchaseInvoiceManager::setContractor(Contractor c)
{
    this->purchaseInvoice.setContractor(c);
}
Contractor PurchaseInvoiceManager::getContractor()
{
    return this->purchaseInvoice.getContractor();
};
