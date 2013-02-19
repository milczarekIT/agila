#include "PurchaseDocumentTVModel.h"

PurchaseDocumentTVModel::PurchaseDocumentTVModel()
{

}

/** musi być kolumna id i type przy wykorzystaniu UNION bo po tym sortuje symbol @see DocumentTVModel::sort(column, order) */
void PurchaseDocumentTVModel::getDocuments()
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    this->setQuery("SELECT id, type, symbol, COALESCE((SELECT symbol FROM contractors WHERE id_contractor = purchase_documents.contractor), ''), "
                   "COALESCE((SELECT name FROM contractors WHERE id_contractor = purchase_documents.contractor), ''), document_date, purchase_date, total "
                    "FROM purchase_documents "
                    "WHERE is_active = true AND warehouse = " + warehouseId.append(" ")
                    + docTypeFilter + fromDateFilter + toDateFilter + docNotTypeFilter + symbolFilter +
                    "UNION "
                    "SELECT id, type, symbol, COALESCE((SELECT symbol FROM contractors WHERE id_contractor = documents_nk.contractor), ''), "
                   "COALESCE((SELECT name FROM contractors WHERE id_contractor = documents_nk.contractor), ''), document_date, document_date, 0.0  "
                    "FROM documents_nk "
                    "WHERE is_active = true AND warehouse = " + warehouseId.append(" ")
                    + docTypeFilter + fromDateFilter + toDateFilter + docNotTypeFilter + symbolFilter + sortOrdering, Database::getInstance().db);

    this->initHeaders();

}

void PurchaseDocumentTVModel::initHeaders()
{
    this->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Typ"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Symbol kontrahenta"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("Nazwa kontrahenta"));
    this->setHeaderData(5, Qt::Horizontal, QObject::tr("Data wystawienia"));
    this->setHeaderData(6, Qt::Horizontal, QObject::tr("Data zakupu"));
    this->setHeaderData(7, Qt::Horizontal, QObject::tr("Wartość"));


}

PurchaseDocumentTVModel::~PurchaseDocumentTVModel()
{
}
