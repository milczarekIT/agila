#include "UnrealizedOrderTVDisplayer.h"

UnrealizedOrderTVDisplayer::UnrealizedOrderTVDisplayer(const QModelIndex & index, int role, TVModel const* model)
    : TVDisplayer(index,role, model)
{
}

QVariant UnrealizedOrderTVDisplayer::display() const
{
    if (isDisplayOrEditRole())
    {
        if(isPriceColumn())
            return displayPrice();
        else
            return model->baseData(index, role);
    }
    if(isTextAligmentRole())
    {
        if (isPriceColumn() || isDateColumn())
                return QVariant(Qt::AlignRight | Qt::AlignVCenter);
    }
    return QVariant();
}


bool UnrealizedOrderTVDisplayer::isPriceColumn() const {
    return index.column() == 4;
}

bool UnrealizedOrderTVDisplayer::isDateColumn() const {
    return (index.column() >= 2 && index.column() <= 3);
}

QVariant UnrealizedOrderTVDisplayer::displayPrice() const
{
    double value = model->baseData(index, role).toDouble();

    if(value == 0.0)
        return "0,00";
    else
        return Price(value).toString();
}
