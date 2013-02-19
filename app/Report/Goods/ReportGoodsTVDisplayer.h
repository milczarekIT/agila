#ifndef REPORTGOODSTVDISPLAYER_H
#define REPORTGOODSTVDISPLAYER_H

#include "Goods/GoodsTVDisplayer.h"

class ReportGoodsTVDisplayer : public GoodsTVDisplayer
{
    bool isQuantityColumn() const;
    bool isUnitColumn() const;
    bool isGoodsGroupColumn() const;
    bool isPriceColumn() const;
public:
    ReportGoodsTVDisplayer(const QModelIndex &index, int role, const TVModel *model);

    QVariant display() const;

};

#endif // REPORTGOODSTVDISPLAYER_H
