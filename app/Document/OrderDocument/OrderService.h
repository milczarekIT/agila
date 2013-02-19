#ifndef ORDERSERVICE_H
#define ORDERSERVICE_H

#include "Document/OrderDocument/OrderModel.h"
#include "Document/DocumentService.h"

class OrderService : public DocumentService
{
private:
    Order order;
    OrderModel *model;
public:
    OrderService();
    ~OrderService();

    Order getOrder(QString symbol);
    void addOrder(Order order);
    void editOrder(Order newOrder);
    void removeOrder(QString symbol);
};

#endif // ORDERSERVICE_H
