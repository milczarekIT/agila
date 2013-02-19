#include "Unit.h"

Unit::Unit()
{

}

Unit::Unit(QString name, int zeroPlaces)
{
    this->id = 0;
    this->name = name;
    this->zeroPlaces = zeroPlaces;   
}

Unit::Unit(int id,QString name, int zeroPlaces)
{
    this->id = id;
    this->name = name;
    this->zeroPlaces = zeroPlaces;
}

void Unit::setZeroPlaces(int zeroPlaces)
{
    this->zeroPlaces = zeroPlaces;
}

int Unit::getZeroPlaces()
{
    return zeroPlaces;
}

QString Unit::toString()
{
    return QString("--Jednostka miary - id: ") + QVariant(this->id).toString() + QString(", Nazwa j.m.: ")  + this->name
            + QString(", Miejsca po przecinku: ") + QVariant(this->zeroPlaces).toString();
}
