#ifndef GOODSMODEL_H
#define GOODSMODEL_H

#include <QStringList>
#include "Database/Model.h"
#include "Goods/Goods.h"
#include "Goods/TaxModel.h"
#include "Goods/UnitModel.h"
#include "Goods/GoodsGroupModel.h"
#include "Goods/GoodsTVDisplayer.h"
#include "Settings/SettingsModel.h"
#include "Other/Application/ApplicationManager.h"

class GoodsModel : public Model
{
private:
    Warehouse *currentWarehouse;


    void addFeatures(int good, QVector<Feature> features);
    void editFeatures(int good, QVector<Feature> features);
    void removeFeatures(int good);

public:
    GoodsModel();
    ~GoodsModel();

    QVector<Goods> getGoods();
    Goods getGood(int id);
    int addGood(Goods g);
    void editGood(Goods g);
    void removeGood(int id);
    void removeGoodFromAllWarehouses(int id);

    double getPriceNet(int goodId, QString priceLevel);
    double getPriceGross(int goodId, QString priceLevel);

    /** deaktywuje towar we wszystkich magazynach w których występuje */
    void deactivateGoodInDb(int id);

    float getGoodQuantity(int id);
    float getGoodQuantityByWarehouse(int id, int warehouseId);

    /**
      * Metoda używana przy ruchach magazynowych
      * Zwiększanie stanu magazynowego
      * @param  id - nr id towaru w bazie danych (goods.id_good)
      *         incrQuantity - wziększenie stanu magazynowego o incrQuantity
      */
    void increaseQuantity(int id, float incrQuantity);

    /** @see increaseQuantity() */
    void decreaseQuantity(int id, float decrQuantity);

    /** dodaje informacje o wystąpieniu danego good w podanym magazynie */
    void addGoodToWarehouse(int goodId, int warehouseId);

    /** dodaje informacje o wystąpieniu danego good w podanym magazynie z podaną ilością */
    void addGoodToWarehouseWithQuantity(int goodId, int warehouseId, float quantity);

    bool isGoodOnlyAtActualWarehouse(int good);

    /** zwraca wektor id magazynów, w których występuje towar id */
    QVector<int> getWarehouseIdsWithGood(int good);

    /**
      * Zwraca wektor cech (z wartościami) dla towaru o podanym id
      * @param good - id_good
      */
    QVector<Feature> getFeatures(int good);

};

#endif // GOODMODEL_H
