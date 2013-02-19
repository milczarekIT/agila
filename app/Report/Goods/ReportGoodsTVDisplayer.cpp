#include "ReportGoodsTVDisplayer.h"

ReportGoodsTVDisplayer::ReportGoodsTVDisplayer(const QModelIndex &index, int role, const TVModel *model) : GoodsTVDisplayer(index, role, model)
{
}

QVariant ReportGoodsTVDisplayer::display() const
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

bool ReportGoodsTVDisplayer::isQuantityColumn() const
{
    return index.column() == 3;
}

bool ReportGoodsTVDisplayer::isUnitColumn() const
{
    return index.column() == 4;
}

bool ReportGoodsTVDisplayer::isGoodsGroupColumn() const
{
    return index.column() == 5;
}

bool ReportGoodsTVDisplayer::isPriceColumn() const
{
   return (index.column() >= 6 && index.column() <= 7);
}
