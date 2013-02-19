#include "OwnerModel.h"

OwnerModel::OwnerModel()
{
}

bool OwnerModel::isOwnerDefinied()
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id_owner FROM owners WHERE is_active = true");
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("OwnerModel::isOwnerDefinied", query);

    return (query->size() > 0);
}

Owner OwnerModel::getOwner(int id)
{
    Owner o;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT name, postcode, city, adress, nip, phone1, phone2, phone3, additional, account_bank_name, "
                   "account_number, website, email, logo "
                   "FROM owners "
                   "WHERE  id_owner = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("OwnerModel::getOwner", query);
    else if(query->size() > 0)
    {
        query->first();

        o.setId(id);
        o.setName(query->value(1).toString());
        o.setPostCode(query->value(2).toString());
        o.setCity(query->value(3).toString());
        o.setAdress(query->value(4).toString());
        o.setNIP(query->value(5).toString());
        o.setPhone(0, query->value(6).toString());
        o.setPhone(1, query->value(7).toString());
        o.setPhone(2, query->value(8).toString());
        o.setAdditional(query->value(9).toString());
        o.setBankName(query->value(10).toString());
        o.setBankAccount(query->value(11).toString());
        o.setWebsite(query->value(12).toString());
        o.setEMail(query->value(13).toString());
        o.setLogoPath(query->value(14).toString());
    }

    delete query;

    return o;
}

Owner OwnerModel::getActualOwner() {
    Owner o;
    query = new QSqlQuery(Database::getInstance().db);
    query->exec("SELECT id_owner, name, postcode, city, adress, nip, phone1, phone2, phone3, additional, account_bank_name, "
                "account_number, website, email, logo "
                "FROM owners "
                "WHERE is_active = true");
    if(query->size() > 0)
    {
        query->first();

        o.setId(query->value(0).toInt());
        o.setName(query->value(1).toString());
        o.setPostCode(query->value(2).toString());
        o.setCity(query->value(3).toString());
        o.setAdress(query->value(4).toString());
        o.setNIP(query->value(5).toString());
        o.setPhone(0, query->value(6).toString());
        o.setPhone(1, query->value(7).toString());
        o.setPhone(2, query->value(8).toString());
        o.setAdditional(query->value(9).toString());
        o.setBankName(query->value(10).toString());
        o.setBankAccount(query->value(11).toString());
        o.setWebsite(query->value(12).toString());
        o.setEMail(query->value(13).toString());
        o.setLogoPath(query->value(14).toString());

    }

    if(this->isQueryError(query))
        throw new SQLException("OwnerModel::getActualOwner", query);

    delete query;

    return o;
}

int OwnerModel::addOwner(Owner o)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO owners (name, postcode, city, adress, nip, phone1, phone2, phone3, additional, account_bank_name, "
                   "account_number, website, email, logo) "
                 "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)  RETURNING id_owner");

    query->addBindValue(o.getName());
    query->addBindValue(o.getPostCode());
    query->addBindValue(o.getCity());
    query->addBindValue(o.getAdress());
    query->addBindValue(o.getNIP());
    query->addBindValue(o.getPhone(0));
    query->addBindValue(o.getPhone(1));
    query->addBindValue(o.getPhone(2));
    query->addBindValue(o.getAdditional());
    query->addBindValue(o.getBankName());
    query->addBindValue(o.getBankAccount());
    query->addBindValue(o.getWebsite());
    query->addBindValue(o.getEMail());
    query->addBindValue(o.getLogoPath());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("OwnerModel::addOwner", query);


    query->next();
    int insertedId = query->record().value("id_owner").toInt();
    delete query;

    return insertedId;
}

void OwnerModel::editOwner(Owner o)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE owners "
                   "SET name = ?, postcode = ?, city = ?, adress = ?, nip = ?, phone1 = ?, phone2 = ?, phone3 = ?, additional = ?, "
                   "account_bank_name = ?, account_number = ?, website = ?, email = ?, logo = ? "
                   "WHERE id_owner = ?");

    query->addBindValue(o.getName());
    query->addBindValue(o.getPostCode());
    query->addBindValue(o.getCity());
    query->addBindValue(o.getAdress());
    query->addBindValue(o.getNIP());
    query->addBindValue(o.getPhone(0));
    query->addBindValue(o.getPhone(1));
    query->addBindValue(o.getPhone(2));
    query->addBindValue(o.getAdditional());
    query->addBindValue(o.getBankName());
    query->addBindValue(o.getBankAccount());
    query->addBindValue(o.getWebsite());
    query->addBindValue(o.getEMail());
    query->addBindValue(o.getLogoPath());
    query->addBindValue(o.getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("OwnerModel::editOwner", query);

    delete query;
}

void OwnerModel::deactivateOwnerInDb(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE owners SET is_active = false WHERE id_owner = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("OwnerModel::deactivateOwnerInDb", query);

    delete query;
}

