#include "DocumentZALManager.h"

DocumentZALManager::DocumentZALManager()
{
this->zalPolicy = new DocumentZALPolicy();
}

DocumentZALManager::~DocumentZALManager(){}


Contractor DocumentZALManager::getContractor()
{
return this->getDocumentZALPolicy()->getContractor();
}
void DocumentZALManager::setContractor(Contractor c)
{
this->getDocumentZALPolicy()->setContractor(c);
}

void DocumentZALManager::countGoodsValue(double discountPercentage)
{
     totalWithDiscount= 0.0;
     discount = 0.0;
     total=0.0;
     totalNet=0.0;
     advance=0.0;
     for (int i=0; i<documentPositionVector.size(); i++)
     {
         totalNet+=(documentPositionVector[i].getPriceNet())*(documentPositionVector[i].getQuantity());
         total+=(documentPositionVector[i].getPriceGross())*(documentPositionVector[i].getQuantity());
          }
         discount=total*(discountPercentage/100);
         totalWithDiscount+=total-discount;

     double sum=0.0;
     if(!zalPolicy->getPreviousZALVector().isEmpty())
     {
          for(int i=0; i<this->zalPolicy->getPreviousZALVector().size();i++)
          {
              sum+= zalPolicy->getPreviousZAL()[i].getTotal();
           }
          advance = totalWithDiscount-sum;
     }
}
