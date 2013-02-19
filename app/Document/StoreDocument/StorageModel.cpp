#include "StorageModel.h"

StorageModel::StorageModel()
{
}


StoreDocument StorageModel::getStoreDocument(QString symbol)
{
    StoreDocument document;
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT type, document_place, document_date, total, issue_person, department, warehouse_result, owner  "
                    "FROM warehouse_documents "
                    "WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("StorageModel::getStoreDocument", query);
    else if(query->size() > 0)
    {
        DepartmentModel *departmentModel = new DepartmentModel();
        query->first();

        document.setDocumentType(query->value(0).toString());
        document.setSymbol(symbol);
        document.setDocumentPlace(documentPlaceModel->getDocumentPlace(query->value(1).toInt()).getName());
        document.setDocumentDate(query->value(2).toDate());
        document.setTotal(query->value(3).toFloat());
        document.setIssueName(peopleModel->getName(query->value(4).toInt()));
        document.setDepartment(departmentModel->getDepartment(query->value(5).toInt()));
        document.setStoreResult(query->value(6).toBool());
        document.setOwnerId(query->value(7).toInt());

        delete departmentModel;
    }
    delete query;


    return document;
}

void StorageModel::addStoreDocument(StoreDocument document)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO warehouse_documents (type, symbol, document_place, document_date, total, "
                    "issue_person, department, warehouse_result, owner, warehouse) "
                        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    query->addBindValue(document.getDocumentType());
    query->addBindValue(document.getSymbol());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(document.getDocumentPlace()));
    query->addBindValue(document.getDocumentDate().toString("yyyy-MM-dd"));
    query->addBindValue(document.getTotal());
    query->addBindValue(peopleModel->getPersonId(document.getIssueName()));
    query->addBindValue(document.getDepartment().getId());
    query->addBindValue(document.getStoreResult());
    query->addBindValue(document.getOwnerId());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("StorageModel::addStoreDocument", query);

    delete query;
}

void StorageModel::editStoreDocument(StoreDocument newDocument)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE warehouse_documents SET type = ?, document_place = ?, document_date = ?, total = ?, "
                    "issue_person = ?, department = ?, warehouse_result = ? "
                    "WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(newDocument.getDocumentType());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(newDocument.getDocumentPlace()));
    query->addBindValue(newDocument.getDocumentDate());
    query->addBindValue(newDocument.getTotal());
    query->addBindValue(peopleModel->getPersonId(newDocument.getIssueName()));
    query->addBindValue(newDocument.getDepartment().getId());
    query->addBindValue(newDocument.getStoreResult());
    query->addBindValue(newDocument.getSymbol());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("StorageModel::editStoreDocument", query);

    delete query;
}

void StorageModel::removeDocument(QString symbol)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM warehouse_documents WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("StorageModel::removeDocument", query);

    delete query;

}
