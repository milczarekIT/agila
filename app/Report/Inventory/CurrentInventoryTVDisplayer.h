#ifndef CURRENTINVENTORYTVDisplayer_H
#define CURRENTINVENTORYTVDisplayer_H

#include "Other/TVDisplayer.h"
#include "Goods/GoodsService.h"

class CurrentInventoryTVDisplayer : public TVDisplayer
{
private:
    static const int COL_ID = 0;
    bool isQuantityColumn() const;
    bool isUnitColumn() const;
    bool isTaxColumn() const;
    bool isGoodsGroupColumn() const;
    bool isPriceColumn() const;

    QVariant displayQuantity() const;
    QVariant displayUnit() const;
    QVariant displayTax() const;
    QVariant displayGoodsGroup() const;
    QVariant displayPrice() const;
public:
    CurrentInventoryTVDisplayer(const QModelIndex & index, int role, TVModel const* model);

    QVariant display() const;
};

#endif // CURRENTINVENTORYTVDisplayer_H
