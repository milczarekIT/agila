#include "TopGoodsTVDisplayer.h"

TopGoodsTVDisplayer::TopGoodsTVDisplayer(const QModelIndex &index, int role, const TVModel *model) : GoodsTVDisplayer(index, role, model)
{
}

QVariant TopGoodsTVDisplayer::display() const
{
    if (isDisplayOrEditRole())
    {
        if (isQuantityColumn())
            return displayQuantity();
        else if(isPriceColumn())
            return displayPrice();
        else
            return model->baseData(index, role);
    }
    if(isTextAligmentRole())
    {
        if (isQuantityColumn() || isPriceColumn())
                return QVariant(Qt::AlignRight | Qt::AlignVCenter);
    }
    return QVariant();
}

bool TopGoodsTVDisplayer::isGoodsGroupColumn() const
{
    return index.column() == 3;
}

bool TopGoodsTVDisplayer::isQuantityColumn() const
{
    return (index.column() == 4);
}

bool TopGoodsTVDisplayer::isPriceColumn() const
{
   return (index.column() >= 5 && index.column() <= 7);
}

