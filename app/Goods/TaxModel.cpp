#include "TaxModel.h"

TaxModel::TaxModel()
{
}

TaxModel::~TaxModel()
{
}

QVector<Tax> TaxModel::getTaxes(bool onlyActiveInApp = false)
{
    QVector<Tax> taxes;
    QString queryString = "SELECT id_tax, name, value, short_name, active_in_app FROM taxes WHERE is_active = true";
    if(onlyActiveInApp)
        queryString.append(" AND active_in_app = true");
    queryString.append(" ORDER BY value DESC");

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare(queryString);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("TaxModel::getTaxes", query);

    Tax tax;
    while(query->next())
    {
        tax.setId(query->value(0).toInt());
        tax.setName(query->value(1).toString());
        tax.setValue(query->value(2).toFloat());
        tax.setShortName(query->value(3).toString());
        tax.setActiveInApp(query->value(4).toBool());
        taxes.push_back(tax);
    }

    delete query;

    return taxes;
}

Tax TaxModel::getTax(int id)
{
    Tax tax;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT name, value, short_name, active_in_app FROM taxes WHERE id_tax = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("TaxModel::getTax", query);
    else if(query->size() > 0)
    {
        query->first();

        tax.setId(id);
        tax.setName(query->value(0).toString());
        tax.setValue(query->value(1).toFloat());
        tax.setShortName(query->value(2).toString());
        tax.setActiveInApp(query->value(3).toBool());
    }
    delete query;

    return tax;
}

void TaxModel::addTax(Tax t)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO taxes (name, value, short_name, active_in_app) "
                    "VALUES (?, ?, ?, ?)");

    query->addBindValue(t.getName());
    query->addBindValue(t.getValue());
    query->addBindValue(t.getShortName());
    query->addBindValue(t.isActiveInApp());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("TaxModel::addTax", query);

    delete query;
}

void TaxModel::editTax(Tax t)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE taxes SET name = ?, short_name = ?, active_in_app = ? WHERE taxes.id_tax = ?");

    query->addBindValue(t.getName());
    query->addBindValue(t.getShortName());
    query->addBindValue(t.isActiveInApp());
    query->addBindValue(t.getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("TaxModel::editTax", query);

    delete query;
}

void TaxModel::removeTax(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE taxes SET is_active = false, active_in_app = false WHERE taxes.id_tax = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("TaxModel::removeTax", query);

    delete query;
}
