#include "Order.h"

Order::Order()
{
}

void Order::setRealizationDate(QDate realizationDate) {
    this->realizationDate = realizationDate;
}

void Order::setDiscount(double discount) {
    this->discount = discount;
}

void Order::setRealized(bool realized) {
    this->realized = realized;
}

QDate Order::getRealizationDate() {
    return realizationDate;
}

double Order::getDiscount() {
    return discount;
}

bool Order::isRealized() {
    return realized;
}

int Order::operator ==(Order order)
{

    if(!(this->contractor == order.getContractor()))
        return 0;
    else if(this->discount != order.getDiscount())
        return 0;
    else if (this->documentSymbol !=order.getSymbol())
        return 0;
    else if(this->documentPositions != order.getDocumentPositions())
        return 0;
    else if(this->documentPlace != order.getDocumentPlace())
        return 0;
    else if(this->documentDate != order.getDocumentDate())
        return 0;
    else if(this->issueName != order.getIssueName())
        return 0;
    else if(this->receiveName != order.getReceiveName())
        return 0;
    else if (this->realizationDate !=order.getRealizationDate())
        return 0;
    else if(!(this->total-order.getTotal()<=0.0001 && this->total - order.getTotal() >= -0.0001))
       return 0;
    else if(this->realized !=order.isRealized())
        return 0;
    else
        return 1;
}
