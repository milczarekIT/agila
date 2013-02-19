#include "CurrentInventoryGroupsTVDisplayer.h"

CurrentInventoryGroupsTVDisplayer::CurrentInventoryGroupsTVDisplayer(const QModelIndex & index, int role, TVModel const* model)
    : TVDisplayer(index, role, model)
{
}

QVariant CurrentInventoryGroupsTVDisplayer::display() const
{
    if (isDisplayOrEditRole())
    {
        if (isQuantityColumn())
            return displayQuantity();
        else if(isGoodsGroupColumn())
            return displayGoodsGroup();
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

bool CurrentInventoryGroupsTVDisplayer::isQuantityColumn() const {
    return index.column() == 1;
}

bool CurrentInventoryGroupsTVDisplayer::isGoodsGroupColumn() const {
    return index.column() == 0;
}

bool CurrentInventoryGroupsTVDisplayer::isPriceColumn() const {
    return index.column() == 2;
}

//przeciążona
QVariant CurrentInventoryGroupsTVDisplayer::displayQuantity() const
{
    double value = model->baseData(index, role).toDouble();
    int zeroPlaces = 3;

    return QString::number(value, ',', zeroPlaces).replace(QRegExp("[.]"), ",");;
}

QVariant CurrentInventoryGroupsTVDisplayer::displayGoodsGroup() const
{
    int idGroup = model->baseData(index, role).toInt();

    if(idGroup == 0)
        return "BRAK";
    else
    {
        GoodsGroupModel *ggmodel = new GoodsGroupModel();
        QString groupName = ggmodel->getGoodsGroup(idGroup).getName();
        delete ggmodel;

        return groupName;
    }
}

QVariant CurrentInventoryGroupsTVDisplayer::displayPrice() const
{
    double value = model->baseData(index, role).toDouble();

    if(value == 0.0)
        return "0,00";
    else
        return QString::number(value, ',', 2).replace(QRegExp("[.]"), ",");
}

