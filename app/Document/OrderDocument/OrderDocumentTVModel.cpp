#include "OrderDocumentTVModel.h"

OrderDocumentTVModel::OrderDocumentTVModel()
{
    sortColumn=1;
    sortOrder=Qt::AscendingOrder;
    docTypeFilter = "";
    fromDateFilter = "";
    toDateFilter = "";
    docNotTypeFilter = "";

}

OrderDocumentTVModel::~OrderDocumentTVModel() {

}

void OrderDocumentTVModel::getDocuments() {
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    setQuery("SELECT id, type, symbol, COALESCE((SELECT symbol FROM contractors WHERE id_contractor = orders.contractor), ''), "
             "COALESCE((SELECT name FROM contractors WHERE id_contractor = orders.contractor), ''), document_date, realization_date, total "
                    "FROM orders "
                    "WHERE is_active = true AND warehouse = " + warehouseId.append(" ")
                    + docTypeFilter + fromDateFilter + toDateFilter + docNotTypeFilter + symbolFilter + sortOrdering, Database::getInstance().db);

    initHeaders();
}


void OrderDocumentTVModel::initHeaders()
{
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Typ"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Symbol kontrahenta"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("Nazwa kontrahenta"));
    this->setHeaderData(5, Qt::Horizontal, QObject::tr("Data wystawienia"));
    this->setHeaderData(6, Qt::Horizontal, QObject::tr("Data realizacji"));
    this->setHeaderData(7, Qt::Horizontal, QObject::tr("Wartość"));
}
