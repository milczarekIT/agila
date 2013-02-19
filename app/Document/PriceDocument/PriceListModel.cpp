#include "PriceListModel.h"

PriceListModel::PriceListModel() : DocumentModel() {

}

PriceListModel::~PriceListModel() {

}

PriceList PriceListModel::getPriceList(QString symbol) {

    PriceList list;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT type, name, description, document_date, valid_from_date, valid_to_date "
                   "FROM price_lists WHERE symbol = ? AND is_active = true AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query)) {
        throw new SQLException("PriceListModel::getPriceList", query);
    }
    else if(query->size() > 0) {
        query->first();
        list.setDocumentType(query->value(0).toString());
        list.setSymbol(symbol);
        list.setDocumentName(query->value(1).toString());
        list.setDescribe(query->value(2).toString());
        list.setDocumentDate(query->value(3).toDate());
        list.setValidFromDate(query->value(4).toDate());
        list.setValidToDate(query->value(5).toDate());
    }

    delete query;
    return list;
}

void PriceListModel::addPriceList(PriceList list) {

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO price_lists (type, symbol, name, description, document_date, valid_from_date, "
                   "valid_to_date, warehouse) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    query->addBindValue(list.getDocumentType());
    query->addBindValue(list.getSymbol());
    query->addBindValue(list.getDocumentName());
    query->addBindValue(list.getDescribe());
    query->addBindValue(list.getDocumentDate().toString("yyyy-MM-dd"));
    query->addBindValue(list.getValidFromDate().toString("yyyy-MM-dd"));
    query->addBindValue(list.getValidToDate().toString("yyyy-MM-dd"));
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("PriceListModel::addPriceList", query);

    delete query;
}

void PriceListModel::editPriceList(PriceList newList) {

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE price_lists SET name = ?, description = ?, document_date = ?, valid_from_date = ?,"
                   "valid_to_date = ? WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(newList.getDocumentName());
    query->addBindValue(newList.getDescribe());
    query->addBindValue(newList.getDocumentDate());
    query->addBindValue(newList.getValidFromDate());
    query->addBindValue(newList.getValidToDate());
    query->addBindValue(newList.getSymbol());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("PriceListModel::editPriceList", query);

    delete query;
}

void PriceListModel::removePriceList(QString symbol) {

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE price_lists SET is_active = false WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("PriceListModel::removePriceList", query);

    delete query;
}
