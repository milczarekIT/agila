#include "UnpaidDocumentTVModel.h"

UnpaidDocumentTVModel::UnpaidDocumentTVModel()
{
    notOnTimeFilter = "";
}

UnpaidDocumentTVModel::~UnpaidDocumentTVModel()
{
}


void UnpaidDocumentTVModel::getUnpaidSaleDocuments() {
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouseId());
    this->setQuery("SELECT sale_documents.symbol,  contractors.name, sale_date, payment_date, total, payment_date::DATE - 'now'::DATE as days_to_payment "
                   "FROM sale_documents, contractors "
                   "WHERE contractors.id_contractor = sale_documents.contractor AND is_paid = false AND sale_documents.is_active = true " + notOnTimeFilter +
                   "AND sale_documents.warehouse = " + warehouseId + " " +
                   "ORDER BY "+QString::number(sortColumn)+" "+((sortOrder==Qt::AscendingOrder) ? "DESC" : "ASC"), Database::getInstance().db);

    this->initUnpaidSaleDocumentsHeaders();
}

Price UnpaidDocumentTVModel::getUnpaidSaleValue() {
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouseId());
    QSqlQuery *query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT SUM(total) AS value "
                         "FROM sale_documents "
                         "WHERE is_active = true AND is_paid = false " + notOnTimeFilter +
                         "AND sale_documents.warehouse = " + warehouseId);
    query->exec();
    query->first();
    double value = query->value(0).toDouble();

    delete query;

    return Price(value);
}

void UnpaidDocumentTVModel::getUnpaidPurchaseDocuments() {
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouseId());
    this->setQuery("SELECT purchase_documents.symbol,  contractors.name, purchase_date, payment_date, total, payment_date::DATE - 'now'::DATE as days_to_payment "
                   "FROM purchase_documents, contractors "
                   "WHERE contractors.id_contractor = purchase_documents.contractor AND is_paid = false  AND purchase_documents.is_active = true " + notOnTimeFilter +
                   "AND purchase_documents.warehouse = " + warehouseId + " "
                   "ORDER BY "+QString::number(sortColumn)+" "+((sortOrder==Qt::AscendingOrder) ? "DESC" : "ASC"), Database::getInstance().db);

    this->initUnpaidPurchaseDocumentsHeaders();
}

Price UnpaidDocumentTVModel::getUnpaidPurchaseDocumentsValue() {
    QString warehouseId = QString::number(ApplicationManager::getInstance()->getWarehouseId());
    QSqlQuery *query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT SUM(total) AS value "
                         "FROM purchase_documents "
                         "WHERE is_active = true AND is_paid = false " + notOnTimeFilter +
                         "AND purchase_documents.warehouse = " + warehouseId);
    query->exec();
    query->first();
    double value = query->value(0).toDouble();

    delete query;

    return Price(value);
}

void UnpaidDocumentTVModel::initUnpaidSaleDocumentsHeaders()
{
    this->setHeaderData(0, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Kontrahent"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Data sprzedaży"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Data płatności"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("Wartość"));
    this->setHeaderData(5, Qt::Horizontal, QObject::tr("Pozostało dni do zapł."));
}

void UnpaidDocumentTVModel::initUnpaidPurchaseDocumentsHeaders()
{
    this->setHeaderData(0, Qt::Horizontal, QObject::tr("Symbol"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Kontrahent"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Data zakupu"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Data płatności"));
    this->setHeaderData(4, Qt::Horizontal, QObject::tr("Wartość"));
    this->setHeaderData(5, Qt::Horizontal, QObject::tr("Pozostało dni do zapł."));
}

void UnpaidDocumentTVModel::initHeaders()
{
    /* @see UnpaidDocumentTVModel::initUnpaidSaleDocumentsHeaders()
            UnpaidDocumentTVModel::initUnpaidPurchaseDocumentsHeaders() */
}

QVariant UnpaidDocumentTVModel::data(const QModelIndex & index, int role) const
{
    UnpaidDocumentTVDisplayer displayer(index, role, this);
    return displayer.display();
}

void UnpaidDocumentTVModel::notOnTimeFilterOnly()
{
    notOnTimeFilter = "AND payment_date::DATE <= 'now'::DATE ";
}

void UnpaidDocumentTVModel::resetOnTimeFilter()
{
    notOnTimeFilter = "";
}
