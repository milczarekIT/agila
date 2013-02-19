#include "DocumentPZ.h"

DocumentPZ::DocumentPZ()    {
}

QDate DocumentPZ::getStoreDate()   {
    return this->storeDate;
}
SimpleStructure DocumentPZ::getTransport()  {
    return this->transport;
}

void DocumentPZ::setStoreDate(QDate storeDate)   {
    this->storeDate = storeDate;
}
void DocumentPZ::setTransport(SimpleStructure transport)    {
    this->transport = transport;
}

DocumentPZ::~DocumentPZ()   {

}
int DocumentPZ::operator ==(DocumentPZ in)
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
    else if(this->transport.getId() != in.getTransport().getId())
        return 0;
    else if(this->storeDate != in.getStoreDate())
        return 0;
    else
        return 1;
}
