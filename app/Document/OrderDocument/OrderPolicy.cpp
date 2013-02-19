#include "OrderPolicy.h"

OrderPolicy::OrderPolicy()
{

}

OrderPolicy::~OrderPolicy()
{

}

void OrderPolicy::setOrderData(Order doc)
{

    order.setDocumentType(doc.getDocumentType());
    order.setSymbol(doc.getSymbol());
    order.setContractor(this->getContractor());
    order.setDocumentPlace(doc.getDocumentPlace());
    order.setDocumentDate(doc.getDocumentDate());
    order.setRealizationDate(doc.getRealizationDate());
    order.setTotal(doc.getTotal());
    order.setDiscount(doc.getDiscount());
    order.setReceiveName(doc.getReceiveName());
    order.setIssueName(doc.getIssueName());
    order.setRealized(doc.isRealized());
    order.setDocumentPositions(doc.getDocumentPositions());

}

Order OrderPolicy::getOrderOld()
{
    return this->orderOld;
}
Order OrderPolicy::getOrder()
{
    return this->order;
}
void OrderPolicy::setOrder(Order order)
{
    this->order=order;
}
void OrderPolicy::setOrderOld(Order orderOld)
{
    this->orderOld=orderOld;
}
void OrderPolicy::setContractor(Contractor c)
{
    this->order.setContractor(c);
}
Contractor OrderPolicy::getContractor()
{
    return this->order.getContractor();
}
