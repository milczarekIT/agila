#include "ReportGoodsTVModel.h"

ReportGoodsTVModel::ReportGoodsTVModel()
{
    quantityFilter = "AND quantity <= 0 ";
}

ReportGoodsTVModel::~ReportGoodsTVModel() {}

void ReportGoodsTVModel::getData()
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    this->setQuery("SELECT id_good, symbol, name, quantity, COALESCE((SELECT name FROM units WHERE id_unit = goods.unit), ''), "
                    "COALESCE((SELECT name FROM goods_groups WHERE id_group = goods.goods_group), 'BRAK'), "
                        "price_a_net, price_a_gross "
                    "FROM goods, wh_goods "
                    "WHERE goods.id_good = wh_goods.good AND wh_goods.warehouse = " + warehouseId.append(" ") +
                    "AND wh_goods.is_active = true " + quantityFilter +
                    "ORDER BY "+QString::number(sortColumn)+" "+((sortOrder==Qt::AscendingOrder) ? "DESC" : "ASC"), Database::getInstance().db);

    this->initHeaders();
}

void ReportGoodsTVModel::initHeaders()
{
    this->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Nazwa"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Ilość"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("j.m."));
    this->setHeaderData(5, Qt::Horizontal, QObject::tr("Grupa towarowa"));
    this->setHeaderData(6, Qt::Horizontal, QObject::tr("Cena netto"));
    this->setHeaderData(7, Qt::Horizontal, QObject::tr("Cena brutto"));
}

QVariant ReportGoodsTVModel::data(const QModelIndex & index, int role) const
{
    ReportGoodsTVDisplayer displayer(index, role, this);
    return displayer.display();
}

QVariant ReportGoodsTVModel::data(int row, int column, int role) {
    QModelIndex modelIndex = this->index(row, column);
    return data(modelIndex, role);
}

void ReportGoodsTVModel::setQuantityFilter(double value)
{
    quantityFilter = "AND quantity <= " + QString::number(value) + " ";
}
