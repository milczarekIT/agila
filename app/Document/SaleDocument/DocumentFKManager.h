#ifndef DOCUMENTFKMANAGER_H
#define DOCUMENTFKMANAGER_H

#include "Document/SaleDocument/DocumentFK.h"
#include "Document/SaleDocument/DocumentFKPolicy.h"
#include "Document/PurchaseDocument/DocumentFZK.h"
#include "Document/PurchaseDocument/DocumentFZKPolicy.h"
class DocumentFKManager
{

public:
    DocumentFKManager();
    ~DocumentFKManager();

    void setFactureData(DocumentFK FK);
    QVector <DocumentPosition> getDocumentPositionOld();
    QVector <DocumentPosition> getDocumentPositionNew();
    double getDiscount();
    double getTotal();
    double getTotalWithDiscount();
    double getTotalNet();
    double getTotalNew();
    double getTotalWithDiscountNew();
    double getTotalNetNew();
    double getToPay();
    void setDocumentPositions(QVector<DocumentPosition> vector);
    void setDocumentPositionsOld(QVector<DocumentPosition> vector);
    void setTotalWithDiscountNew(double value);
    void setTotalNew(double value);
    void setTotalNetNew(double value);
    void setToPay(double value);
    DocumentFKPolicy *getFKPolicy();
    DocumentFZKPolicy *getFZKPolicy();
    virtual void countGoodsValue(double discountPercentage,bool first);
    void addGoodsToVector(DocumentPosition dp);
    void setChangedQuantity(int row, double quantity);
    void removeFromVector(int position);

protected:
    /**
    Wektor pozycji na dokumencie.
    */
    QVector <DocumentPosition> documentPositionVectorNew;
    QVector <DocumentPosition> documentPositionVectorOld;
    DocumentFKPolicy* fkPolicy;
    DocumentFZKPolicy* fzkPolicy;
    /**
    Zmienna globalna przechowujaca rabat(kwotowo) zwiazany z danym kontrahentem
    */
    double discount;
    double discountNew;
    /**
    Zmienna globalna przechowujaca całkowita wartość dóbr dodanych do faktury( brutto po rabacie)
    */
    double totalWithDiscount;
    double totalWithDiscountNew;
    /**
    Zmienna globalna przechowujaca całkowita wartość dóbr dodanych do faktury(bez rabatu brutto)
    */
    double total;
    double totalNew;
    double toPay;
    /**
    Zmienna globalna przechowujaca całkowita wartość dóbr dodanych do faktury(bez rabatu netto)
    */
    double totalNet;
    double totalNetNew;
    void itIsTheSamePosition(DocumentPosition dp,int i);

};

#endif // DOCUMENTFKMANAGER_H
