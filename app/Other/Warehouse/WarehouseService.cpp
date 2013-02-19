#include "WarehouseService.h"

WarehouseService::WarehouseService()
{
    model = new WarehouseModel();
}

WarehouseService::~WarehouseService()
{
    delete model;
}

QVector<Warehouse> WarehouseService::getWarehouses() {
    QVector<Warehouse> warehouses;
    try {
        warehouses = model->getWarehouses();

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
    return warehouses;
}

Warehouse WarehouseService::getWarehouse(int id) {
    Warehouse warehouse;
    try {
        warehouse = model->getWarehouse(id);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
    return warehouse;
}

int WarehouseService::addWarehouse(Warehouse warehouse) {
    int insertedId = -1;
    try {
        insertedId = model->addWarehouse(warehouse);

        if(warehouse.isDefaultWarehouse())
            this->setDefaultWarehouse(insertedId);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
    return insertedId;
}

void WarehouseService::editWarehouse(Warehouse warehouse) {
    try {
        model->editWarehouse(warehouse);

        if(warehouse.isDefaultWarehouse())
            model->setDefaultWarehouse(warehouse.getId());
        else if(!model->isDefaultMagazineInDb())
            model->setDefaultRandomWarehouseOtherThan(warehouse.getId());

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
}

void WarehouseService::removeWarehouse(int id) {
    try {
        model->removeWarehouse(id);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
}

bool WarehouseService::isNameAvailable(QString name) {
    bool available = false;
    try {
        available = model->isNameAvailable(name);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
    return available;
}

bool WarehouseService::isShortNameAvailable(QString shortName) {
    bool available = false;
    try {
        available = model->isShortNameAvailable(shortName);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
    return available;
}

void WarehouseService::setDefaultWarehouse(int id) {
    try {
        model->setDefaultWarehouse(id);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
}

Warehouse* WarehouseService::getDefaultWarehouse() {
    Warehouse* defaultWarehouse = new Warehouse();
    try {
       defaultWarehouse = model->getDefaultWarehouse();

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
    return defaultWarehouse;
}

void WarehouseService::importGoodsFromWarehouse(int fromWarehouse, int toWarehouse) {
    try {
       model->importGoodsFromWarehouse(fromWarehouse, toWarehouse);

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
}
