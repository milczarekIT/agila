#ifndef ORDEREDGOODSTVDISPLAYER_H
#define ORDEREDGOODSTVDISPLAYER_H

#include "Goods/GoodsTVDisplayer.h"

class OrderedGoodsTVDisplayer : public GoodsTVDisplayer
{
    bool isQuantityColumn() const;
    bool isUnitColumn() const;
    bool isPriceColumn() const;
public:
    OrderedGoodsTVDisplayer(const QModelIndex &index, int role, const TVModel *model);

    QVariant display() const;
};

#endif // ORDEREDGOODSTVDISPLAYER_H
