#include "DocumentZALPolicy.h"

DocumentZALPolicy::DocumentZALPolicy()
{
}

DocumentZALPolicy::~DocumentZALPolicy()
{
}

DocumentZAL DocumentZALPolicy::getDocumentZAL()
{
return this->documentZAL;
}

DocumentZAL DocumentZALPolicy::getOldDocumentZAL()
{
return this->oldDocumentZAL;
}

void DocumentZALPolicy::setOldDocumentZAL(DocumentZAL documentZALOld)
{
this->oldDocumentZAL=documentZALOld;
}

void DocumentZALPolicy::setDocumentZAL(DocumentZAL documentZAL)
{
this->documentZAL=documentZAL;
}

void DocumentZALPolicy::setDocumentData(DocumentZAL doc)
{
    documentZAL.setDocumentType(doc.getDocumentType());
    documentZAL.setSymbol(doc.getSymbol());
    documentZAL.setMethodOfPayment(doc.getMethodOfPayment());
    documentZAL.setDocumentPlace(doc.getDocumentPlace());
    documentZAL.setDocumentDate(doc.getDocumentDate());
    documentZAL.setSaleDate(doc.getSaleDate());
    documentZAL.setPaymentDate(doc.getPaymentDate());
    documentZAL.setTotal(doc.getTotal());
    documentZAL.setPaidValue(doc.getPaidValue());
    documentZAL.setDiscount(doc.getDiscount());
    documentZAL.setOrder(doc.getOrder());
    documentZAL.setIssueName(doc.getIssueName());
    documentZAL.setReceiveName(doc.getReceiveName());
    documentZAL.setPaid(doc.isPaid());
    documentZAL.setStoreResult(doc.getStoreResult());
    documentZAL.setDocumentPositions(doc.getDocumentPositions());
}

void DocumentZALPolicy::setContractor(Contractor c)
{
    documentZAL.setContractor(c);
}

Contractor DocumentZALPolicy::getContractor()
{
    return this->documentZAL.getContractor();
}

void DocumentZALPolicy::setPreviousZAL(QVector <SimpleDocumentInfo> previous)
{
    this->documentZAL.setPreviousDocumentsZAL(previous);
}
QVector<SimpleDocumentInfo> DocumentZALPolicy::getPreviousZAL()
{
    return this->documentZAL.getPreviousDocumentsZAL();
}
void DocumentZALPolicy::appendToPrevious(SimpleDocumentInfo simple)
{
    this->previous.append(simple);
}
void DocumentZALPolicy::setPreviousZALVector(QVector <SimpleDocumentInfo> previous)
{
    this->previous = previous;
}
QVector<SimpleDocumentInfo> DocumentZALPolicy::getPreviousZALVector()
{
    return this->previous;
}
void DocumentZALPolicy::removeFromVector(int id)
{
    this->previous.remove(id);
}
