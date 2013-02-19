#include "GoodsService.h"

GoodsService::GoodsService()
{
    model = new GoodsModel();
    cacheService = new GoodsCacheService();

    insertedId = -1;
}

GoodsService::~GoodsService()
{
    delete model;
    delete cacheService;
}

QVector<Goods> GoodsService::getGoods() {
    QVector<Goods> goods;
    try {
        goods = model->getGoods();

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
    return goods;
}

Goods GoodsService::getGood(int id) {

    try {
        good = model->getGood(id);
        good.setFeatures(model->getFeatures(id));

    } catch(SQLException *e) {
        this->showErrorInfo(e);
    }
    return good;
}


int GoodsService::addGood(Goods g)
{
    try {
        Database::getInstance().db.transaction();

        insertedId = addGoodWithoutTrasaction(g);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
    return insertedId;
}

// do edycji, aby nie było 2óch transakcji
int GoodsService::addGoodWithoutTrasaction(Goods g)
{
    try {

        this->insertedId = model->addGood(g);
        model->addGoodToWarehouse(insertedId, ApplicationManager::getInstance()->getWarehouse()->getId());

    } catch(SQLException *e) {

        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
    return insertedId;
}

int GoodsService::addGoodForAllWarehouses(Goods g)
{
    try {
        Database::getInstance().db.transaction();

        this->insertedId = model->addGood(g);
        WarehouseService *whService = new WarehouseService();
        QVector<Warehouse> warehouses = whService->getWarehouses();
        delete whService;

        for(int i = 0; i < warehouses.size(); i++) {
            model->addGoodToWarehouse(insertedId, warehouses[i].getId());
        }

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
    return insertedId;
}

void GoodsService::editGood(Goods g)
{
    try {
        Database::getInstance().db.transaction();

        if(cacheService->isUsed(g.getId()))
        {
            int newId = this->addGoodWithoutTrasaction(g); // dodaje nowy towar do goods oraz aktualnego magazynu, z ilością zero
            model->increaseQuantity(newId, g.getQuantity()); // zwiąksza ilość od zera do stanu faktycznego
            int oldId = g.getId();

            if(! model->isGoodOnlyAtActualWarehouse(g.getId()))
            {
                int currentWarehouseId = ApplicationManager::getInstance()->getWarehouseId();
                QVector<int> warehouseIds = model->getWarehouseIdsWithGood(g.getId());
                for(int i = 0; i < warehouseIds.size(); i++)
                {
                    if(warehouseIds[i] != currentWarehouseId)
                    {
                        float quantityAtWarehouse = model->getGoodQuantityByWarehouse(oldId, warehouseIds[i]);
                        model->addGoodToWarehouseWithQuantity(newId, warehouseIds[i], quantityAtWarehouse);
                    }
                }
            }

            model->deactivateGoodInDb(oldId);
            cacheService->saveHistory(oldId, newId);
        }
        else
            updateGood(g);

        Database::getInstance().db.commit();
    } catch(SQLException *e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

/* transakcje w editGood */
void GoodsService::updateGood(Goods g) {
    try {

        model->editGood(g);

    } catch(SQLException *e) {
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());

    }
}

void GoodsService::removeGood(int id)
{
    try {
        Database::getInstance().db.transaction();

        model->removeGood(id);

        Database::getInstance().db.commit();
    } catch(SQLException* e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

void GoodsService::removeGoodFromAllWarehouses(int id)
{
    try {
        Database::getInstance().db.transaction();

        model->removeGoodFromAllWarehouses(id);

        Database::getInstance().db.commit();
    } catch(SQLException* e) {
        Database::getInstance().db.rollback();
        MessageBox().createWarningBox("Niespodziewany błąd. \nLog: " + e->getLogFilePath());
    }
}

bool GoodsService::isGoodOnlyAtActualWarehouse(int good) {
    bool onlyAtActualWarehouse = true;
    try {
        onlyAtActualWarehouse = model->isGoodOnlyAtActualWarehouse(good);

    } catch(SQLException* e) {
        this->showErrorInfo(e);
    }

    return onlyAtActualWarehouse;
}

double GoodsService::getPriceNet(int goodId, int priceLevel) {
    double price = 0.0;
    try {
        price = model->getPriceNet(goodId, Price::priceLevelToString(priceLevel));

    } catch(SQLException* e) {
        this->showErrorInfo(e);
    }

    return price;
}

double GoodsService::getPriceGross(int goodId, int priceLevel) {
    double price = 0.0;
    try {
        price = model->getPriceGross(goodId, Price::priceLevelToString(priceLevel));

    } catch(SQLException* e) {
        this->showErrorInfo(e);
    }

    return price;
}

