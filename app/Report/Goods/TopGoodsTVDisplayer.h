#ifndef TOPGOODSTVDISPLAYER_H
#define TOPGOODSTVDISPLAYER_H

#include "Goods/GoodsTVDisplayer.h"

class TopGoodsTVDisplayer : public GoodsTVDisplayer
{
    bool isQuantityColumn() const;
    bool isGoodsGroupColumn() const;
    bool isPriceColumn() const;

public:
    TopGoodsTVDisplayer(const QModelIndex & index, int role, TVModel const* model);

    QVariant display() const;
};

#endif // TOPGOODSTVDISPLAYER_H
