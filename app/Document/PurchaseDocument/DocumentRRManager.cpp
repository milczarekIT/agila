#include "DocumentRRManager.h"

DocumentRRManager::DocumentRRManager()
{

}

DocumentRRManager::~DocumentRRManager(){}

void DocumentRRManager::setDocumentRRData(PurchaseInvoice doc)
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
    purchaseInvoice.setPurchaseDocument();
    purchaseInvoice.setPaid(doc.isPaid());
    purchaseInvoice.setStoreResult(doc.getStoreResult());
    purchaseInvoice.setDocumentPositions(this->getDocumentPosition());

}
