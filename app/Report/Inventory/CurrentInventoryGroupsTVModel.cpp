#include "CurrentInventoryGroupsTVModel.h"

CurrentInventoryGroupsTVModel::CurrentInventoryGroupsTVModel()
{
    zeroQuantityFilter = "";
    sortColumn = 1;
    sortOrder = Qt::AscendingOrder;
}

CurrentInventoryGroupsTVModel::~CurrentInventoryGroupsTVModel()
{
}


void CurrentInventoryGroupsTVModel::getData()
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    this->setQuery("SELECT goods_group, SUM(quantity) as SUMA, SUM(quantity*price_mag_net) "
                   "FROM goods, wh_goods "
                   "WHERE type = 1 AND wh_goods.is_active=true "
                   "AND wh_goods.good = goods.id_good AND wh_goods.warehouse = " + warehouseId.append(" ") +
                   "GROUP BY goods_group " + zeroQuantityFilter +
                   "ORDER BY "+QString::number(sortColumn)+" "+((sortOrder==Qt::AscendingOrder) ? "DESC" : "ASC"), Database::getInstance().db);

    this->initHeaders();
}

Price CurrentInventoryGroupsTVModel::getValue()
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    QSqlQuery *query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT SUM(quantity*price_mag_net) AS value "
                     "FROM goods, wh_goods "
                     "WHERE wh_goods.is_active = true AND type = 1 "
                     "AND wh_goods.good = goods.id_good AND wh_goods.warehouse = " + warehouseId);
    query->exec();
    query->first();
    double value = query->value(0).toDouble();

    delete query;
    return Price(value);
}


void CurrentInventoryGroupsTVModel::initHeaders()
{
    this->setHeaderData(0, Qt::Horizontal, QObject::tr("Grupa towarowa"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Stan"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Wartość magazynowa netto"));
}

QVariant CurrentInventoryGroupsTVModel::data(const QModelIndex & index, int role) const
{
    CurrentInventoryGroupsTVDisplayer displayer(index, role, this);
    return displayer.display();
}

void CurrentInventoryGroupsTVModel::showWithZeroQuantityFilter() {
    zeroQuantityFilter = "";
}

void CurrentInventoryGroupsTVModel::dontShowWithZeroQuantityFilter() {
    zeroQuantityFilter = "HAVING SUM(quantity) > 0 ";
}
