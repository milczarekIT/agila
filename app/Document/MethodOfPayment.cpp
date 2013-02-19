#include "MethodOfPayment.h"

MethodOfPayment::MethodOfPayment()
{

}

MethodOfPayment::MethodOfPayment(QString name, int maturity)
{
    this->id = 0;
    this->name = name;
    this->maturity = maturity;
}

MethodOfPayment::MethodOfPayment(int id,QString name, int maturity)
{
    this->id = id;
    this->name = name;
    this->maturity = maturity;
}

void MethodOfPayment::setMaturity(int maturity)
{
    this->maturity = maturity;
}

int MethodOfPayment::getMaturity()
{
    return maturity;
}

QString MethodOfPayment::toString()
{
    return QString("--METODA PŁATNOŚCI: id: ") + QVariant(this->getId()).toString() + QString(", nazwa płatności: ") + this->getName()
            + QString(", termin płatności: ") + QVariant(this->getMaturity()).toString();
}

int MethodOfPayment::operator == (MethodOfPayment mop)
{
    if(this->maturity != mop.getMaturity())
        return 0;
    else
        return 1;
}
