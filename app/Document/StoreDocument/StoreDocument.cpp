#include "StoreDocument.h"

StoreDocument::StoreDocument()
{
}

StoreDocument::~StoreDocument(){};

SimpleStructure StoreDocument::getDepartment()
{
    return this->department;
}

void StoreDocument::setDepartment(SimpleStructure department)
{
    this->department = department;
}
int StoreDocument::operator ==(StoreDocument in)
{
     if(!(this->contractor == in.getContractor()))
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
     else if(this->department.getId() != in.getDepartment().getId())
        return 0;
    else
        return 1;
}
