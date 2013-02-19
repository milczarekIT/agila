#include "CurrentInventoryTVDisplayer.h"

CurrentInventoryTVDisplayer::CurrentInventoryTVDisplayer(const QModelIndex & index, int role, TVModel const* model) : TVDisplayer(index, role, model)
{
}

QVariant CurrentInventoryTVDisplayer::display() const
{
    if (isDisplayOrEditRole())
    {
        if (isQuantityColumn())
            return displayQuantity();
        else if(isUnitColumn())
            return displayUnit();
        else if(isTaxColumn())
            return displayTax();
        else if(isGoodsGroupColumn())
            return displayGoodsGroup();
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

bool CurrentInventoryTVDisplayer::isQuantityColumn() const {
    return index.column() == 5;
}

bool CurrentInventoryTVDisplayer::isUnitColumn() const {
    return index.column() == 6;
}

bool CurrentInventoryTVDisplayer::isTaxColumn() const {
    return index.column() == 4;
}

bool CurrentInventoryTVDisplayer::isGoodsGroupColumn() const {
    return index.column() == 3;
}

bool CurrentInventoryTVDisplayer::isPriceColumn() const {
    return index.column() >= 7 && index.column() <= 8;
}

QVariant CurrentInventoryTVDisplayer::displayQuantity() const
{
    double value = model->baseData(index, role).toDouble();
    int idGood = getCellDataAtCol(COL_ID).toInt();

    GoodsService *goodsService = new GoodsService();
    int zeroPlaces = goodsService->getGood(idGood).getUnit().getZeroPlaces();
    delete goodsService;

    return QString::number(value, ',', zeroPlaces).replace(QRegExp("[.]"), ",");
}

QVariant CurrentInventoryTVDisplayer::displayUnit() const
{
    int idUnit = model->baseData(index, role).toInt();

    if(idUnit == 0)
        return "-";
    else
    {
        UnitModel *unitModel = new UnitModel();
        QString unitName = unitModel->getUnit(idUnit).getName();
        delete unitModel;

        return unitName;
    }
}

QVariant CurrentInventoryTVDisplayer::displayTax() const
{
    int idTax = model->baseData(index, role).toInt();

    TaxModel *taxModel = new TaxModel();
    Tax tax = taxModel->getTax(idTax);
    delete taxModel;

    return tax.getShortName();
}

QVariant CurrentInventoryTVDisplayer::displayGoodsGroup() const
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

QVariant CurrentInventoryTVDisplayer::displayPrice() const
{
    double value = model->baseData(index, role).toDouble();

    if(value == 0.0)
        return "0,00";
    else
        return QString::number(value, ',', 2).replace(QRegExp("[.]"), ",");
}
