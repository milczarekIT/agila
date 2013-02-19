#include "PriceDocumentTVModel.h"

PriceDocumentTVModel::PriceDocumentTVModel() {
}

PriceDocumentTVModel::~PriceDocumentTVModel() {
}

void PriceDocumentTVModel::getDocuments()
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    this->setQuery("SELECT id, type, symbol, name, document_date, valid_from_date, valid_to_date, description from price_lists "
                   "WHERE is_active = true  AND warehouse = " + warehouseId.append(" ")
                   + docTypeFilter + fromDateFilter + toDateFilter + docNotTypeFilter
                   + symbolFilter + sortOrdering, Database::getInstance().db);
    this->initHeaders();
}

void PriceDocumentTVModel::setDocTypeFilter(QString value) {
    DocumentTVModel::setDocTypeFilter(value);
}

void PriceDocumentTVModel::setDocTypeFilter(QStringList value)
{
    if(value.size() == 0) {

        docTypeFilter = "";

    } else {

        docTypeFilter = "AND (";
        docTypeFilter.append("price_lists.symbol LIKE '%" + value.at(0) + "%' ");

        for(int i = 1; i < value.size(); i++) {
            docTypeFilter.append("OR price_lists.symbol LIKE '%" + value.at(i) + "%' ");
        }

        docTypeFilter.append(") ");
    }
}

void PriceDocumentTVModel::initHeaders()
{
    int i = 0;
    this->setHeaderData(i++, Qt::Horizontal, QObject::tr("id"));
    this->setHeaderData(i++, Qt::Horizontal, QObject::tr("Typ"));
    this->setHeaderData(i++, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(i++, Qt::Horizontal, QObject::tr("Nazwa"));
    this->setHeaderData(i++, Qt::Horizontal, QObject::tr("Data wystawienia"));
    this->setHeaderData(i++, Qt::Horizontal, QObject::tr("Obowiązuje od"));
    this->setHeaderData(i++, Qt::Horizontal, QObject::tr("Obowiązuje do"));
    this->setHeaderData(i++, Qt::Horizontal, QObject::tr("Opis"));
}
