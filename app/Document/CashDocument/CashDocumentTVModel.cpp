#include "CashDocumentTVModel.h"

CashDocumentTVModel::CashDocumentTVModel()
{
}

CashDocumentTVModel::~CashDocumentTVModel() {

}

void CashDocumentTVModel::getDocuments()
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    this->setQuery("SELECT id, type, symbol, COALESCE((SELECT symbol FROM contractors WHERE id_contractor = cash_documents.contractor), ''), "
                   "COALESCE((SELECT name FROM contractors WHERE id_contractor = cash_documents.contractor), ''), document_date, payment_date, value "
                    "FROM cash_documents "
                    "WHERE is_active = true AND warehouse = " + warehouseId.append(" ")
                    + docTypeFilter + fromDateFilter + toDateFilter + docNotTypeFilter + symbolFilter + sortOrdering, Database::getInstance().db);

    this->initHeaders();
}

void CashDocumentTVModel::initHeaders()
{
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Typ"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Symbol kontrahenta"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("Nazwa kontrahenta"));
    this->setHeaderData(5, Qt::Horizontal, QObject::tr("Data wystawienia"));
    this->setHeaderData(6, Qt::Horizontal, QObject::tr("Data płatności"));
    this->setHeaderData(7, Qt::Horizontal, QObject::tr("Wartość"));
}
