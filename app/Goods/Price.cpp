#include "Price.h"

Price::Price()
{
}

Price::Price(double val)
{
    this->val = val;
}

Price::~Price()
{
}

double Price::value() {
    return val;
}

QString Price::toString() {
    return QString::number(val, ',', 2).replace(QRegExp("[.]"), ",");
}

void Price::operator = (Price price)
{
    this->val = price.value();
}

void Price::operator = (double value)
{
    this->val = value;
}

QString Price::priceLevelToString(int priceLevel) {
    if(priceLevel == Price::A)
        return "A";
    if(priceLevel == Price::B)
        return "B";
    if(priceLevel == Price::C)
        return "C";
    if(priceLevel == Price::MAG)
        return "MAG";
    if(priceLevel == Price::ABC)
        return "ABC";
    else
        return "";
}

int Price::priceLevelToInt(QString priceLevelString) {
    if(priceLevelString == "A")
        return Price::A;
    if(priceLevelString == "B")
        return Price::B;
    if(priceLevelString == "C")
        return Price::C;
    if(priceLevelString == "MAG")
        return Price::MAG;
    if(priceLevelString == "ABC")
        return Price::ABC;
    else
        return -1;
}
