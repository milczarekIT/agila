#include "GoodsTVDisplayer.h"

GoodsTVDisplayer::GoodsTVDisplayer(const QModelIndex & index, int role, TVModel const* model) : TVDisplayer(index, role, model)
{
}

GoodsTVDisplayer::~GoodsTVDisplayer()
{
}

QVariant GoodsTVDisplayer::display() const
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
        if (isQuantityColumn() || isPriceColumn() || isTaxColumn())
                return QVariant(Qt::AlignRight | Qt::AlignVCenter);
    }
    return QVariant();
}

bool GoodsTVDisplayer::isQuantityColumn() const {
    return index.column() == 3;
}

bool GoodsTVDisplayer::isUnitColumn() const {
    return index.column() == 4;
}

bool GoodsTVDisplayer::isTaxColumn() const {
    return index.column() == 5;
}

bool GoodsTVDisplayer::isGoodsGroupColumn() const {
    return index.column() == 6;
}

bool GoodsTVDisplayer::isPriceColumn() const {
    return index.column() >= 7 && index.column() <= 14;
}

QVariant GoodsTVDisplayer::displayQuantity() const
{
    double value = model->baseData(index, role).toDouble();
    int idGood = getCellDataAtCol(COL_ID).toInt();

    GoodsService *goodsService = new GoodsService();
    int zeroPlaces = goodsService->getGood(idGood).getUnit().getZeroPlaces();
    delete goodsService;

    return QString::number(value, ',', zeroPlaces).replace(QRegExp("[.]"), ",");;
}


QVariant GoodsTVDisplayer::displayPrice() const
{
    double value = model->baseData(index, role).toDouble();

    if(value == 0.0)
        return "";
    else
        return QString::number(value, ',', 2).replace(QRegExp("[.]"), ",");
}
