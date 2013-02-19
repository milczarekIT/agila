#include "DocumentFKModel.h"

DocumentFKModel::DocumentFKModel() : DocumentModel()
{
}

DocumentFK DocumentFKModel::getDocumentFK(QString symbol)
{
    DocumentFK fk;
    ContractorService *conService = new ContractorService();
    MOPModel *mopModel = new MOPModel();

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT type, contractor, method_of_payment, document_place, document_date, sale_date, payment_date, "
                   "total, discount, receive_person, issue_person, is_paid, warehouse_result, owner "
                   "FROM sale_documents "
                   "WHERE symbol = ? AND warehouse = ? "
                   "AND is_active = true");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
            throw new SQLException("DocumentFKModel::getDocumentFK", query);
    else if(query->size() > 0)
    {
        query->first();

        fk.setSymbol(symbol);
        fk.setDocumentType(query->value(0).toString());
        fk.setContractor(conService->getContractor(query->value(1).toInt()));
        fk.setMethodOfPayment(mopModel->getMethodOfPayment(query->value(2).toInt()));
        fk.setDocumentPlace(documentPlaceModel->getDocumentPlace(query->value(3).toInt()).getName());
        fk.setDocumentDate(query->value(4).toDate());
        fk.setSaleDate(query->value(5).toDate());
        fk.setPaymentDate(query->value(6).toDate());
        fk.setTotal(query->value(7).toDouble());
        fk.setDiscount(query->value(8).toDouble());
        fk.setReceiveName(peopleModel->getName(query->value(9).toInt()));
        fk.setIssueName(peopleModel->getName(query->value(10).toInt()));
        fk.setPaid(query->value(11).toInt());
        fk.setStoreResult(query->value(12).toBool());
        fk.setOwnerId(query->value(13).toInt());
    }
    delete conService;
    delete mopModel;

    delete query;

    return fk;
}

QString DocumentFKModel::getInvoiceSymbolByDocumentFK(QString documentFK)
{
    QString invoiceSymbol;

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT base_document FROM linked_documents WHERE linked_document = ? AND warehouse = ?");
    query->addBindValue(documentFK);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
            throw new SQLException("DocumentFKModel::getInvoiceSymbolByDocumentFK", query);
    else if(query->size() > 0)
    {
        query->first();
        invoiceSymbol = query->value(0).toString();
    }
    delete query;

    return invoiceSymbol;
}

void DocumentFKModel::addDocumentFK(DocumentFK fk)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO sale_documents (type, symbol, contractor, method_of_payment, document_place, "
                   "document_date, sale_date, payment_date, total, discount, order_symbol, receive_person, issue_person, is_paid, "
                   "warehouse_result, owner, warehouse) "
                       "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query->addBindValue(fk.getDocumentType());
    query->addBindValue(fk.getSymbol());
    query->addBindValue(fk.getContractor().getId());
    query->addBindValue(fk.getMethodOfPayment().getId());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(fk.getDocumentPlace()));
    query->addBindValue(fk.getDocumentDate().toString("yyyy-MM-dd"));
    query->addBindValue(fk.getSaleDate().toString("yyyy-MM-dd"));
    query->addBindValue(fk.getPaymentDate().toString("yyyy-MM-dd"));
    query->addBindValue(fk.getTotal());
    query->addBindValue(fk.getDiscount());
    query->addBindValue(fk.getOrder());
    query->addBindValue(peopleModel->getPersonId(fk.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(fk.getIssueName()));
    query->addBindValue(fk.isPaid());
    query->addBindValue(fk.getStoreResult());
    query->addBindValue(fk.getOwnerId());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentFKModel::addDocumentFK", query);

    delete query;
}

void DocumentFKModel::editDocumentFK(DocumentFK newFk)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE sale_documents SET type = ?, contractor = ?, method_of_payment = ?, document_place = ?, sale_date = ?, "
                   "payment_date = ?, total = ?, discount = ?, order_symbol = ?, receive_person = ?, issue_person = ?, is_paid = ?, warehouse_result = ? "
                   "WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(newFk.getDocumentType());
    query->addBindValue(newFk.getContractor().getId());
    query->addBindValue(newFk.getMethodOfPayment().getId());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(newFk.getDocumentPlace()));
    query->addBindValue(newFk.getSaleDate());
    query->addBindValue(newFk.getPaymentDate());
    query->addBindValue(newFk.getTotal());
    query->addBindValue(newFk.getDiscount());
    query->addBindValue(newFk.getOrder());
    query->addBindValue(peopleModel->getPersonId(newFk.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(newFk.getIssueName()));
    query->addBindValue(newFk.isPaid());
    query->addBindValue(newFk.getStoreResult());
    query->addBindValue(newFk.getSymbol());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentFKModel::editDocumentFK", query);

    delete query;
}

void DocumentFKModel::removeDocumentFK(QString symbol)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM sale_documents WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentFKModel::removeDocumentFK", query);

    delete query;
}

