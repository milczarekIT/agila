#include "CurrentInventoryTVModel.h"

CurrentInventoryTVModel::CurrentInventoryTVModel()
{
    sortColumn = 1;
    sortOrder = Qt::AscendingOrder;
    zeroQuantityFilter = "";
}

CurrentInventoryTVModel::~CurrentInventoryTVModel()
{
}


void CurrentInventoryTVModel::getData()
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    this->setQuery("SELECT id_good, symbol, name, goods_group, tax, quantity, unit, price_mag_net, quantity*price_mag_net AS value "
                   "FROM goods, wh_goods "
                   "WHERE goods.id_good = wh_goods.good AND wh_goods.is_active = true AND type = " + QString::number(Goods::GOOD) + " "
                   "AND wh_goods.warehouse = " + warehouseId.append(" ")
                   + zeroQuantityFilter +
                   "ORDER BY "+QString::number(sortColumn)+" "+((sortOrder==Qt::AscendingOrder) ? "DESC" : "ASC"), Database::getInstance().db);

    this->initHeaders();
}

Price CurrentInventoryTVModel::getValue()
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    QSqlQuery *query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT SUM(quantity*price_mag_net) AS value "
                         "FROM goods, wh_goods "
                        "WHERE goods.id_good = wh_goods.good AND wh_goods.warehouse = " +warehouseId.append(" ") +
                        "AND wh_goods.is_active = true AND type = " + QString::number(Goods::GOOD));
    query->exec();
    query->first();
    double value = query->value(0).toDouble();
    delete query;

    return Price(value);
}


void CurrentInventoryTVModel::initHeaders()
{
    this->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Nazwa"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Grupa towarowa"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("VAT"));
    this->setHeaderData(5, Qt::Horizontal, QObject::tr("Stan"));
    this->setHeaderData(6, Qt::Horizontal, QObject::tr("j.m."));
    this->setHeaderData(7, Qt::Horizontal, QObject::tr("Cena magazynowa netto"));
    this->setHeaderData(8, Qt::Horizontal, QObject::tr("Wartość magazynowa netto"));

}

QVariant CurrentInventoryTVModel::data(const QModelIndex & index, int role) const
{
    CurrentInventoryTVDisplayer displayer(index, role, this);
    return displayer.display();
}

QVariant CurrentInventoryTVModel::data(int row, int column, int role) {
    QModelIndex modelIndex = this->index(row, column);
    return data(modelIndex, role);
}

void CurrentInventoryTVModel::showWithZeroQuantityFilter() {
    zeroQuantityFilter = "";
}

void CurrentInventoryTVModel::dontShowWithZeroQuantityFilter() {
    zeroQuantityFilter = "AND quantity > 0 ";
}
