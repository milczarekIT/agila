#ifndef UNIT_H
#define UNIT_H

#include <QString>
#include <QVariant>
#include "Other/SimpleStructure.h"

class Unit : public SimpleStructure
{
private:
    int zeroPlaces;
public:
    Unit();
    Unit(QString name, int zeroPlaces);
    Unit(int id,QString name, int zeroPlaces);

    void setZeroPlaces(int zeroPlaces);

    int getZeroPlaces();

    QString toString();
};

#endif // UNIT_H
