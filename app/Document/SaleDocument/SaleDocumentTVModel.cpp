#include "SaleDocumentTVModel.h"

SaleDocumentTVModel::SaleDocumentTVModel()
{
}

SaleDocumentTVModel::~SaleDocumentTVModel() {}

void SaleDocumentTVModel::getDocuments()
{
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouse()->getId());
    this->setQuery("SELECT id, type, symbol, COALESCE((SELECT symbol FROM contractors WHERE id_contractor = sale_documents.contractor), ''), "
                    "COALESCE((SELECT name FROM contractors WHERE id_contractor = sale_documents.contractor), ''), document_date, sale_date, total "
                    "FROM sale_documents "
                    "WHERE is_active = true AND warehouse = " + warehouseId.append(" ")
                    + docTypeFilter + fromDateFilter + toDateFilter + docNotTypeFilter + symbolFilter
                    + sortOrdering, Database::getInstance().db);
    this->initHeaders();
}

void SaleDocumentTVModel::setDocTypeFilter(QString value)
{
    DocumentTVModel::setDocTypeFilter(value);
}


void SaleDocumentTVModel::setDocTypeFilter(QStringList value)
{
    if(value.size() == 0)
        docTypeFilter = "";
    else
    {
        docTypeFilter = "AND (";
        docTypeFilter.append("sale_documents.symbol LIKE '%" + value.at(0) + "%' ");
        for(int i = 1; i < value.size(); i++)
        {
            docTypeFilter.append("OR sale_documents.symbol LIKE '%" + value.at(i) + "%' ");
        }
        docTypeFilter.append(") ");

    }
}

void SaleDocumentTVModel::initHeaders()
{
    this->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Typ"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Symbol kontrahenta"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("Nazwa kontrahenta"));
    this->setHeaderData(5, Qt::Horizontal, QObject::tr("Data wystawienia"));
    this->setHeaderData(6, Qt::Horizontal, QObject::tr("Data sprzedaży"));
    this->setHeaderData(7, Qt::Horizontal, QObject::tr("Wartość"));
}


