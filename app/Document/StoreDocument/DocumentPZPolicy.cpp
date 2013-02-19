#include "DocumentPZPolicy.h"

DocumentPZPolicy::DocumentPZPolicy()
{
}
DocumentPZPolicy::~DocumentPZPolicy(){}


DocumentPZ DocumentPZPolicy::getDocumentPZ()
{
return this->documentPZ;
}

DocumentPZ DocumentPZPolicy::getOldDocumentPZ()
{
return this->documentPZOld;
}

void DocumentPZPolicy::setOldDocumentPZ(DocumentPZ documentPZOld)
{
this->documentPZOld=documentPZOld;
}

void DocumentPZPolicy::setDocumentPZ(DocumentPZ documentPZ)
{
this->documentPZ=documentPZ;
}

void DocumentPZPolicy::setDocumentData(DocumentPZ doc)
{

    documentPZ.setDocumentType(doc.getDocumentType());
    documentPZ.setSymbol(doc.getSymbol());
    documentPZ.setDocumentDate(doc.getDocumentDate());
    documentPZ.setDocumentPlace(doc.getDocumentPlace());
    documentPZ.setStoreDate(doc.getStoreDate());
    documentPZ.setTransport(doc.getTransport());
    documentPZ.setIssueName(doc.getIssueName());
    documentPZ.setReceiveName(doc.getReceiveName());
    documentPZ.setStoreResult(doc.getStoreResult());
    documentPZ.setTotal(doc.getTotal());
    documentPZ.setDocumentPositions(doc.getDocumentPositions());
}

void DocumentPZPolicy::setContractor(Contractor c)
{
    documentPZ.setContractor(c);
}

Contractor DocumentPZPolicy::getContractor()
{
    return this->documentPZ.getContractor();
}
