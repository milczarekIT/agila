#ifndef OTHERMODEL_H
#define OTHERMODEL_H

#include <QString>
#include "Database/Model.h"

class OtherModel : public Model
{
public:
    OtherModel();

    /**
      * Zwraca Miasto o podanym kodzie pocztowym
      */
    QString getCityByPostalCode(QString postalCode);
};

#endif // OTHERMODEL_H
