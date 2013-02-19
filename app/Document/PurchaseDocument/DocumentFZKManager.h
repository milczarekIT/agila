#ifndef DOCUMENTFZKMANAGER_H
#define DOCUMENTFZKMANAGER_H

#include "Document/SaleDocument/DocumentFKManager.h"

class DocumentFZKManager : public DocumentFKManager
{
public:
    DocumentFZKManager();
    ~DocumentFZKManager();
    void countGoodsValue(double discountPercentage, bool first);
};

#endif // DOCUMENTFZKMANAGER_H
