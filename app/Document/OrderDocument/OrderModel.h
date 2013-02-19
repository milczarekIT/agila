#ifndef ORDERMODEL_H
#define ORDERMODEL_H

#include "Document/DocumentModel.h"
#include "Contractor/ContractorService.h"
#include "Document/OrderDocument/Order.h"

class OrderModel : public DocumentModel
{
public:
    OrderModel();
    ~OrderModel();

    Order getOrder(QString symbol);
    void addOrder(Order order);
    void editOrder(Order newOrder);
    void removeOrder(QString symbol);
};

#endif // ORDERMODEL_H
