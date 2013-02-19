#include "CashDocumentModel.h"

CashDocumentModel::CashDocumentModel() : DocumentModel()
{
}


CashDocument CashDocumentModel::getCashDocument(QString symbol)
{
    CashDocument document;
    ContractorService *conService = new ContractorService();
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT contractor, document_place, value, document_date, payment_date, document, title, receive_person, issue_person, "
                   "description, owner "
                    "FROM cash_documents "
                    "WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentKPModel::getDocumentKP", query);
    else if(query->size() > 0)
    {
        query->first();

        document.setSymbol(symbol);
        document.setContractor(conService->getContractor(query->value(0).toInt()));
        document.setDocumentPlace(documentPlaceModel->getDocumentPlace(query->value(1).toInt()).getName());
        document.setTotal(query->value(2).toDouble());
        document.setDocumentDate(query->value(3).toDate());
        document.setPaymentDate(query->value(4).toDate());
        document.setBaseDocumentSymbol(query->value(5).toString());
        document.setTitle(query->value(6).toString());
        document.setReceiveName(peopleModel->getName(query->value(7).toInt()));
        document.setIssueName(peopleModel->getName(query->value(8).toInt()));
        document.setDescription(query->value(9).toString());
        document.setOwnerId(query->value(10).toInt());
    }

    delete query;

    return document;
}

void CashDocumentModel::addCashDocument(CashDocument document)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO cash_documents (type, symbol, contractor, document_place, value, document_date, payment_date, "
                    "document, title, receive_person, issue_person, description, owner, warehouse) "
                    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query->addBindValue(document.getDocumentType());
    query->addBindValue(document.getSymbol());
    query->addBindValue(document.getContractor().getId());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(document.getDocumentPlace()));
    query->addBindValue(document.getTotal());
    query->addBindValue(document.getDocumentDate());
    query->addBindValue(document.getPaymentDate());
    query->addBindValue(document.getBaseDocumentSymbol());
    query->addBindValue(document.getTitle());
    query->addBindValue(peopleModel->getPersonId(document.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(document.getIssueName()));
    query->addBindValue(document.getDescription());
    query->addBindValue(document.getOwnerId());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentKPModel::addDocumentKP", query);

    delete query;

}

void CashDocumentModel::editCashDocument(CashDocument newDocument)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE cash_documents "
                    "SET contractor = ?, document_place = ?, value = ?, document_date = ?, payment_date = ?, title = ?, "
                    "document = ?, receive_person = ?, issue_person = ?, description = ? "
                    "WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(newDocument.getContractor().getId());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(newDocument.getDocumentPlace()));
    query->addBindValue(newDocument.getTotal());
    query->addBindValue(newDocument.getDocumentDate());
    query->addBindValue(newDocument.getPaymentDate());
    query->addBindValue(newDocument.getTitle());
    query->addBindValue(newDocument.getBaseDocumentSymbol());
    query->addBindValue(peopleModel->getPersonId(newDocument.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(newDocument.getIssueName()));
    query->addBindValue(newDocument.getDescription());
    query->addBindValue(newDocument.getSymbol());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentKPModel::editDocumentKP", query);

    delete query;
}

void CashDocumentModel::removeCashDocument(QString symbol)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM cash_documents WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentKPModel::removeDocumentKP", query);

    delete query;
}
