#include "ContractorService.h"

ContractorService::ContractorService()
{
    model = new ContractorModel();
    phoneService = new PhoneService();
    cacheService = new ContractorCacheService();

    insertedId = -1;
}

ContractorService::~ContractorService()
{
    delete model;
    delete phoneService;
    delete cacheService;
}

QVector<Contractor> ContractorService::getContractors() {
    QVector<Contractor> contractors;
    try {
        contractors = model->getContractors();

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return contractors;
}

Contractor ContractorService::getContractor(int id) {

    try {

        getStandardData(id);
        getPhones(id);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return contractor;
}

void ContractorService::getStandardData(int id) {
    contractor = model->getContractor(id);
}

void ContractorService::getPhones(int id) {
    contractor.setPhones(phoneService->getPhones(id));
}

int ContractorService::addContractor(Contractor c)
{
    try {
        Database::getInstance().db.transaction();

        insertedId = addContractorWithoutTransaction(c);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }

    return insertedId;
}

int ContractorService::addContractorWithoutTransaction(Contractor c)
{
    insertedId = model->addContractor(c);
    this->phoneService->addPhones(insertedId, c.getPhones());

    return insertedId;
}


void ContractorService::editContractor(Contractor c)
{
    try {
        Database::getInstance().db.transaction();
        if(cacheService->isUsed(c.getId()))
        {
            int newId = this->addContractorWithoutTransaction(c);
            int oldId = c.getId();
            model->deactivateContractorInDb(oldId);
            cacheService->saveHistory(oldId, newId);
        }
        else
            updateContractor(c);

        Database::getInstance().db.commit();
    } catch(SQLException *e)
    {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void ContractorService::updateContractor(Contractor c) {

    editStandardData(c);
    editPhones(c.getId(), c.getPhones());
}

void ContractorService::editStandardData(Contractor c) {
    model->editContractor(c);
}
void ContractorService::editPhones(int contractor, QVector<Phone> phones) {
    phoneService->editPhones(contractor, phones);
}

void ContractorService::removeContractor(int id)
{
    try {
        Database::getInstance().db.transaction();

        removeStandardData(id);
        removePhones(id);

        Database::getInstance().db.commit();
    } catch(SQLException* e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void ContractorService::removeStandardData(int id) {
    model->removeContractor(id);
}
void ContractorService::removePhones(int contractor) {
    phoneService->removePhones(contractor);
}
