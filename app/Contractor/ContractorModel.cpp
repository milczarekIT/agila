#include "ContractorModel.h"

ContractorModel::ContractorModel()
{
    this->additionalIdModel = new ContractorAdditionalTypeIdModel();
}

ContractorModel::~ContractorModel()
{
    delete additionalIdModel;
}
QVector<Contractor> ContractorModel::getContractors() {
    QVector<Contractor> contractors;

    SOMModel *somModel = new SOMModel();
    ContractorGroupModel *contractorGroupModel = new ContractorGroupModel();
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT symbol, name, contractor_group, type, postcode, city, "
                "adress, nip, additional_id_type, additional_id_value, discount, additional, "
                "account_number, website, email, comments, source_of_mem, representative, is_company, id_contractor "
                "FROM contractors WHERE is_active = true ORDER BY name");
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("ContractorModel::getContractors", query);
    while(query->next())
    {
        Contractor c;
        c.setSymbol(query->value(0).toString());
        c.setName(query->value(1).toString());
        c.setContractorGroup(contractorGroupModel->getContractorGroup(query->value(2).toInt()));
        c.setType(query->value(3).toInt());
        c.setPostcode(query->value(4).toString());
        c.setCity(query->value(5).toString());
        c.setAddress(query->value(6).toString());
        c.setNip(query->value(7).toString());
        int additionalTypeId = query->value(8).toInt();
        QString additionalIdValue = query->value(9).toString();
        c.setAdditionalId(this->additionalIdModel->getTypeId(additionalTypeId), additionalIdValue);
        c.setDiscount(query->value(10).toDouble());
        c.setAdditional(query->value(11).toString());
        c.setAccountNumber(query->value(12).toString());
        c.setWebsite(query->value(13).toString());
        c.setEmail(query->value(14).toString());
        c.setComments(query->value(15).toString());
        c.setSourceOfMember(somModel->getSourceOfMember(query->value(16).toInt()));
        c.setRepresetative(query->value(17).toString());
        c.setCompany(query->value(18).toBool());
        c.setId(query->value(19).toInt());
        contractors.push_back(c);
    }

    delete somModel;
    delete contractorGroupModel;
    delete query;

    return contractors;
}

Contractor ContractorModel::getContractor(int id)
{
    SOMModel *somModel = new SOMModel();
    ContractorGroupModel *contractorGroupModel = new ContractorGroupModel();
    Contractor c;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT symbol, name, contractor_group, type, postcode, city, "
                "adress, nip, additional_id_type, additional_id_value, discount, additional, "
                "account_number, website, email, comments, source_of_mem, representative, is_company "
                "FROM contractors "
                "WHERE  id_contractor = :id");
    query->bindValue(":id", id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("ContractorModel::getContractor", query);
    else if(query->size() > 0)
    {
        query->first();

        c.setId(id);
        c.setSymbol(query->value(0).toString());
        c.setName(query->value(1).toString());
        c.setContractorGroup(contractorGroupModel->getContractorGroup(query->value(2).toInt()));
        c.setType(query->value(3).toInt());
        c.setPostcode(query->value(4).toString());
        c.setCity(query->value(5).toString());
        c.setAddress(query->value(6).toString());
        c.setNip(query->value(7).toString());
        int additionalTypeId = query->value(8).toInt();
        QString additionalIdValue = query->value(9).toString();
        c.setAdditionalId(this->additionalIdModel->getTypeId(additionalTypeId), additionalIdValue);
        c.setDiscount(query->value(10).toDouble());
        c.setAdditional(query->value(11).toString());
        c.setAccountNumber(query->value(12).toString());
        c.setWebsite(query->value(13).toString());
        c.setEmail(query->value(14).toString());
        c.setComments(query->value(15).toString());
        c.setSourceOfMember(somModel->getSourceOfMember(query->value(16).toInt()));
        c.setRepresetative(query->value(17).toString());
        c.setCompany(query->value(18).toBool());

    }

    delete somModel;
    delete contractorGroupModel;
    delete query;

    return c;
}

int ContractorModel::addContractor(Contractor c)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO contractors (id_contractor, symbol, name, contractor_group, type, postcode, city, "
                   "adress, nip, additional_id_type, additional_id_value, discount, additional, account_number, website, email, "
                   "comments, source_of_mem, representative, is_company) "
                    "VALUES (DEFAULT, :symbol, :name, :contractor_group, :type, :post_code, :city, :adress, :nip, :additional_id_type, "
                   ":additional_id_value, :discount, :additional, :account_number, :website, :email, :comments, :source_of_mem, "
                   ":representative, :is_company) RETURNING id_contractor");
    query->bindValue(":symbol", c.getSymbol());
    query->bindValue(":name", c.getName());
    query->bindValue(":contractor_group", c.getContractorGroup().getId());
    query->bindValue(":type", c.getType());
    query->bindValue(":post_code", c.getPostcode());
    query->bindValue(":city", c.getCity());
    query->bindValue(":adress", c.getAddress());
    query->bindValue(":nip", c.getNip());
    query->bindValue(":additional_id_type", c.getAdditionalId().getType().getId());
    query->bindValue(":additional_id_value", c.getAdditionalId().getValue());
    query->bindValue(":discount", c.getDiscount());
    query->bindValue(":additional", c.getAdditional());
    query->bindValue(":account_number", c.getAccountNumber());
    query->bindValue(":website", c.getWebsite());
    query->bindValue(":email", c.getEmail());
    query->bindValue(":commments", c.getComments());
    query->bindValue(":source_of_mem", c.getSourceOfMember().getId());
    query->bindValue(":represetative", c.getRepresentative());
    query->bindValue(":is_comapny", c.isCompany());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("addContractor", query);

    query->next();
    int insertedId = query->record().value("id_contractor").toInt();

    return insertedId;
}

void ContractorModel::editContractor(Contractor c)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE contractors "
                    "SET symbol = :symbol, name = :name, contractor_group = :contractor_group, "
                        "type = :type, postcode  = :postcode, city = :city, adress = :adress, nip = :nip, additional_id_type = :additional_id_type, "
                        "additional_id_value = :additional_id_value, discount = :discount, additional = :additional, account_number = :account_number, website = :website, "
                        "email = :email, comments = :comments, "
                        "source_of_mem = :source_of_mem, representative = :representative, is_company = :is_company "
                    "WHERE id_contractor = :id");

    query->bindValue(":symbol", c.getSymbol());
    query->bindValue(":name", c.getName());
    query->bindValue(":contractor_group", c.getContractorGroup().getId());
    query->bindValue(":type", c.getType());
    query->bindValue(":postcode", c.getPostcode());
    query->bindValue(":city", c.getCity());
    query->bindValue(":adress", c.getAddress());
    query->bindValue(":nip", c.getNip());
    query->bindValue(":additional_id_type", c.getAdditionalId().getType().getId());
    query->bindValue(":additional_id_value", c.getAdditionalId().getValue());
    query->bindValue(":discount", c.getDiscount());
    query->bindValue(":additional", c.getAdditional());
    query->bindValue(":account_number", c.getAccountNumber());
    query->bindValue(":website", c.getWebsite());
    query->bindValue(":email", c.getEmail());
    query->bindValue(":comments", c.getComments());
    query->bindValue(":source_of_mem", c.getSourceOfMember().getId());
    query->bindValue(":representative", c.getRepresentative());
    query->bindValue(":is_company", c.isCompany());
    query->bindValue(":id", c.getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("ContractorModel::editContractor", query);

    delete query;

}

void ContractorModel::removeContractor(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE contractors SET is_active = false WHERE id_contractor = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("ContractorModel::removeContractor", query);

    delete query;
}

void ContractorModel::deactivateContractorInDb(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE contractors SET is_active = false WHERE id_contractor = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("ContractorModel::deactivateContractorInDb", query);

    delete query;
}


