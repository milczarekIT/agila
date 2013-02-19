#ifndef ORDERPOLICY_H
#define ORDERPOLICY_H

#include "Document/OrderDocument/Order.h"

class OrderPolicy
{
public:
    OrderPolicy();
    ~OrderPolicy();
    Order getOrderOld();
    Order getOrder();
    void setOrder(Order order);
    void setOrderOld(Order orderOld);
    void setOrderData(Order doc);

    void setContractor(Contractor c);
    Contractor getContractor();

private:
    Order orderOld,order;
};

#endif // ORDERPOLICY_H
