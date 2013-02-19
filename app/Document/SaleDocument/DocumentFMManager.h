#ifndef DOCUMENTFMMANAGER_H
#define DOCUMENTFMMANAGER_H

#include "Document/SaleDocument/SaleManager.h"

class DocumentFMManager : public SaleManager
{

public:
    DocumentFMManager();
    ~DocumentFMManager();
    void countGoodsValue(double discounPercentage);
};

#endif // DOCUMENTFMMANAGER_H
