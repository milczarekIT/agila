#include "TopContractorsTVModel.h"

TopContractorsTVModel::TopContractorsTVModel()
{
    limit = 0;
    fromDateFilter = "";
    toDateFilter = "";
}

void TopContractorsTVModel::getData()
{
    this->setQuery("SELECT DISTINCT c.id_contractor, c.symbol, c.name, c.contractor_group, "
                   "((COALESCE((SELECT SUM(total) "
                                "FROM sale_documents "
                                "WHERE sale_documents.type IN (SELECT type FROM documents "
                                                                "WHERE family = 'SALE' AND NOT type IN ('FK', 'ZAL')) "
                                + fromDateFilter + toDateFilter +
                                "AND contractor  = c.id_contractor), 0)) + "
                   "(COALESCE((SELECT SUM(((SELECT total FROM sale_documents "
                                        "WHERE symbol = ld.linked_document)-(SELECT total FROM sale_documents "
                                                                            "WHERE symbol = ld.base_document))) as roznicaFK "
                            "FROM linked_documents ld, sale_documents "
                            "WHERE linked_document IN (SELECT symbol as symbol_FK FROM sale_documents WHERE type IN (SELECT type FROM documents WHERE family = 'SALE' AND type IN ('FK', 'ZAL') )) "
                            "AND ld.linked_document = sale_documents.symbol "
                            + fromDateFilter + toDateFilter +
                            "AND sale_documents.contractor = c.id_contractor), 0))) as total "
                   "FROM contractors c, sale_documents sd "
                   "WHERE ((COALESCE((SELECT SUM(total) "
                                   "FROM sale_documents "
                                   "WHERE sale_documents.type IN (SELECT type FROM documents "
                                                                   "WHERE family = 'SALE' AND NOT type IN ('FK', 'ZAL')) "
                                    + fromDateFilter + toDateFilter +
                                   "AND contractor  = c.id_contractor), 0)) + "
                          "(COALESCE((SELECT SUM(((SELECT total FROM sale_documents "
                                               "WHERE symbol = ld.linked_document)-(SELECT total FROM sale_documents "
                                                                                   "WHERE symbol = ld.base_document))) as roznicaFK "
                                   "FROM linked_documents ld, sale_documents "
                                   "WHERE linked_document IN (SELECT symbol as symbol_FK FROM sale_documents WHERE type IN (SELECT type FROM documents WHERE family = 'SALE' AND type IN ('FK', 'ZAL') )) "
                                    + fromDateFilter + toDateFilter +
                                    "AND ld.linked_document = sale_documents.symbol "
                                   "AND sale_documents.contractor = c.id_contractor), 0))) > 0 "
                   "AND c.id_contractor = sd.contractor "
                   "AND (c.type = " + QString::number(Contractor::BUYER) + " OR c.type = " +  QString::number(Contractor::BUYER|Contractor::SUPPLIER) +") "
                   "AND c.is_active = true "
                   "ORDER BY total DESC, c.name ASC "
                   "LIMIT " + QString::number(limit), Database::getInstance().db);

    this->initHeaders();
}

void TopContractorsTVModel::initHeaders()
{
    this->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Nazwa"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Grupa kontrahencka"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("Wartość sprzedaży"));
}

QVariant TopContractorsTVModel::data(const QModelIndex & index, int role) const
{
    TopContractorsTVDisplayer displayer(index, role, this);
    return displayer.display();
}

QVariant TopContractorsTVModel::data(int row, int column, int role) {
    QModelIndex modelIndex = this->index(row, column);
    return data(modelIndex, role);
}

void TopContractorsTVModel::setListLimitFilter(int limit)
{
    this->limit = limit;
}

void TopContractorsTVModel::setDateFromFilter(QDate fromDate)
{
    this->fromDateFilter = "AND sale_date::DATE >= '" + fromDate.toString("yyyy-MM-dd") + "'::DATE ";
}

void TopContractorsTVModel::setDateToFilter(QDate toDate)
{
    this->toDateFilter = "AND sale_date::DATE <= '" + toDate.toString("yyyy-MM-dd") + "'::DATE ";
}
