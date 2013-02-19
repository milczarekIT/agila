#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include "Document/Document.h"
#include "Document/SaleDocument/InvoicePolicy.h"
#include "Document/PurchaseDocument/PurchasePolicy.h"
#include "Document/OrderDocument/OrderPolicy.h"
#include "Document/StoreDocument/DocumentPZPolicy.h"
#include "Document/StoreDocument/DocumentWZPolicy.h"
#include "Document/StoreDocument/StoragePolicy.h"
#include "Document/SaleDocument/DocumentZALPolicy.h"
class DocumentManager
{
    QWidget * parent;

public:

      DocumentManager(QWidget * parent = 0);
      ~DocumentManager();

      virtual void countGoodsValue(double discountPercentage);
      virtual void itIsTheSamePosition(DocumentPosition dp,int i);
      virtual void setContractor(Contractor c)=0;
      virtual Contractor getContractor()=0;

      void addGoodsToVector(DocumentPosition dp);
      void setChangedQuantity(int row, double quantity);
      void removeFromVector(int position);
      QVector<DocumentPosition> getDocumentPosition();
      double getTotalWithDiscount();
      double getTotal();
      double getTotalNet();
      double getAdvance();
      void setDocumentPositions (QVector<DocumentPosition> vector);
      void setTotalNet(double totalNet);
      void setTotalWithDiscount(double totalWithDiscount);
      void setTotal(double total);
      void setDiscount(double discount);
      void setAdvance(double advance);

      //Polices
      OrderPolicy* getOrderPolicy();
      InvoicePolicy* getInvoicePolicy();
      PurchasePolicy* getPurchasePolicy();
      DocumentPZPolicy *getDocumentPZPolicy();
      DocumentWZPolicy *getDocumentWZPolicy();
      StoragePolicy *getStoragePolicy();
      DocumentZALPolicy * getDocumentZALPolicy();


protected:
      QVector <DocumentPosition> documentPositionVector;
      /**
      Zmienna globalna przechowujaca rabat(kwotowo) zwiazany z danym kontrahentem
      */
      double discount;
      /**
      Zmienna globalna przechowujaca całkowita wartość dóbr dodanych do faktury( brutto po rabacie)
      */
      double totalWithDiscount;
      /**
      Zmienna globalna przechowujaca całkowita wartość dóbr dodanych do faktury(bez rabatu brutto)
      */
      double total;
      /**
      Zmienna globalna przechowujaca całkowita wartość dóbr dodanych do faktury(bez rabatu netto)
      */
      double totalNet;
      double advance;

      InvoicePolicy* invoicePolicy;
      PurchasePolicy* purchasePolicy;
      OrderPolicy* orderPolicy;
      DocumentPZPolicy* documentPZPolicy;
      DocumentWZPolicy* documentWZPolicy;
      StoragePolicy* storagePolicy;
      DocumentZALPolicy* zalPolicy;

};

#endif // DOCUMENTMANAGER_H
