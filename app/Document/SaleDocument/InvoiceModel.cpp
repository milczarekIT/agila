#include "InvoiceModel.h"


InvoiceModel::InvoiceModel() : DocumentModel()
{
}

InvoiceModel::~InvoiceModel()
{
}


Invoice InvoiceModel::getInvoice(QString symbol)
{
    Invoice invoice;
    ContractorService *conService = new ContractorService();
    MOPModel *mopModel = new MOPModel();

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT type, contractor, method_of_payment, document_place, document_date, sale_date, payment_date, "
                    "total, discount, order_symbol, receive_person, issue_person, is_paid, warehouse_result, owner "
                    "FROM sale_documents "
                    "WHERE symbol = ? "
                    "AND is_active = true AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("InvoiceModel::getInvoice", query);
    else if(query->size() > 0)
    {
        query->first();

        invoice.setDocumentType(query->value(0).toString());
        invoice.setSymbol(symbol);
        invoice.setContractor(conService->getContractor(query->value(1).toInt()));
        invoice.setMethodOfPayment(mopModel->getMethodOfPayment(query->value(2).toInt()));
        invoice.setDocumentPlace(documentPlaceModel->getDocumentPlace(query->value(3).toInt()).getName());
        invoice.setDocumentDate(query->value(4).toDate());
        invoice.setSaleDate(query->value(5).toDate());
        invoice.setPaymentDate(query->value(6).toDate());
        invoice.setTotal(query->value(7).toDouble());
        invoice.setDiscount(query->value(8).toDouble());
        invoice.setOrder(query->value(9).toString());
        invoice.setReceiveName(peopleModel->getName(query->value(10).toInt()));
        invoice.setIssueName(peopleModel->getName(query->value(11).toInt()));
        invoice.setPaid(query->value(12).toInt());
        invoice.setStoreResult(query->value(13).toBool());
        invoice.setOwnerId(query->value(14).toInt());
    }
    delete conService;
    delete mopModel;
    delete query;

    return invoice;
}

void InvoiceModel::addInvoice(Invoice fv)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO sale_documents (type, symbol, contractor, method_of_payment, document_place, "
                    "document_date, sale_date, payment_date, total, discount, order_symbol, receive_person, issue_person, is_paid, "
                    "warehouse_result, owner, warehouse) "
                        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    query->addBindValue(fv.getDocumentType());
    query->addBindValue(fv.getSymbol());
    if (fv.getDocumentType()=="PA")
        query->addBindValue(0);
    else
        query->addBindValue(fv.getContractor().getId());
    query->addBindValue(fv.getMethodOfPayment().getId());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(fv.getDocumentPlace()));
    query->addBindValue(fv.getDocumentDate().toString("yyyy-MM-dd"));
    query->addBindValue(fv.getSaleDate().toString("yyyy-MM-dd"));
    query->addBindValue(fv.getPaymentDate().toString("yyyy-MM-dd"));
    query->addBindValue(fv.getTotal());
    query->addBindValue(fv.getDiscount());
    query->addBindValue(fv.getOrder());
    query->addBindValue(peopleModel->getPersonId(fv.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(fv.getIssueName()));
    query->addBindValue(fv.isPaid());
    query->addBindValue(fv.getStoreResult());
    query->addBindValue(fv.getOwnerId());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("InvoiceModel::addInvoice", query);

    delete query;
}

void InvoiceModel::editInvoice(Invoice newInvoice)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE sale_documents SET type = ?, contractor = ?, method_of_payment = ?, document_place = ?,document_date = ?, sale_date = ?, "
                    "payment_date = ?, total = ?, discount = ?, order_symbol =?, receive_person = ?, issue_person = ?, is_paid = ?, warehouse_result = ? "
                    "WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(newInvoice.getDocumentType());
    if (newInvoice.getDocumentType()=="PA")
        query->addBindValue(0);
    else
        query->addBindValue(newInvoice.getContractor().getId());

    query->addBindValue(newInvoice.getMethodOfPayment().getId());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(newInvoice.getDocumentPlace()));
    query->addBindValue(newInvoice.getDocumentDate());
    query->addBindValue(newInvoice.getSaleDate());
    query->addBindValue(newInvoice.getPaymentDate());
    query->addBindValue(newInvoice.getTotal());
    query->addBindValue(newInvoice.getDiscount());
    query->addBindValue(newInvoice.getOrder());
    query->addBindValue(peopleModel->getPersonId(newInvoice.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(newInvoice.getIssueName()));
    query->addBindValue(newInvoice.isPaid());
    query->addBindValue(newInvoice.getStoreResult());
    query->addBindValue(newInvoice.getSymbol());
    query->addBindValue(currentWarehouse->getId());
    query->exec();


    if(this->isQueryError(query))
        throw new SQLException("InvoiceModel::editInvoice", query);

    delete query;
}


void InvoiceModel::removeInvoice(QString symbol)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM sale_documents WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("InvoiceModel::removeInvoice", query);

    delete query;

}



