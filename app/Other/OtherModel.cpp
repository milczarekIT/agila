#include "OtherModel.h"

OtherModel::OtherModel()
{
}

QString OtherModel::getCityByPostalCode(QString postalCode)
{
    QString city = "";
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT city FROM postal_codes WHERE code = ?");
    query->addBindValue(postalCode);
    query->exec();

    if(this->isQueryError(query))
       throw new SQLException("OtherModel::getCityByPostalCode", query);
    else if(query->size() > 0)
    {
        query->first();
        city = query->value(0).toString();
    }

    return city;
}
