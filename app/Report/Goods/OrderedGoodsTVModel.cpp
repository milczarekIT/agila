#include "OrderedGoodsTVModel.h"

OrderedGoodsTVModel::OrderedGoodsTVModel(QString type)
{
    this->type = type;

    if(type == "ZK")
    {
        priceNetColumnName = "price_a_net";
        priceGrossColumnName = "price_a_gross";
    }
    else if(type == "ZD")
    {
        priceNetColumnName = "price_mag_net";
        priceGrossColumnName = "price_mag_gross";
    }
}

void OrderedGoodsTVModel::getData()
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    this->setQuery("SELECT g.id_good, g.symbol, g.name, wh.quantity, SUM(dp.quantity) AS zamowiono, COALESCE((SELECT name FROM units WHERE id_unit = g.unit), '-'), g." + priceNetColumnName + ", "
                   "g." + priceGrossColumnName +", g." + priceNetColumnName + "* SUM(dp.quantity) AS wartosc_netto "
                   "FROM documents_positions dp, orders o, goods g, wh_goods wh "
                   "WHERE dp.document = o.symbol "
                   "AND g.id_good = wh.good AND wh.warehouse = " + warehouseId.append(" ") +
                   "AND o.warehouse = " + warehouseId.append(" ") +
                   "AND g.id_good = dp.good AND o.is_active = true AND o.type = '" + type + "' AND o.realized = 0 "
                   "GROUP BY g.id_good, wh.quantity  "
                   "ORDER BY "+QString::number(sortColumn)+" "+((sortOrder==Qt::AscendingOrder) ? "DESC" : "ASC"), Database::getInstance().db);

    this->initHeaders();
}

void OrderedGoodsTVModel::initHeaders()
{
    this->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Nazwa"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Stan"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("Zamówiono"));
    this->setHeaderData(5, Qt::Horizontal, QObject::tr("j.m."));
    if(type == "ZK")
    {
        this->setHeaderData(6, Qt::Horizontal, QObject::tr("Cena sprz. netto"));
        this->setHeaderData(7, Qt::Horizontal, QObject::tr("Cena sprz. brutto"));
    } else if(type == "ZD") {
        this->setHeaderData(6, Qt::Horizontal, QObject::tr("Cena zak. netto"));
        this->setHeaderData(7, Qt::Horizontal, QObject::tr("Cena zak. brutto"));
    }
    this->setHeaderData(8, Qt::Horizontal, QObject::tr("Wartość netto"));
}

QVariant OrderedGoodsTVModel::data(const QModelIndex & index, int role) const
{
    OrderedGoodsTVDisplayer displayer(index, role, this);
    return displayer.display();
}

QVariant OrderedGoodsTVModel::data(int row, int column, int role) {
    QModelIndex modelIndex = this->index(row, column);
    return data(modelIndex, role);
}
