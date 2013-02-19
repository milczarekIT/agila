#include "StoreDocumentManager.h"

StoreDocumentManager::StoreDocumentManager()
{
}
StoreDocumentManager::~StoreDocumentManager(){}

void StoreDocumentManager::itIsTheSamePosition(DocumentPosition dp,int i)
{
    if (documentPositionVector.size()>1)
         {

          if(documentPositionVector[i].getGood().getId()==dp.getGood().getId())
             {
              if(documentPositionVector[i].getPriceNet()==dp.getPriceNet())
                {
                  documentPositionVector[i].setQuantity(documentPositionVector[i].getQuantity()+dp.getQuantity());
                  documentPositionVector.remove(documentPositionVector.size()-1);
                }
              }
         }
}


