#include "DocumentPZModel.h"

DocumentPZModel::DocumentPZModel() : DocumentModel()
{
}


DocumentPZ DocumentPZModel::getDocumentPZ(QString symbol)
{
    DocumentPZ document;
    ContractorService *conService = new ContractorService();
    TransportModel *transportModel = new TransportModel();
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT type, contractor, document_place, document_date, warehouse_date, total, receive_person, issue_person, transport, "
                   "warehouse_result, owner, warehouse "
                   "FROM warehouse_documents "
                   "WHERE symbol = ? AND warehouse = ?");

    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
         throw new SQLException("DocumentPZModel::getDocumentPZ", query);
    else if(query->size() > 0)
    {
        query->first();

        document.setDocumentType(query->value(0).toString());//
        document.setSymbol(symbol);
        document.setContractor(conService->getContractor(query->value(1).toInt()));
        document.setDocumentPlace(documentPlaceModel->getDocumentPlace(query->value(2).toInt()).getName());
        document.setDocumentDate(query->value(3).toDate());
        document.setStoreDate(query->value(4).toDate());
        document.setTotal(query->value(5).toFloat());
        document.setReceiveName(peopleModel->getName(query->value(6).toInt()));
        document.setIssueName(peopleModel->getName(query->value(7).toInt()));
        document.setTransport(transportModel->getMeanOfTransport(query->value(8).toInt()));
        document.setStoreResult(query->value(9).toBool());
        document.setOwnerId(query->value(10).toInt());
    }

    delete conService;
    delete transportModel;
    delete query;

    return document;
}

void DocumentPZModel::addDocumentPZ(DocumentPZ document)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO warehouse_documents (type, symbol, contractor, document_place, document_date, warehouse_date, total, "
                    "receive_person, issue_person, transport, warehouse_result, owner, warehouse) "
                        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query->addBindValue(document.getDocumentType());
    query->addBindValue(document.getSymbol());
    query->addBindValue(document.getContractor().getId());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(document.getDocumentPlace()));
    query->addBindValue(document.getDocumentDate().toString("yyyy-MM-dd"));
    query->addBindValue(document.getStoreDate().toString("yyyy-MM-dd"));
    query->addBindValue(document.getTotal());
    query->addBindValue(peopleModel->getPersonId(document.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(document.getIssueName()));
    query->addBindValue(document.getTransport().getId());
    query->addBindValue(document.getStoreResult());
    query->addBindValue(document.getOwnerId());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
         throw new SQLException("DocumentPZModel::addDocumentPZ", query);

    delete query;
}


void DocumentPZModel::editDocumentPZ(DocumentPZ newDocument)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE warehouse_documents SET type = ?, contractor = ?, document_place = ?, document_date = ?, warehouse_date = ?, total = ?, "
                    "receive_person = ?, issue_person = ?, transport = ?, warehouse_result = ? "
                    "WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(newDocument.getDocumentType());
    query->addBindValue(newDocument.getContractor().getId());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(newDocument.getDocumentPlace()));
    query->addBindValue(newDocument.getDocumentDate());
    query->addBindValue(newDocument.getStoreDate());
    query->addBindValue(newDocument.getTotal());
    query->addBindValue(peopleModel->getPersonId(newDocument.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(newDocument.getIssueName()));
    query->addBindValue(newDocument.getTransport().getId());
    query->addBindValue(newDocument.getStoreResult());
    query->addBindValue(newDocument.getSymbol());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentPZModel::editDocumentPZ", query);

    delete query;
}

void DocumentPZModel::removeDocument(QString symbol)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM warehouse_documents WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
         throw new SQLException("DocumentPZModel::removeDocument", query);

    delete query;
}
