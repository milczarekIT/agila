#include "UnpaidDocumentTVDisplayer.h"

UnpaidDocumentTVDisplayer::UnpaidDocumentTVDisplayer(const QModelIndex & index, int role, TVModel const* model) : TVDisplayer(index, role, model)
{
}

QVariant UnpaidDocumentTVDisplayer::display() const
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
        if (isDaysToPay() || isPriceColumn() || isDateColumn())
                return QVariant(Qt::AlignRight | Qt::AlignVCenter);
    }
    return QVariant();
}

bool UnpaidDocumentTVDisplayer::isDaysToPay() const {
    return index.column() == 5;
}

bool UnpaidDocumentTVDisplayer::isPriceColumn() const {
    return index.column() == 4;
}

bool UnpaidDocumentTVDisplayer::isDateColumn() const {
    return (index.column() >= 2 && index.column() <= 3);
}

QVariant UnpaidDocumentTVDisplayer::displayPrice() const
{
    double value = model->baseData(index, role).toDouble();

    if(value == 0.0)
        return "0,00";
    else
        return Price(value).toString();
}
