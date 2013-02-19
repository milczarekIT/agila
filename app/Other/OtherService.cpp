#include "OtherService.h"

OtherService::OtherService()
{
    model = new OtherModel();
}

OtherService::~OtherService()
{
    delete model;
}

QString OtherService::getCityByPostalCode(QString postalCode)
{
    QString city = "";
    try {
        city = model->getCityByPostalCode(postalCode);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return city;
}
