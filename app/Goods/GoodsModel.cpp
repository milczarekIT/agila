#include "GoodsModel.h"


GoodsModel::GoodsModel()
{
    currentWarehouse = ApplicationManager::getInstance()->getWarehouse();
}

GoodsModel::~GoodsModel() {}

QVector<Goods> GoodsModel::getGoods() {

    QVector<Goods> goods;
    TaxModel *taxModel = new TaxModel();
    UnitModel *unitModel = new UnitModel();
    GoodsGroupModel *goodsGroupModel = new GoodsGroupModel();

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT symbol, name, type, quantity, unit, tax, pkwiu, goods_group, "
                        "price_a_net, price_a_gross, price_mag_net, price_mag_gross, "
                        "price_b_net, price_b_gross, price_c_net, price_c_gross, "
                        "description, foto, weight, id_good "
                    "FROM goods, wh_goods wh WHERE id_good = wh.good AND wh.warehouse = :warehouse AND wh.is_active = true ORDER BY name");
    query->bindValue(":warehouse", currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::getGoods", query);
    while(query->next())
    {
        Goods g;
        g.setSymbol(query->value(0).toString());
        g.setName(query->value(1).toString());
        g.setType(query->value(2).toInt());
        g.setQuantity(query->value(3).toDouble());
        g.setUnit(unitModel->getUnit(query->value(4).toInt()));
        g.setTax(taxModel->getTax(query->value(5).toInt()));
        g.setPkwiu(query->value(6).toString());
        g.setGoodsGroup(goodsGroupModel->getGoodsGroup(query->value(7).toInt()));
        g.setPriceNet(Price::A, query->value(8).toDouble());
        g.setPriceGross(Price::A, query->value(9).toDouble());
        g.setPriceNet(Price::MAG, query->value(10).toDouble());
        g.setPriceGross(Price::MAG, query->value(11).toDouble());
        g.setPriceNet(Price::B, query->value(12).toDouble());
        g.setPriceGross(Price::B, query->value(13).toDouble());
        g.setPriceNet(Price::C, query->value(14).toDouble());
        g.setPriceGross(Price::C, query->value(15).toDouble());
        g.setDescription(query->value(16).toString());
        g.setFoto(query->value(17).toString());
        g.setWeight(query->value(18).toFloat());
        g.setId(query->value(19).toInt());
        goods.push_back(g);
    }

    delete taxModel;
    delete unitModel;
    delete goodsGroupModel;

    return goods;
}


Goods GoodsModel::getGood(int id)
{
    TaxModel *taxModel = new TaxModel();
    UnitModel *unitModel = new UnitModel();
    GoodsGroupModel *goodsGroupModel = new GoodsGroupModel();
    Goods g;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT symbol, name, type, wh.quantity, unit, tax, pkwiu, goods_group, "
                        "price_a_net, price_a_gross, price_mag_net, price_mag_gross, "
                        "price_b_net, price_b_gross, price_c_net, price_c_gross, "
                        "description, foto, weight "
                    "FROM goods, wh_goods wh "
                    "WHERE goods.id_good = wh.good AND wh.warehouse =  :warehouse AND id_good = :id");
    query->bindValue(":warehouse", currentWarehouse->getId());
    query->bindValue(":id", id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::getGood", query);
    else if(query->size() > 0)
    {
        query->first();

        g.setId(id);
        g.setSymbol(query->value(0).toString());
        g.setName(query->value(1).toString());
        g.setType(query->value(2).toInt());
        g.setQuantity(query->value(3).toDouble());
        g.setUnit(unitModel->getUnit(query->value(4).toInt()));
        g.setTax(taxModel->getTax(query->value(5).toInt()));
        g.setPkwiu(query->value(6).toString());
        g.setGoodsGroup(goodsGroupModel->getGoodsGroup(query->value(7).toInt()));
        g.setPriceNet(Price::A, query->value(8).toDouble());
        g.setPriceGross(Price::A, query->value(9).toDouble());
        g.setPriceNet(Price::MAG, query->value(10).toDouble());
        g.setPriceGross(Price::MAG, query->value(11).toDouble());
        g.setPriceNet(Price::B, query->value(12).toDouble());
        g.setPriceGross(Price::B, query->value(13).toDouble());
        g.setPriceNet(Price::C, query->value(14).toDouble());
        g.setPriceGross(Price::C, query->value(15).toDouble());
        g.setDescription(query->value(16).toString());
        g.setFoto(query->value(17).toString());
        g.setWeight(query->value(18).toFloat());

    }

    delete taxModel;
    delete unitModel;
    delete goodsGroupModel;

    return g;
}

int GoodsModel::addGood(Goods g)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO goods (id_good, symbol, name, type, tax, unit, pkwiu, goods_group, "
                                            "price_a_net, price_a_gross, price_mag_net, price_mag_gross, price_b_net, price_b_gross, "
                                            "price_c_net, price_c_gross, description, foto, weight) "
                    "VALUES (DEFAULT, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?) RETURNING id_good");

    query->addBindValue(g.getSymbol());
    query->addBindValue(g.getName());
    query->addBindValue(g.getType());
    query->addBindValue(g.getTax().getId());
    query->addBindValue(g.getUnit().getId());
    query->addBindValue(g.getPkwiu());
    query->addBindValue(g.getGoodsGroup().getId());
    query->addBindValue(g.getPriceNet(Price::A).value());
    query->addBindValue(g.getPriceGross(Price::A).value());
    query->addBindValue(g.getPriceNet(Price::MAG).value());
    query->addBindValue(g.getPriceGross(Price::MAG).value());
    query->addBindValue(g.getPriceNet(Price::B).value());
    query->addBindValue(g.getPriceGross(Price::B).value());
    query->addBindValue(g.getPriceNet(Price::C).value());
    query->addBindValue(g.getPriceGross(Price::C).value());
    query->addBindValue(g.getDescription());
    query->addBindValue(g.getFoto());
    query->addBindValue(g.getWeight());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::addGood", query);
    else
    {
        // dodaj także wartości cech towarowych
        query->next();
        int addedId = query->record().value("id_good").toInt();
        this->addFeatures(addedId, g.getFeatures());

        return addedId;
    }

}

void GoodsModel::addGoodToWarehouse(int goodId, int warehouseId) {
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO wh_goods (warehouse, good) VALUES (?, ?)");
    query->addBindValue(warehouseId);
    query->addBindValue(goodId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::addGoodToWarehouse", query);
}

void GoodsModel::addGoodToWarehouseWithQuantity(int goodId, int warehouseId, float quantity)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO wh_goods (warehouse, good, quantity) VALUES (?, ?, ?)");
    query->addBindValue(warehouseId);
    query->addBindValue(goodId);
    query->addBindValue(quantity);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::addGoodToWarehouseWithQuantity", query);
}

void GoodsModel::editGood(Goods g)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE goods "
                   "SET symbol = ?, name = ?, type = ?, tax = ?, unit = ?, pkwiu = ?, goods_group = ?, "
                         "price_a_net = ?, price_a_gross = ?, price_mag_net = ?, price_mag_gross = ?, price_b_net = ?, price_b_gross = ?, "
                         "price_c_net = ?, price_c_gross = ?, description = ?, foto = ?, weight = ? "
                   "WHERE id_good = ?");

    query->addBindValue(g.getSymbol());
    query->addBindValue(g.getName());
    query->addBindValue(g.getType());
    query->addBindValue(g.getTax().getId());
    query->addBindValue(g.getUnit().getId());
    query->addBindValue(g.getPkwiu());
    query->addBindValue(g.getGoodsGroup().getId());
    query->addBindValue(g.getPriceNet(Price::A).value());
    query->addBindValue(g.getPriceGross(Price::A).value());
    query->addBindValue(g.getPriceNet(Price::MAG).value());
    query->addBindValue(g.getPriceGross(Price::MAG).value());
    query->addBindValue(g.getPriceNet(Price::B).value());
    query->addBindValue(g.getPriceGross(Price::B).value());
    query->addBindValue(g.getPriceNet(Price::C).value());
    query->addBindValue(g.getPriceGross(Price::C).value());
    query->addBindValue(g.getDescription());
    query->addBindValue(g.getFoto());
    query->addBindValue(g.getWeight());
    query->addBindValue(g.getId());

    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::editGood", query);
    else
    {
        // edytuj cechy towarowe
        QVector<Feature> oldFeatures = this->getFeatures(g.getId());
        QVector<Feature> newFeatures = g.getFeatures();
        if(oldFeatures != newFeatures)
            this->editFeatures(g.getId(), newFeatures);

    }
}

void GoodsModel::removeGood(int id)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE wh_goods SET is_active = false WHERE good = ? AND warehouse = ?");
    query->addBindValue(id);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::removeGood", query);
}

void GoodsModel::removeGoodFromAllWarehouses(int id) {
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE wh_goods SET is_active = false WHERE good = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::removeGoodFromAllWarehouses", query);

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE goods SET is_active = false WHERE id_good = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::removeGoodFromAllWarehouses2", query);
}

void GoodsModel::deactivateGoodInDb(int id)
{
    // tabela wh_goods
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE wh_goods SET quantity = 0, is_active = false WHERE good = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::deactivateGoodsInDb", query);
    delete query;

    // tabela goods
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE goods SET is_active = false WHERE id_good = ?");
    query->addBindValue(id);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::deactivateGoodsInDb2", query);

    delete query;
}

float GoodsModel::getGoodQuantity(int id)
{
    return this->getGoodQuantityByWarehouse(id, currentWarehouse->getId());
}

float GoodsModel::getGoodQuantityByWarehouse(int id, int warehouseId) {
    float quantity = 0.0;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT quantity FROM wh_goods WHERE good = ? AND warehouse = ?");
    query->addBindValue(id);
    query->addBindValue(warehouseId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::getGoodQuantityByWarehouse", query);
    else if(query->size() > 0)
    {
        query->first();
        quantity = query->value(0).toDouble();
    }
    return quantity;
}

void GoodsModel::increaseQuantity(int id, float incrQuantity)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE wh_goods SET quantity = quantity+? WHERE good = ? AND warehouse = ?");
    query->addBindValue(incrQuantity);
    query->addBindValue(id);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::increaseQuantity", query);
}

void GoodsModel::decreaseQuantity(int id, float decrQuantity)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE wh_goods SET quantity = quantity-? WHERE good = ? AND warehouse = ?");
    query->addBindValue(decrQuantity);
    query->addBindValue(id);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::decreaseQuantity", query);
}

QVector<Feature> GoodsModel::getFeatures(int good)
{
    QVector<Feature> features;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT feature, name, value FROM features, goods_future_values "
                    "WHERE goods_future_values.feature = features.id_feature "
                    "AND good = ?");
    query->addBindValue(good);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::getFeatures", query);
    else
    {
        Feature *f = new Feature();
        while(query->next())
        {
            f->setId(query->value(0).toInt());
            f->setName(query->value(1).toString());
            f->setValue(query->value(2).toString());
            features.push_back(*f);
        }
        delete f;
    }

    return features;
}

void GoodsModel::addFeatures(int good, QVector<Feature> features)
{
    query = new QSqlQuery(Database::getInstance().db);
    for(int i = 0; i < features.size(); i++)
    {
        if(!features[i].getValue().isEmpty())
        {
            query->prepare("INSERT INTO  goods_future_values (good, feature, value) "
                            "VALUES (?, ?, ?)");
            query->addBindValue(good);
            query->addBindValue(features[i].getId());
            query->addBindValue(features[i].getValue());
            query->exec();

            if(this->isQueryError(query))
                throw new SQLException("GoodsModel::addFeatures", query);
        }

    }

    delete query;
}

void GoodsModel::editFeatures(int good, QVector<Feature> features)
{
    this->removeFeatures(good);
    this->addFeatures(good, features);
}

void GoodsModel::removeFeatures(int good)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM goods_future_values WHERE good = ?");
    query->addBindValue(good);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::removeFeatures", query);
}

bool GoodsModel::isGoodOnlyAtActualWarehouse(int good) {
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT warehouse FROM wh_goods WHERE good = ? AND is_active = true AND warehouse != ?");
    query->addBindValue(good);
    query->addBindValue(ApplicationManager::getInstance()->getWarehouseId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::removeFeatures", query);

    return (query->size() == 0);
}

QVector<int> GoodsModel::getWarehouseIdsWithGood(int good) {
    QVector<int> warehouseIds;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT warehouse FROM wh_goods WHERE good = ? AND is_active = true");
    query->addBindValue(good);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::removeFeatures", query);

    while(query->next())
    {
        warehouseIds.push_back(query->value(0).toInt());
    }
    delete query;

    return warehouseIds;
}

double GoodsModel::getPriceNet(int goodId, QString priceLevel) {
    QString columnName = "price_" + priceLevel.toLower() + "_net";

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT " + columnName + " FROM goods WHERE id_good = ?");
    query->addBindValue(goodId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::getPriceNet", query);

    double price = 0.0;
    if(query->size() > 0)
    {
        query->first();
        price = query->value(0).toDouble();
    }
    delete query;

    return price;
}

double GoodsModel::getPriceGross(int goodId, QString priceLevel) {
    QString columnName = "price_" + priceLevel.toLower() + "_gross";

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT " + columnName + " FROM goods WHERE id_good = ?");
    query->addBindValue(goodId);
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("GoodsModel::getPriceGross", query);

    double price = 0.0;
    if(query->size() > 0)
    {
        query->first();
        price = query->value(0).toDouble();
    }
    delete query;

    return price;
}
