#include "StoragePolicy.h"

StoragePolicy::StoragePolicy()
{
}
StoragePolicy::~StoragePolicy(){}


StoreDocument StoragePolicy::getStoreDocument()
{
return this->storeDocument;
}

StoreDocument StoragePolicy::getOldStoreDocument()
{
return this->storeDocumentOld;
}

void StoragePolicy::setOldStoreDocument(StoreDocument storeDocumentOld)
{
this->storeDocumentOld=storeDocumentOld;
}

void StoragePolicy::setStoreDocument(StoreDocument storeDocument)
{
this->storeDocument=storeDocument;
}

void StoragePolicy::setDocumentData(StoreDocument doc)
{

    storeDocument.setDocumentType(doc.getDocumentType());
    storeDocument.setSymbol(doc.getSymbol());
    storeDocument.setDocumentDate(doc.getDocumentDate());
    storeDocument.setDocumentPlace(doc.getDocumentPlace());
    storeDocument.setDepartment(doc.getDepartment());
    storeDocument.setIssueName(doc.getIssueName());
    storeDocument.setReceiveName(doc.getReceiveName());
    storeDocument.setStoreResult(doc.getStoreResult());
    storeDocument.setTotal(doc.getTotal());
    storeDocument.setDocumentPositions(doc.getDocumentPositions());

}

void StoragePolicy::setContractor(Contractor c)
{
    storeDocument.setContractor(c);
}

Contractor StoragePolicy::getContractor()
{
    return this->storeDocument.getContractor();
}
