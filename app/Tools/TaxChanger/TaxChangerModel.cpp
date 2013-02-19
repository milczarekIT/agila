#include "TaxChangerModel.h"

TaxChangerModel::TaxChangerModel()
{
}

void TaxChangerModel::changeTaxesForAll(Tax oldTax, Tax newTax, int basePrice, int priceType)
{
    QString query = "UPDATE goods SET tax = ?, ";

    QSqlQuery qm(Database::getInstance().db);
    qm.addBindValue(newTax.getId());

    if(basePrice == Price::NET)
    {
        if(priceType == Price::ABC)
        {
            query.append("price_a_gross =  price_a_net *((100.0 + ?)/100.0), "
                         "price_b_gross = price_b_net * ((100.0 + ? ) / 100.0), "
                         "price_c_gross = price_c_net * ((100.0 + ? ) / 100.0) ");
            qm.addBindValue(newTax.getValue());
            qm.addBindValue(newTax.getValue());
            qm.addBindValue(newTax.getValue());
        }
        if(priceType == (Price::ABC + Price::MAG))
        {
            query.append(", ");
        }
        if(priceType == Price::MAG)
        {
            query.append("price_mag_gross = price_mag_net * ((100.0 + ?) / 100.0) ");
            qm.addBindValue(newTax.getValue());
        }
        query.append("WHERE tax = ?");
        qm.addBindValue(oldTax.getId());
    }
    else if(basePrice == Price::GROSS)
    {
        if(priceType == Price::ABC)
        {
            query.append("price_a_net =  price_a_gross *(100.0/(100.0 + ?)), "
                             "price_b_net = price_b_gross * (100.0/(100.0 + ?)), "
                             "price_c_net = price_c_gross * (100.0/(100.0 + ?)) ");
            qm.addBindValue(newTax.getValue());
            qm.addBindValue(newTax.getValue());
            qm.addBindValue(newTax.getValue());
        }
        if(priceType == (Price::ABC + Price::MAG))
        {
            query.append(", ");
        }
        if(priceType == Price::MAG)
        {
            query.append("price_mag_net = price_mag_gross * (100.0/(100.0 + ?)) ");
            qm.addBindValue(newTax.getValue());
        }
        query.append("WHERE tax = ?");
        qm.addBindValue(oldTax.getId());
    }
    qm.prepare(query);
    qm.exec();
}

void TaxChangerModel::changeTaxesForGroup(int goodGroup, Tax newTax, int basePrice, int priceType)
{
    QString query = "UPDATE goods SET tax = ?, ";

    QSqlQuery qm(Database::getInstance().db);
    qm.addBindValue(newTax.getId());

    if(basePrice == Price::NET)
    {
        if(priceType == Price::ABC)
        {
            query.append("price_a_gross =  price_a_net *((100.0 + ?)/100.0), "
                         "price_b_gross = price_b_net * ((100.0 + ? ) / 100.0), "
                         "price_c_gross = price_c_net * ((100.0 + ? ) / 100.0) ");
            qm.addBindValue(newTax.getValue());
            qm.addBindValue(newTax.getValue());
            qm.addBindValue(newTax.getValue());
        }
        if(priceType == (Price::ABC + Price::MAG))
        {
            query.append(", ");
        }
        if(priceType == Price::MAG)
        {
            query.append("price_mag_gross = price_mag_net * ((100.0 + ?) / 100.0) ");
            qm.addBindValue(newTax.getValue());
        }
        query.append("WHERE goods_group = ?");
        qm.addBindValue(goodGroup);
    }
    else if(basePrice == Price::GROSS)
    {
        if(priceType == Price::ABC)
        {
            query.append("price_a_net =  price_a_gross *(100.0/(100.0 + ?)), "
                              "price_b_net = price_b_gross * (100.0/(100.0 + ?)), "
                              "price_c_net = price_c_gross * (100.0/(100.0 + ?)) ");
            qm.addBindValue(newTax.getValue());
            qm.addBindValue(newTax.getValue());
            qm.addBindValue(newTax.getValue());
        }
        if(priceType == (Price::ABC + Price::MAG))
        {
            query.append(", ");
        }
        if(priceType == Price::MAG)
        {
            query.append("price_mag_net = price_mag_gross * (100.0/(100.0 + ?)) ");
            qm.addBindValue(newTax.getValue());
        }
        query.append("WHERE goods_group = ?");
        qm.addBindValue(goodGroup);
    }
    qm.prepare(query);
    qm.exec();
}
