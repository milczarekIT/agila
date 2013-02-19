#include "SettingsPreferencesModel.h"

SettingsPreferencesModel::SettingsPreferencesModel()
{
}

QVariant SettingsPreferencesModel::getValue(QString name)
{
    QVariant value;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT value FROM settings_preferences WHERE name = ?");
    query->addBindValue(name);

    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("SettingsPreferencesModel::getValue", query);
    if(query->size() > 0)
    {
        query->first();
        value = query->value(0);
    }
    delete query;

    return value;
}

void SettingsPreferencesModel::setValue(QString name, QString value)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT value FROM settings_preferences WHERE name = ?");
    query->addBindValue(name);

    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("SettingsPreferencesModel::setValue", query);
    if(query->size() == 0)
    {
        insertValue(name, value);
    }
    else if(query->size() == 1)
    {
        updateValue(name, value);
    }

    delete query;
}

void SettingsPreferencesModel::insertValue(QString name, QString value)
{
    QSqlQuery *query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO settings_preferences (name, value) VALUES (?, ?)");
    query->addBindValue(name);
    query->addBindValue(value);

    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("SettingsPreferencesModel::insertValue", query);

    delete query;
}

void SettingsPreferencesModel::updateValue(QString name, QString value)
{
    QSqlQuery *query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE settings_preferences SET value = ? WHERE name = ?");
    query->addBindValue(value);
    query->addBindValue(name);

    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("SettingsPreferencesModel::updateValue", query);

    delete query;
}

int SettingsPreferencesModel::getTaxIdForRR()
{
    return this->getValue("TAXRR_ID").toInt();
}

void SettingsPreferencesModel::setTaxIdForRR(int idTax)
{
    this->setValue("TAXRR_ID",QString::number(idTax,'.',0));
}

int SettingsPreferencesModel::getPriceConversion()
{
    return this->getValue("PRICE_CONVERSION").toInt();
}

void SettingsPreferencesModel::setPriceConversion(int type)
{
    this->setValue("PRICE_CONVERSION", QString::number(type, '.', 0));
}
int SettingsPreferencesModel::getDefaultPrintAction()
{
    return this->getValue("DEFAULT_PRINT_ACTION").toInt();
}

void SettingsPreferencesModel::setDefaultPrintAction(int action)
{
    this->setValue("DEFAULT_PRINT_ACTION", QString::number(action, '.', 0));
}

int SettingsPreferencesModel::getDefaultPrintNumberOfCopies()
{
    return this->getValue("DEFAULT_PRINT_NUMBER_OF_COPIES").toInt();
}

void SettingsPreferencesModel::setDefaultPrintNumberOfCopies(int number)
{
    this->setValue("DEFAULT_PRINT_NUMBER_OF_COPIES", QString::number(number, '.', 0));
}

double SettingsPreferencesModel::getDefaultGoodsMargin()
{
    return this->getValue("DEFAULT_GOODS_MARGIN").toDouble();
}

void SettingsPreferencesModel::setDefaultGoodsMargin(double margin)
{
    this->setValue("DEFAULT_GOODS_MARGIN", QString::number(margin, ',', 2));
}

double SettingsPreferencesModel::getDefaultGoodsDiscountB()
{
    return this->getValue("DEFAULT_GOODS_DISCOUNT_B").toDouble();
}

void SettingsPreferencesModel::setDefaultGoodsDiscountB(double discount)
{
    this->setValue("DEFAULT_GOODS_DISCOUNT_B", QString::number(discount, ',', 2));
}

double SettingsPreferencesModel::getDefaultGoodsDiscountC()
{
    return this->getValue("DEFAULT_GOODS_DISCOUNT_C").toDouble();
}

void SettingsPreferencesModel::setDefaultGoodsDiscountC(double discount)
{
    this->setValue("DEFAULT_GOODS_DISCOUNT_C", QString::number(discount, ',', 2));
}
