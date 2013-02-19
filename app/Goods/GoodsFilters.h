#ifndef GOODSFILTERS_H
#define GOODSFILTERS_H

#include <QString>
#include "Goods/Goods.h"

class GoodsFilters
{
private:
    QString symbolFilter;
    QString nameFilter;
    QString goodsGroupFilter;
    QString goodsTypeFilter;
    QString taxForRRFilter;

public:
    GoodsFilters();

    void setGoodsGroupFilter(int idGroup);
    void setSymbolFilter (QString value);
    void setNameFilter (QString value);
    void setGoodsTypeFilter(int type);
    void setTaxForRRFilter(int idTax);

    QString getSymbolFilter();
    QString getNameFilter();
    QString getGoodsGroupFilter();
    QString getGoodsTypeFilter();
    QString getTaxForRRFilter();
};

#endif // GOODSFILTERS_H
