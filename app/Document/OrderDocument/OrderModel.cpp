#include "OrderModel.h"

OrderModel::OrderModel() : DocumentModel()
{
}

OrderModel::~OrderModel()
{

}

Order OrderModel::getOrder(QString symbol)
{
    Order order;
    ContractorService *conService = new ContractorService();
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("SELECT type, contractor, document_place, document_date, realization_date, "
                    "total, discount, receive_person, issue_person, realized, owner "
                    "FROM orders "
                    "WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("OrderModel::getOrder", query);
    else if(query->size() > 0)
    {
        query->first();

        order.setSymbol(symbol);
        order.setDocumentType(query->value(0).toString());
        order.setContractor(conService->getContractor(query->value(1).toInt()));
        order.setDocumentPlace(documentPlaceModel->getDocumentPlace(query->value(2).toInt()).getName());
        order.setDocumentDate(query->value(3).toDate());
        order.setRealizationDate(query->value(4).toDate());
        order.setTotal(query->value(5).toDouble());
        order.setDiscount(query->value(6).toDouble());
        order.setReceiveName(peopleModel->getName(query->value(7).toInt()));
        order.setIssueName(peopleModel->getName(query->value(8).toInt()));
        order.setRealized(query->value(9).toBool());
        order.setOwnerId(query->value(10).toInt());

    }
    delete conService;
    delete query;

    return order;
}

void OrderModel::addOrder(Order order)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("INSERT INTO orders (type, symbol, contractor, document_place, "
                    "document_date, realization_date, total, discount, receive_person, issue_person, realized, owner, warehouse) "
                        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    query->addBindValue(order.getDocumentType());
    query->addBindValue(order.getSymbol());
    query->addBindValue(order.getContractor().getId());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(order.getDocumentPlace()));
    query->addBindValue(order.getDocumentDate().toString("yyyy-MM-dd"));
    query->addBindValue(order.getRealizationDate().toString("yyyy-MM-dd"));
    query->addBindValue(order.getTotal());
    query->addBindValue(order.getDiscount());
    query->addBindValue(peopleModel->getPersonId(order.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(order.getIssueName()));
    query->addBindValue(QVariant(order.isRealized()).toInt());
    query->addBindValue(order.getOwnerId());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("OrderModel::addOrder", query);

    delete query;
}

void OrderModel::editOrder(Order newOrder)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("UPDATE orders SET type = ?, contractor = ?, document_place = ?, document_date = ?, realization_date = ?, "
                    "total = ?, discount = ?, receive_person = ?, issue_person = ?, realized = ? "
                    "WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(newOrder.getDocumentType());
    query->addBindValue(newOrder.getContractor().getId());
    query->addBindValue(documentPlaceModel->getDocumentPlaceId(newOrder.getDocumentPlace()));
    query->addBindValue(newOrder.getDocumentDate());
    query->addBindValue(newOrder.getRealizationDate());
    query->addBindValue(newOrder.getTotal());
    query->addBindValue(newOrder.getDiscount());
    query->addBindValue(peopleModel->getPersonId(newOrder.getReceiveName()));
    query->addBindValue(peopleModel->getPersonId(newOrder.getIssueName()));
    query->addBindValue(QVariant(newOrder.isRealized()).toInt());
    query->addBindValue(newOrder.getSymbol());
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("OrderModel::editOrder", query);

    delete query;
}

void OrderModel::removeOrder(QString symbol)
{
    query = new QSqlQuery(Database::getInstance().db);
    query->prepare("DELETE FROM orders WHERE symbol = ? AND warehouse = ?");
    query->addBindValue(symbol);
    query->addBindValue(currentWarehouse->getId());
    query->exec();

    if(this->isQueryError(query))
        throw new SQLException("OrderModel::removeOrder", query);

    delete query;
}
