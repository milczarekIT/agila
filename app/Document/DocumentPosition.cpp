#include "DocumentPosition.h"
DocumentPosition::DocumentPosition()
{
}
void DocumentPosition::setGood(Goods good) { this->good = good; }
void DocumentPosition::setQuantity(double quantity) { this->quantity = quantity; }
void DocumentPosition::setPriceNet(double priceNet) { this->priceNet = priceNet; }
void DocumentPosition::setTax(Tax tax) { this->tax = tax; }
void DocumentPosition::setPriceGross(double priceGross){this->priceGross=priceGross;}
void DocumentPosition::setPriceLevel(int priceLevel) { this->priceLevel = priceLevel; }

Goods DocumentPosition::getGood() { return good; }
double DocumentPosition::getQuantity() { return quantity;;}
double DocumentPosition::getPriceNet() { return priceNet; }
Tax DocumentPosition::getTax() { return tax; }
double DocumentPosition::getPriceGross(){return priceGross;}
int DocumentPosition::getPriceLevel() { return priceLevel; }

QString DocumentPosition::toString()
{
    return "\t | \t" + QString::number(this->good.getId())
                               + "\t | \t" + QString::number(this->quantity)
                               + "\t | \t" + QString::number(this->priceNet)
                               + "\t | \t" + QString::number(this->tax.getId());
}

int DocumentPosition::operator==(DocumentPosition dp)
{
    if(this->good.getId() != dp.getGood().getId())
        return 0;
    else if(this->quantity != dp.getQuantity())
        return 0;
    else if(this->priceNet != dp.getPriceNet())
        return 0;
    else if(this->tax.getId() != dp.getTax().getId())
        return 0;
    else
        return 1;
}

QString DocumentPosition::getQuantityInString() {
    QString quantityInString;
    int decimalPlaces = good.getUnit().getZeroPlaces();
    quantityInString = QString::number(quantity, 'f', decimalPlaces);
    return quantityInString;
}
