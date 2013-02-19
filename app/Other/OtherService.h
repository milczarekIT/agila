#ifndef OTHERSERVICE_H
#define OTHERSERVICE_H

#include "Service.h"
#include "OtherModel.h"

class OtherService : public Service
{
    OtherModel *model;
public:
    OtherService();
    ~OtherService();

    QString getCityByPostalCode(QString postalCode);
};

#endif // OTHERSERVICE_H
