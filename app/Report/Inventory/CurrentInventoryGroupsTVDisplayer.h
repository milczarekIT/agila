#ifndef CURRENTINVENTORYGROUPSTVDISPLAYER_H
#define CURRENTINVENTORYGROUPSTVDISPLAYER_H

#include "Other/TVDisplayer.h"
#include "Goods/GoodsService.h"

class CurrentInventoryGroupsTVDisplayer : public TVDisplayer
{
    static const int COL_ID = 0;
     bool isQuantityColumn() const;
     bool isGoodsGroupColumn() const;
     bool isPriceColumn() const;

     QVariant displayQuantity() const;
     QVariant displayGoodsGroup() const;
     QVariant displayPrice() const;
public:
    CurrentInventoryGroupsTVDisplayer(const QModelIndex & index, int role, TVModel const* model);

    QVariant display() const;
};

#endif // CURRENTINVENTORYGROUPSTVDISPLAYER_H
