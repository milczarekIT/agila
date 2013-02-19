#include "DocumentWZPolicy.h"

DocumentWZPolicy::DocumentWZPolicy()
{
}

DocumentWZPolicy::~DocumentWZPolicy(){}


DocumentWZ DocumentWZPolicy::getDocumentWZ()
{
return this->documentWZ;
}

DocumentWZ DocumentWZPolicy::getOldDocumentWZ()
{
return this->documentWZOld;
}

void DocumentWZPolicy::setOldDocumentWZ(DocumentWZ documentWZOld)
{
this->documentWZOld=documentWZOld;
}

void DocumentWZPolicy::setDocumentWZ(DocumentWZ documentWZ)
{
this->documentWZ=documentWZ;
}

void DocumentWZPolicy::setDocumentData(DocumentWZ doc)
{

    documentWZ.setDocumentType(doc.getDocumentType());
    documentWZ.setSymbol(doc.getSymbol());
    documentWZ.setDocumentDate(doc.getDocumentDate());
    documentWZ.setDocumentPlace(doc.getDocumentPlace());
    documentWZ.setFactureSymbol(doc.getFactureSymbol());
    documentWZ.setWaybillNumber(doc.getWaybillNumber());
    documentWZ.setShipping(doc.getShipping());
    documentWZ.setSendDate(doc.getSendDate());
    documentWZ.setTransport(doc.getTransport());
    documentWZ.setIssueName(doc.getIssueName());
    documentWZ.setReceiveName(doc.getReceiveName());
    documentWZ.setStoreResult(doc.getStoreResult());
    documentWZ.setTotal(doc.getTotal());
    documentWZ.setDocumentPositions(doc.getDocumentPositions());

}

void DocumentWZPolicy::setContractor(Contractor c)
{
    documentWZ.setContractor(c);
}

Contractor DocumentWZPolicy::getContractor()
{
    return this->documentWZ.getContractor();
}
