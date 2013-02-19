#include "DocumentWZ.h"

DocumentWZ::DocumentWZ()    {
}

QString DocumentWZ::getFactureSymbol()  {
    return this->factureSymbol;
}

QDate DocumentWZ::getSendDate()   {
    return this->sendDate;
}
SimpleStructure DocumentWZ::getTransport()  {
    return this->transport;
}

QString DocumentWZ::getWaybillNumber() {
    return this->waybillNumber;
}

int DocumentWZ::getShipping() {
    return this->shipping;
}

void DocumentWZ::setFactureSymbol(QString symbol)   {
    this->factureSymbol = symbol;
}

void DocumentWZ::setSendDate(QDate storeDate)   {
    this->sendDate = storeDate;
}
void DocumentWZ::setTransport(SimpleStructure transport)    {
    this->transport = transport;
}
void DocumentWZ::setWaybillNumber(QString waybillNumber) {
    this->waybillNumber = waybillNumber;
}
void DocumentWZ::setShipping(int shipping) {
    this->shipping = shipping;
}

int DocumentWZ::operator ==(DocumentWZ in)
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
    else if(this->sendDate != in.getSendDate())
        return 0;
    else if(this->waybillNumber != in.getWaybillNumber())
        return 0;
    else if(this->shipping != in.getShipping())
        return 0;
    else if(this->factureSymbol != in.getFactureSymbol())
        return 0;
    else
        return 1;
}
