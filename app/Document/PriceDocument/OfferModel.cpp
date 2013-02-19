#include "OfferModel.h"

OfferModel::OfferModel()
{
}

OfferModel::~OfferModel() {
}

PriceList OfferModel::getOffer(QString symbol) {

    PriceList list;
    ContractorService *conService = new ContractorService();
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT type, document_date, valid_from_date, valid_to_date, contractor "
                   "FROM price_lists WHERE symbol = ? AND is_active = true AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query)) {
        throw new SQLException("OfferModel::getOffer", query);
    }
    else if(query->size() > 0) {
        query->first();
        list.setDocumentType(query->value(0).toString());
        list.setSymbol(symbol);
        list.setDocumentDate(query->value(1).toDate());
        list.setValidFromDate(query->value(2).toDate());
        list.setValidToDate(query->value(3).toDate());
        list.setContractor(conService->getContractor(query->value(4).toInt()));
    }

    delete query;
    delete conService;
    return list;
}

void OfferModel::addOffer(PriceList list) {

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO price_lists (type, symbol, document_date, valid_from_date, "
                   "valid_to_date, contractor, warehouse) VALUES (?, ?, ?, ?, ?, ?, ?)");
    query->addBindValue(list.getDocumentType());
    query->addBindValue(list.getSymbol());
    query->addBindValue(list.getDocumentDate().toString("yyyy-MM-dd"));
    query->addBindValue(list.getValidFromDate().toString("yyyy-MM-dd"));
    query->addBindValue(list.getValidToDate().toString("yyyy-MM-dd"));
    query->addBindValue(list.getContractor().getId());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("OfferModel::addOffer", query);

    delete query;
}

void OfferModel::editOffer(PriceList newList) {

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE price_lists SET document_date = ?, valid_from_date = ?, valid_to_date = ?, "
                   "contractor = ? WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(newList.getDocumentDate());
    query->addBindValue(newList.getValidFromDate());
    query->addBindValue(newList.getValidToDate());
    query->addBindValue(newList.getContractor().getId());
    query->addBindValue(newList.getSymbol());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("OfferModel::editOffer", query);

    delete query;
}

void OfferModel::removeOffer(QString symbol) {

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE price_lists SET is_active = false WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("OfferModel::removeOffer", query);

    delete query;
}
