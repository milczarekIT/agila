#include "UnrealizedOrderTVModel.h"

UnrealizedOrderTVModel::UnrealizedOrderTVModel(QString type)
{
    this->type = type;
    this->sortColumn = 4;
}

UnrealizedOrderTVModel::~UnrealizedOrderTVModel()
{

}


void UnrealizedOrderTVModel::getData()
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouseId());
    this->setQuery("SELECT symbol, COALESCE((SELECT name FROM contractors WHERE id_contractor = orders.contractor), ''), document_date, realization_date, total "
                   "FROM orders "
                   "WHERE type = '" + type + "' "
                   "AND is_active  = true "
                   "AND realized = 0 "
                   "AND warehouse = " + warehouseId + " " +
                   "ORDER BY "+QString::number(sortColumn)+" "+((sortOrder==Qt::AscendingOrder) ? "DESC" : "ASC"), Database::getInstance().db);

    this->initHeaders();
}

Price UnrealizedOrderTVModel::getValue()
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouseId());
    QSqlQuery query("SELECT SUM(total) AS value "
                    "FROM orders "
                    "WHERE is_active = true AND realized = 0 AND type ='" + type + "'"
                    "AND orders.warehouse = " + warehouseId, Database::getInstance().db);
    query.exec();
    query.first();
    double value = query.value(0).toDouble();

    return Price(value);
}

void UnrealizedOrderTVModel::initHeaders()
{
    this->setHeaderData(0, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Nazwa"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Data zamówienia"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Data realiazcji"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("Wartość brutto"));
}

QVariant UnrealizedOrderTVModel::data(const QModelIndex & index, int role) const
{
    UnrealizedOrderTVDisplayer displayer(index, role, this);
    return displayer.display();
}
