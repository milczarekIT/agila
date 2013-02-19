#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include "Document/DocumentManager.h"
#include "Document/OrderDocument/Order.h"

class OrderManager : public DocumentManager
{
public:
    OrderManager();
     ~OrderManager();

    void itIsTheSamePosition(DocumentPosition dp,int i);
    Contractor getContractor();
    void setContractor(Contractor c);

};

#endif // ORDERMANAGER_H
