#include "InvoicePolicy.h"

InvoicePolicy::InvoicePolicy()
{
}

InvoicePolicy::~InvoicePolicy()
{
}

Invoice InvoicePolicy::getInvoice()
{
return this->invoice;
}

Invoice InvoicePolicy::getOldInvoice()
{
return this->oldInvoice;
}

void InvoicePolicy::setOldInvoice(Invoice invoiceOld)
{
this->oldInvoice=invoiceOld;
}

void InvoicePolicy::setInvoice(Invoice invoice)
{
this->invoice=invoice;
}

void InvoicePolicy::setDocumentData(Invoice doc)
{
    invoice.setDocumentType(doc.getDocumentType());
    invoice.setSymbol(doc.getSymbol());
    invoice.setMethodOfPayment(doc.getMethodOfPayment());
    invoice.setDocumentPlace(doc.getDocumentPlace());
    invoice.setDocumentDate(doc.getDocumentDate());
    invoice.setSaleDate(doc.getSaleDate());
    invoice.setPaymentDate(doc.getPaymentDate());
    invoice.setTotal(doc.getTotal());
    invoice.setDiscount(doc.getDiscount());
    invoice.setOrder(doc.getOrder());
    invoice.setIssueName(doc.getIssueName());
    invoice.setReceiveName(doc.getReceiveName());
    invoice.setPaid(doc.isPaid());
    invoice.setStoreResult(doc.getStoreResult());
    invoice.setDocumentPositions(doc.getDocumentPositions());

}

void InvoicePolicy::setContractor(Contractor c)
{
    invoice.setContractor(c);
}

Contractor InvoicePolicy::getContractor()
{
    return this->invoice.getContractor();
}
