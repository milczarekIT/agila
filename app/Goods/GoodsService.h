#ifndef GOODSSERVICE_H
#define GOODSSERVICE_H

#include "Goods/Goods.h"
#include "Goods/GoodsModel.h"
#include "Goods/GoodsCacheService.h"
#include "Other/Exceptions/SQLException.h"
#include "Other/Warehouse/WarehouseService.h"
#include "Other/Service.h"
class GoodsModel;

class GoodsService : public Service
{
    GoodsModel *model;
    GoodsCacheService *cacheService;

    int insertedId;
    Goods good;

    int addGoodWithoutTrasaction(Goods g);
    void updateGood(Goods g);
public:
    GoodsService();
    ~GoodsService();

    QVector<Goods> getGoods();
    Goods getGood(int id);
    int addGood(Goods g);
    int addGoodForAllWarehouses(Goods g);
    void editGood(Goods g);
    void removeGood(int id);
    void removeGoodFromAllWarehouses(int id);

    bool isGoodOnlyAtActualWarehouse(int good);

    double getPriceNet(int goodId, int priceLevel);
    double getPriceGross(int goodId, int priceLevel);
};

#endif // GOODSSERVICE_H
