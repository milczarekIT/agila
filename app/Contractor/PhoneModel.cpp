#include "PhoneModel.h"

PhoneModel::PhoneModel()
{
}

PhoneModel::~PhoneModel()
{
}

QVector<Phone> PhoneModel::getPhones(int contractorId)
{
    QVector<Phone> cPhones;

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id_contractors_phone, phone_name, number, is_default "
                   "FROM contractors_phones WHERE contractors_phones.contractor = :contractorId");
    query->bindValue(":contractorId", contractorId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("PhoneModel::getPhones", query);

    while(query->next())
    {
        int id = query->value(0).toInt();
        QString name = query->value(1).toString();
        QString number = query->value(2).toString();
        bool defaultPhone = query->value(3).toBool();
        Phone p(id, name, number, defaultPhone);
        cPhones.push_back(p);
    }

    delete query;

    return cPhones;
}

void PhoneModel::addPhone(int contractorId, Phone phone)
{
    if(phone.getName().isEmpty())
        phone.setName(".");
    if(phone.getNumber().isEmpty())
        phone.setNumber(".");

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO contractors_phones (contractor, phone_name, number, is_default) "
                   "VALUES (?, ?, ?, ?)");
    query->addBindValue(contractorId);
    query->addBindValue(phone.getName());
    query->addBindValue(phone.getNumber());
    query->addBindValue(QVariant(phone.isDefault()).toInt());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("PhoneModel::addPhone", query);

    delete query;
}

void PhoneModel::editPhone(int contractorId, Phone newPhone)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE contractors_phones SET phone_name = ?, number = ?, is_default = ? "
                   "WHERE contractors_phones.id_contractors_phone = ? and contractor = ?");
    query->addBindValue(newPhone.getName());
    query->addBindValue(newPhone.getNumber());
    query->addBindValue(QVariant(newPhone.isDefault()).toInt());
    query->addBindValue(newPhone.getId());
    query->addBindValue(contractorId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("PhoneModel::editPhone", query);

    delete query;
}

void PhoneModel::removePhone(int idPhone)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM contractors_phones WHERE id_contractors_phone = ?");
    query->addBindValue(idPhone);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("PhoneModel::removePhone", query);

    delete query;
}

void PhoneModel::removeAllPhones(int contractor) {
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM contractors_phones WHERE contractor = ?");
    query->addBindValue(contractor);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("PhoneModel::removeAllPhones", query);

    delete query;
}
