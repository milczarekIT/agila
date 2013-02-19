#include "OrderedGoodsTVDisplayer.h"

OrderedGoodsTVDisplayer::OrderedGoodsTVDisplayer(const QModelIndex &index, int role, const TVModel *model) : GoodsTVDisplayer(index, role, model)
{
}

QVariant OrderedGoodsTVDisplayer::display() const
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

bool OrderedGoodsTVDisplayer::isQuantityColumn() const
{
    return (index.column() == 3 || index.column() == 4);
}

bool OrderedGoodsTVDisplayer::isUnitColumn() const
{
    return index.column() == 5;
}

bool OrderedGoodsTVDisplayer::isPriceColumn() const
{
   return (index.column() >= 6 && index.column() <= 8);
}
