#include "PurchaseInvoiceModel.h"

PurchaseInvoiceModel::PurchaseInvoiceModel() : DocumentModel()
{
}

PurchaseInvoiceModel::~PurchaseInvoiceModel()
{
}

PurchaseInvoice PurchaseInvoiceModel::getPurchaseInvoice(QString symbol)
{
    PurchaseInvoice invoice;
    ContractorService *conService = new ContractorService();
    MOPModel *mopModel = new MOPModel();

    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT type, contractor, method_of_payment, document_place, document_date, purchase_date, payment_date, "
                    "total, discount, order_symbol, purchase_document, receive_person, issue_person, is_paid, warehouse_result, owner "
                    "FROM purchase_documents "
                    "WHERE symbol = ? AND warehouse = ?"
                    "AND is_active = true");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("PurchaseInvoiceModel::getPurchaseInvoice", query);
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
        invoice.setPurchaseDocument(query->value(10).toString());
        invoice.setReceiveName(peopleModel->getName(query->value(11).toInt()));
        invoice.setIssueName(peopleModel->getName(query->value(12).toInt()));
        invoice.setPaid(query->value(13).toBool());
        invoice.setStoreResult(query->value(14).toBool());
        invoice.setOwnerId(query->value(15).toInt());
    }

    delete conService;
    delete mopModel;

    return invoice;
}

void PurchaseInvoiceModel::addPurchaseInvoice(PurchaseInvoice invoice)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO purchase_documents (type, symbol, contractor, method_of_payment, document_place, "
                    "document_date, purchase_date, payment_date, total, discount, order_symbol, purchase_document, receive_person, issue_person, "
                   "is_paid, warehouse_result, owner, warehouse) "
                        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?,  ?, ?, ?, ?, ?, ?, ?, ?)");

    query->addBindValue(invoice.getDocumentType());
    query->addBindValue(invoice.getSymbol());
    query->addBindValue(invoice.getContractor().getId());
    query->addBindValue(invoice.getMethodOfPayment().getId());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(invoice.getDocumentPlace()));
    query->addBindValue(invoice.getDocumentDate().toString("yyyy-MM-dd"));
    query->addBindValue(invoice.getSaleDate().toString("yyyy-MM-dd"));
    query->addBindValue(invoice.getPaymentDate().toString("yyyy-MM-dd"));
    query->addBindValue(invoice.getTotal());
    query->addBindValue(invoice.getDiscount());
    query->addBindValue(invoice.getOrder());
    query->addBindValue(invoice.getPurchaseDocument());
    query->addBindValue(peopleModel->getPersonId(invoice.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(invoice.getIssueName()));
    query->addBindValue(invoice.isPaid());
    query->addBindValue(invoice.getStoreResult());
    query->addBindValue(invoice.getOwnerId());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("PurchaseInvoiceModel::addPurchaseInvoice", query);
}

void PurchaseInvoiceModel::editPurchaseInvoice(PurchaseInvoice newInvoice)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE purchase_documents SET type = ?, contractor = ?, method_of_payment = ?, document_place = ?,document_date = ?, purchase_date = ?, "
                    "payment_date = ?, total = ?, discount = ?, order_symbol = ?, purchase_document = ?, receive_person = ?, issue_person = ?, is_paid = ?, warehouse_result = ? "
                    "WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(newInvoice.getDocumentType());
    query->addBindValue(newInvoice.getContractor().getId());
    query->addBindValue(newInvoice.getMethodOfPayment().getId());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(newInvoice.getDocumentPlace()));
    query->addBindValue(newInvoice.getDocumentDate());
    query->addBindValue(newInvoice.getSaleDate());
    query->addBindValue(newInvoice.getPaymentDate());
    query->addBindValue(newInvoice.getTotal());
    query->addBindValue(newInvoice.getDiscount());
    query->addBindValue(newInvoice.getOrder());
    query->addBindValue(newInvoice.getPurchaseDocument());
    query->addBindValue(peopleModel->getPersonId(newInvoice.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(newInvoice.getIssueName()));
    query->addBindValue(newInvoice.isPaid());
    query->addBindValue(newInvoice.getStoreResult());
    query->addBindValue(newInvoice.getSymbol());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("PurchaseInvoiceModel::getPurchaceInvoice", query);
}


void PurchaseInvoiceModel::removePurchaseInvoice(QString symbol)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM purchase_documents WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
       throw new SQLException("PurchaseInvoiceModel::removePurchaseInvoice", query);

    delete query;
}
