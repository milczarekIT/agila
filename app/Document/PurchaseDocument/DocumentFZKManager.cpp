#include "DocumentFZKManager.h"

DocumentFZKManager::DocumentFZKManager()
{
    this->fzkPolicy = new DocumentFZKPolicy();
}
DocumentFZKManager::~DocumentFZKManager(){}

void DocumentFZKManager::countGoodsValue(double discountPercentage,bool first)
{

     totalWithDiscountNew= 0.0;
     discountNew = 0.0;
     totalNew=0.0;
     totalNetNew=0.0;
     toPay=0.0;

     if(first==true)
     {
         totalWithDiscount=0.0;
         discount = 0.0;
         total=0.0;
         totalNet=0.0;

         for (int i=0; i<documentPositionVectorOld.size(); i++)
         {discount+=(documentPositionVectorOld[i].getPriceGross()*(discountPercentage/100))*(documentPositionVectorOld[i].getQuantity());
             total+=(documentPositionVectorOld[i].getPriceGross())*(documentPositionVectorOld[i].getQuantity());
             totalNet+=(documentPositionVectorOld[i].getPriceNet())*(documentPositionVectorOld[i].getQuantity());
          }   totalWithDiscount+=total-discount;
     }

     for (int i=0; i<documentPositionVectorNew.size(); i++)
     {
         discountNew+=(documentPositionVectorNew[i].getPriceGross()*(discountPercentage/100))*(documentPositionVectorNew[i].getQuantity());
         totalNew+=(documentPositionVectorNew[i].getPriceGross())*(documentPositionVectorNew[i].getQuantity());
         totalNetNew+=(documentPositionVectorNew[i].getPriceNet())*(documentPositionVectorNew[i].getQuantity());
      }   totalWithDiscountNew+=totalNew-discountNew;
     if(this->getFZKPolicy()->getFZK().getInvoice().isPaid()==true)
          toPay=totalWithDiscountNew-totalWithDiscount;
    else
        toPay=totalWithDiscount+(totalWithDiscountNew-totalWithDiscount);
}
