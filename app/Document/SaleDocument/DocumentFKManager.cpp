#include "DocumentFKManager.h"

DocumentFKManager::~DocumentFKManager(){}
DocumentFKManager::DocumentFKManager()
{
this->fkPolicy= new DocumentFKPolicy();
}

void DocumentFKManager::addGoodsToVector(DocumentPosition dp)
{

    documentPositionVectorNew.append(dp);
    for(int i=0; i<documentPositionVectorNew.size()-1;i++)
              {
    itIsTheSamePosition(dp,i);
    }
}

void DocumentFKManager::removeFromVector(int position)
{
this->documentPositionVectorNew.remove(position);
}


void DocumentFKManager::countGoodsValue(double discountPercentage,bool first)
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
         {
             totalNet+=(documentPositionVectorOld[i].getPriceNet())*(documentPositionVectorOld[i].getQuantity());
             total+=(documentPositionVectorOld[i].getPriceGross())*(documentPositionVectorOld[i].getQuantity());
          }
         discount+=total*(discountPercentage/100);
         totalWithDiscount+=total-discount;
     }

     for (int i=0; i<documentPositionVectorNew.size(); i++)
     {
         totalNetNew+=(documentPositionVectorNew[i].getPriceNet())*(documentPositionVectorNew[i].getQuantity());
         totalNew+=(documentPositionVectorNew[i].getPriceGross())*(documentPositionVectorNew[i].getQuantity());
          }
     discountNew=totalNew*(discountPercentage/100);
     totalWithDiscountNew=totalNew-discountNew;
     if(this->getFKPolicy()->getFK().getInvoice().isPaid()==true)
          toPay=totalWithDiscountNew-totalWithDiscount;
    else
        toPay=totalWithDiscount+(totalWithDiscountNew-totalWithDiscount);

}

void DocumentFKManager::itIsTheSamePosition(DocumentPosition dp,int i)
{
    if (documentPositionVectorNew.size()>1)
         {

          if(documentPositionVectorNew[i].getGood().getId()==dp.getGood().getId())
             {
              if(documentPositionVectorNew[i].getPriceNet()==dp.getPriceNet())
                {
                  documentPositionVectorNew[i].setQuantity(documentPositionVectorNew[i].getQuantity()+dp.getQuantity());
                  documentPositionVectorNew.remove(documentPositionVectorNew.size()-1);
                }
              }
         }
}

void DocumentFKManager::setChangedQuantity(int row, double quantity)
{
documentPositionVectorNew[row].setQuantity(quantity);
}

QVector<DocumentPosition> DocumentFKManager::getDocumentPositionNew(){
    return this->documentPositionVectorNew;
}

QVector<DocumentPosition> DocumentFKManager::getDocumentPositionOld(){
return this->documentPositionVectorOld;
}

double DocumentFKManager::getTotal()
{
return this->total;
}

double DocumentFKManager::getTotalWithDiscount(){
return this->totalWithDiscount;
}

double DocumentFKManager::getTotalNew()
{
return this->totalNew;
}

double DocumentFKManager::getTotalWithDiscountNew(){
return this->totalWithDiscountNew;
}
double DocumentFKManager::getTotalNetNew()
{
return this->totalNetNew;
}

double DocumentFKManager::getTotalNet(){
return this->totalNet;
}

double DocumentFKManager::getToPay(){
return this->toPay;
}

void DocumentFKManager::setDocumentPositions(QVector<DocumentPosition> vector)
{
    this->documentPositionVectorNew=vector;
}
void DocumentFKManager::setDocumentPositionsOld(QVector<DocumentPosition> vector)
{
    this->documentPositionVectorOld=vector;
}
void DocumentFKManager::setTotalWithDiscountNew(double value)
{
    this->totalWithDiscountNew=value;
}
void DocumentFKManager::setTotalNew(double value)
{
    this->totalNew=value;
}
void DocumentFKManager::setTotalNetNew(double value)
{
    this->totalNetNew=value;
}
void DocumentFKManager::setToPay(double value)
{
    this->toPay=value;
}
DocumentFKPolicy* DocumentFKManager::getFKPolicy()
{
    return this->fkPolicy;
}
DocumentFZKPolicy* DocumentFKManager::getFZKPolicy()
{
    return this->fzkPolicy;
}
