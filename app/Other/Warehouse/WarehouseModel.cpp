#include "WarehouseModel.h"

WarehouseModel::WarehouseModel()
{
}

QVector<Warehouse> WarehouseModel::getWarehouses()
{
    QVector<Warehouse> warehouses;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id, short_name, warehouse_name, is_default FROM warehouses WHERE is_active = true ORDER BY warehouse_name");
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("WarehouseModel::getWarehouses", query);

    while(query->next())
    {
        Warehouse warehouse;
        warehouse.setId(query->value(0).toInt());
        warehouse.setShortName(query->value(1).toString());
        warehouse.setName(query->value(2).toString());
        warehouse.setDefaultWarehouse(query->value(3).toBool());
        warehouses.push_back(warehouse);
    }

    delete query;

    return warehouses;
}

Warehouse WarehouseModel::getWarehouse(int id)
{
    Warehouse warehouse;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT short_name, warehouse_name, is_default FROM warehouses WHERE id = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("WarehouseModel::getWarehouse", query);

    if(query->size() > 0)
    {
        query->first();

        warehouse.setId(id);
        warehouse.setShortName(query->value(0).toString());
        warehouse.setName(query->value(1).toString());
        warehouse.setDefaultWarehouse(query->value(2).toBool());
    }
    delete query;

    return warehouse;
}

int WarehouseModel::addWarehouse(Warehouse warehouse)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO warehouses (id, short_name, Warehouse_name, is_default) VALUES (DEFAULT, ?, ?, ?) RETURNING id");
    query->addBindValue(warehouse.getShortName());
    query->addBindValue(warehouse.getName());
    query->addBindValue(warehouse.isDefaultWarehouse());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("WarehouseModel::addWarehouse", query);

    query->next();
    int addedId = query->record().value("id").toInt();

    delete query;

    return addedId;
}

void WarehouseModel::editWarehouse(Warehouse warehouse)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE warehouses SET warehouse_name = ?, short_name = ?, is_default = ? WHERE id = ?");
    query->addBindValue(warehouse.getName());
    query->addBindValue(warehouse.getShortName());
    query->addBindValue(warehouse.isDefaultWarehouse());
    query->addBindValue(warehouse.getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("WarehouseModel::editWarehouse", query);

    delete query;
}

bool WarehouseModel::isDefaultMagazineInDb() {
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id FROM warehouses WHERE is_default = true");
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("WarehouseModel::editWarehouse", query);

    bool defaultExist = (query->size() > 0);
    delete query;

    return defaultExist;
}

void WarehouseModel::setDefaultRandomWarehouseOtherThan(int warehouseId) {
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE warehouses SET is_default = true WHERE id = (SELECT id FROM warehouses WHERE id != ? ORDER BY id LIMIT 1)");
    query->addBindValue(warehouseId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("WarehouseModel::editWarehouse", query);

    delete query;
}

void WarehouseModel::removeWarehouse(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE warehouses SET is_active = false WHERE id = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("WarehouseModel::removeWarehouse", query);

    delete query;

}

void WarehouseModel::setDefaultWarehouse(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE warehouses SET is_default = true WHERE id = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("WarehouseModel::setDefaultWarehouse", query);

    delete query;

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE warehouses SET is_default = false WHERE id != ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("WarehouseModel::setDefaultWarehouse", query);
}

bool WarehouseModel::isNameAvailable(QString name) {
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id FROM warehouses WHERE warehouse_name = ? AND is_active = true");
    query->addBindValue(name);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("WarehouseModel::isNameAvailable", query);

    bool available = (query->size() == 0);
    delete query;

    return available;
}

bool WarehouseModel::isShortNameAvailable(QString shortName) {
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id FROM warehouses WHERE short_name = ? AND is_active = true");
    query->addBindValue(shortName);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("WarehouseModel::isShortNameAvailable", query);

    bool available = (query->size() == 0);
    delete query;

    return available;
}

Warehouse* WarehouseModel::getDefaultWarehouse() {
    Warehouse *warehouse = new Warehouse();
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT id, short_name, warehouse_name, is_default FROM warehouses WHERE is_default = true AND is_active = true");
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("WarehouseModel::getDefaultWarehouse", query);

    if(query->size() > 0)
    {
        query->first();
        warehouse->setId(query->value(0).toInt());
        warehouse->setShortName(query->value(1).toString());
        warehouse->setName(query->value(2).toString());
        warehouse->setDefaultWarehouse(query->value(3).toBool());
    }
    delete query;

    return warehouse;
}

void WarehouseModel::importGoodsFromWarehouse(int fromWarehouse, int toWarehouse) {
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO wh_goods(warehouse, good, quantity, is_active) "
                   "SELECT ?, id_good, 0, true FROM goods WHERE is_active = true AND id_good IN "
                        "(SELECT good FROM wh_goods WHERE warehouse = ? AND is_active = true)");
    query->addBindValue(toWarehouse);
    query->addBindValue(fromWarehouse);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("WarehouseModel::importGoodsFromWarehouse", query);

    delete query;
}
