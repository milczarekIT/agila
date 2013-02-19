#include "DocumentFMManager.h"

DocumentFMManager::DocumentFMManager()
{
    this->invoicePolicy= new InvoicePolicy();
}

DocumentFMManager::~DocumentFMManager()
{
    delete invoicePolicy;
}

void DocumentFMManager::countGoodsValue(double discountPercentage)
{
     totalWithDiscount= 0.0;
     discount = 0.0;
     total=0.0;
     for (int i=0; i<documentPositionVector.size(); i++)
     {
     total+=documentPositionVector[i].getPriceNet()*documentPositionVector[i].getQuantity();
      }
     discount+=total*(discountPercentage/100);
     totalWithDiscount+=total-discount;
}

