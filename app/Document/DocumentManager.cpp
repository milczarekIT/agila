#include "DocumentManager.h"

DocumentManager::DocumentManager(QWidget * parent)
{
    this->parent=parent;
}

DocumentManager::~DocumentManager()
{
}

void DocumentManager::addGoodsToVector(DocumentPosition dp)
{

    documentPositionVector.append(dp);
    for(int i=0; i<documentPositionVector.size()-1;i++)
              {
    itIsTheSamePosition(dp,i);
    }
}


void DocumentManager::itIsTheSamePosition(DocumentPosition dp,int i)
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

void DocumentManager::countGoodsValue(double discountPercentage)
{
     totalWithDiscount= 0.0;
     discount = 0.0;
     total=0.0;
     totalNet=0.0;
     for (int i=0; i<documentPositionVector.size(); i++)
     {
     totalNet+=(documentPositionVector[i].getPriceNet())*(documentPositionVector[i].getQuantity());
     total+=(documentPositionVector[i].getPriceGross())*(documentPositionVector[i].getQuantity());
      }
     discount=total*(discountPercentage/100);
     totalWithDiscount+=total-discount;
}


void DocumentManager::setChangedQuantity(int row, double quantity)
{
    documentPositionVector[row].setQuantity(quantity);
}

void DocumentManager::removeFromVector(int position)
{
    this->documentPositionVector.remove(position);
}

QVector<DocumentPosition> DocumentManager::getDocumentPosition()
{
    return this->documentPositionVector;
}

double DocumentManager::getTotalWithDiscount()
{
    return this->totalWithDiscount;
}

double DocumentManager::getTotal()
{
    return this->total;
}

double DocumentManager::getTotalNet()
{
    return this->totalNet;
}
double DocumentManager::getAdvance()
{
    return this->advance;
}
void DocumentManager::setTotal(double total)
{
    this->total=total;
}

void DocumentManager::setDocumentPositions(QVector<DocumentPosition> vector)
{
    this->documentPositionVector=vector;
}

void DocumentManager::setTotalWithDiscount(double totalWithDiscount)
{
    this->totalWithDiscount=totalWithDiscount;
}

void DocumentManager::setTotalNet(double totalNet)
{
    this->totalNet=totalNet;
}

void DocumentManager::setDiscount(double discount)
{
    this->discount=discount;
}
void DocumentManager::setAdvance(double advance)
{
    this->advance=advance;
}
InvoicePolicy* DocumentManager::getInvoicePolicy()
{
    return this->invoicePolicy;
}

PurchasePolicy* DocumentManager::getPurchasePolicy()
{
    return this->purchasePolicy;
}

OrderPolicy* DocumentManager::getOrderPolicy()
{
    return this->orderPolicy;
}
DocumentPZPolicy* DocumentManager::getDocumentPZPolicy()
{
    return this->documentPZPolicy;
}
DocumentWZPolicy* DocumentManager::getDocumentWZPolicy()
{
    return this->documentWZPolicy;
}
StoragePolicy* DocumentManager::getStoragePolicy()
{
    return this->storagePolicy;
}
DocumentZALPolicy* DocumentManager::getDocumentZALPolicy()
{
    return this->zalPolicy;
}

