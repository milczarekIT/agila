#include "OwnerService.h"

OwnerService::OwnerService()
{
    this->model = new OwnerModel();
    cacheService = new OwnerCacheService();

    insertedId = -1;
}

OwnerService::~OwnerService() {

}

bool OwnerService::isOwnerDefinied()
{
    bool definied = false;

    try {
        definied = model->isOwnerDefinied();

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return definied;
}

Owner OwnerService::getOwner(int id) {
    Owner owner;

    try {
        owner = model->getOwner(id);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return owner;
}

Owner OwnerService::getActualOwner() {
    Owner owner;

    try {
        owner = model->getActualOwner();

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return owner;
}

int OwnerService::addOwner(Owner o) {

    try {
        insertedId = model->addOwner(o);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }

    return this->insertedId;
}

void OwnerService::editOwner(Owner o) {
    try {

        if(cacheService->isUsed(o.getId()))
        {
            int newId = this->addOwner(o);
            int oldId = o.getId();
            model->deactivateOwnerInDb(oldId);
            cacheService->saveHistory(oldId, newId);
        }
        else
            model->editOwner(o);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
}

