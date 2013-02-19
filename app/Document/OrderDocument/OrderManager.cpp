#include "OrderManager.h"

OrderManager::OrderManager()
{
    this->orderPolicy = new OrderPolicy();
}

OrderManager::~OrderManager()
{
    delete orderPolicy;
}

void OrderManager::itIsTheSamePosition(DocumentPosition dp,int i)
{
    if (documentPositionVector.size()>1)
     {

      if(documentPositionVector[i].getGood().getId()==dp.getGood().getId())
         {
          if(documentPositionVector[i].getPriceGross()==dp.getPriceGross())
            {
              documentPositionVector[i].setQuantity(documentPositionVector[i].getQuantity()+dp.getQuantity());
              documentPositionVector.remove(documentPositionVector.size()-1);
            }
          }
    }
}
Contractor OrderManager::getContractor()
{
return this->getOrderPolicy()->getContractor();
}
void OrderManager::setContractor(Contractor c)
{
this->getOrderPolicy()->setContractor(c);
}
