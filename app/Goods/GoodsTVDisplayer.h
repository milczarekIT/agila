#ifndef GOODSTVDISPLAYER_H
#define GOODSTVDISPLAYER_H

#include <QSqlQueryModel>
#include "Other/TVDisplayer.h"
#include "Goods/UnitModel.h"
#include "Goods/TaxModel.h"
#include "Goods/GoodsGroupModel.h"
#include "Goods/GoodsService.h"

/**
  * Displayer customowych danych dla modelu Goods w TableView
  * @author Bartosz Milczarek
  */
class GoodsTVDisplayer : public TVDisplayer
{
protected:
    bool isQuantityColumn() const;
    bool isUnitColumn() const;
    bool isTaxColumn() const;
    bool isGoodsGroupColumn() const;
    bool isPriceColumn() const;

    QVariant displayQuantity() const;
    QVariant displayPrice() const;
public:
    GoodsTVDisplayer(const QModelIndex & index, int role, TVModel const* model);
    ~GoodsTVDisplayer();

    QVariant display() const;
};

#endif // GOODSTVDISPLAYER_H
