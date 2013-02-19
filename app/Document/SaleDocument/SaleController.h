#ifndef SALECONTROLLER_H
#define SALECONTROLLER_H

#include "Document/DocumentController.h"

class SaleController : public DocumentController
{

public:
    explicit SaleController();
    ~SaleController();

protected:

    void addGood();
    bool isQuantityColumn(int column);
    void setGoodsValue();
};

#endif // SALECONTROLLER_H
