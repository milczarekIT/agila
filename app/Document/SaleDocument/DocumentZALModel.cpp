#include "DocumentZALModel.h"

DocumentZALModel::DocumentZALModel()
{
}

DocumentZALModel::~DocumentZALModel()
{
}

DocumentZAL DocumentZALModel::getDocumentZAL(QString symbol)
{
    DocumentZAL document;
    ContractorService *conService = new ContractorService();
    MOPModel *mopModel = new MOPModel();

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT type, contractor, method_of_payment, document_place, document_date, sale_date, payment_date, "
                    "total, paid, discount, order_symbol, receive_person, issue_person, is_paid, warehouse_result, owner "
                    "FROM sale_documents "
                    "WHERE symbol = ? AND warehouse = ?"
                    "AND is_active = true");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentZALModel::getDocumentZAL", query);
    else if(query->size() > 0)
    {
        query->first();

        document.setDocumentType(query->value(0).toString());
        document.setSymbol(symbol);
        document.setContractor(conService->getContractor(query->value(1).toInt()));
        document.setMethodOfPayment(mopModel->getMethodOfPayment(query->value(2).toInt()));
        document.setDocumentPlace(documentPlaceModel->getDocumentPlace(query->value(3).toInt()).getName());
        document.setDocumentDate(query->value(4).toDate());
        document.setSaleDate(query->value(5).toDate());;
        document.setPaymentDate(query->value(6).toDate());
        document.setTotal(query->value(7).toDouble());
        document.setPaidValue(query->value(8).toDouble());
        document.setDiscount(query->value(9).toDouble());
        document.setOrder(query->value(10).toString());
        document.setReceiveName(peopleModel->getName(query->value(11).toInt()));
        document.setIssueName(peopleModel->getName(query->value(12).toInt()));
        document.setPaid(query->value(13).toInt());
        document.setStoreResult(query->value(14).toBool());
        document.setOwnerId(query->value(15).toInt());
    }
    delete conService;
    delete mopModel;
    delete query;

    return document;
}

void DocumentZALModel::addDocumentZAL(DocumentZAL document)
{

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO sale_documents (type, symbol, contractor, method_of_payment, document_place, "
                    "document_date, sale_date, payment_date, total, paid, discount, order_symbol, receive_person, issue_person, is_paid, "
                          "warehouse_result, owner, warehouse) "
                        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    query->addBindValue(document.getDocumentType());
    query->addBindValue(document.getSymbol());
    if (document.getDocumentType()=="PA")
        query->addBindValue(0);
    else
        query->addBindValue(document.getContractor().getId());

    query->addBindValue(document.getMethodOfPayment().getId());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(document.getDocumentPlace()));
    query->addBindValue(document.getDocumentDate().toString("yyyy-MM-dd"));
    query->addBindValue(document.getSaleDate().toString("yyyy-MM-dd"));
    query->addBindValue(document.getPaymentDate().toString("yyyy-MM-dd"));
    query->addBindValue(document.getTotal());
    query->addBindValue(document.getPaidValue());
    query->addBindValue(document.getDiscount());
    query->addBindValue(document.getOrder());
    query->addBindValue(peopleModel->getPersonId(document.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(document.getIssueName()));
    query->addBindValue(document.isPaid());
    query->addBindValue(document.getStoreResult());
    query->addBindValue(document.getOwnerId());
    query->addBindValue(currentWarehouse->getId());
    query->exec();


    if(this->isQueryError(query))
        throw new SQLException("DocumentZALModel::addInvoice", query);

    delete query;
}

void DocumentZALModel::editDocumentZAL(DocumentZAL newDocument)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE sale_documents SET type = ?, contractor = ?, method_of_payment = ?, document_place = ?,document_date = ?, sale_date = ?, "
                    "payment_date = ?, total = ?, paid = ?, discount = ?, order_symbol =?, receive_person = ?, issue_person = ?, is_paid = ?, warehouse_result = ? "
                    "WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(newDocument.getDocumentType());
    if (newDocument.getDocumentType()=="PA")
        query->addBindValue(0);
    else
        query->addBindValue(newDocument.getContractor().getId());

    query->addBindValue(newDocument.getMethodOfPayment().getId());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(newDocument.getDocumentPlace()));
    query->addBindValue(newDocument.getDocumentDate());
    query->addBindValue(newDocument.getSaleDate());
    query->addBindValue(newDocument.getPaymentDate());
    query->addBindValue(newDocument.getTotal());
    query->addBindValue(newDocument.getPaidValue());
    query->addBindValue(newDocument.getDiscount());
    query->addBindValue(newDocument.getOrder());
    query->addBindValue(peopleModel->getPersonId(newDocument.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(newDocument.getIssueName()));
    query->addBindValue(newDocument.isPaid());
    query->addBindValue(newDocument.getStoreResult());
    query->addBindValue(newDocument.getSymbol());
    query->addBindValue(currentWarehouse->getId());
    query->exec();


    if(this->isQueryError(query))
        throw new SQLException("DocumentZALModel::editDocumentZAL", query);

    delete query;
}


void DocumentZALModel::removeDocumentZAL(QString symbol)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM sale_documents WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(ApplicationManager::getInstance()->getWarehouseId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("DocumentZALModel::removeDocumentZAL", query);

    delete query;

}



