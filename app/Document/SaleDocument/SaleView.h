#ifndef SALEVIEW_H
#define SALEVIEW_H

#include "Document/DocumentView.h"

class SaleView : public DocumentView
{

public:
   explicit SaleView(QWidget* parent);
    ~SaleView();
    DateEdit* getPaymantDate();
    bool isPaid();
    bool isStoreUpdating();
    void setLineGoodsValueNet(double valueNet);
    void setLineDiscount(double discount);
    void setLineGoodsValueDiscount(double goodsValueWithDiscount);
    void setSaleOrStoreDate(QDate saleDate);
    void setPaymentDate(QDate paymentDate);
    void setCheckPaid(bool paid);
    void setCheckStoreUpdate(bool update);

    QLineEdit* getDiscountOrWaybillNo();
    QLineEdit *getLineOrderSymbol();
    double getLineGoodsValueNet();
    double getLineGoodsValueDiscount();
    QDate getSaleOrStoreDate();
    DateEdit* getPaymentDate();
    QComboBox *getWayToPay();

protected:
    void initGoodsTable() ;
    void initOptionalLineEdits();
    void initOptionalButtons();
    void initOptionalConnections();
    void addOptionalComponents();

    QLineEdit *lineOrder;
    QLineEdit *lineDiscount;
    QLineEdit *lineGoodsValueDiscount;
    QLineEdit *lineGoodsValueNet;
    QComboBox* boxWayToPay;
    QCheckBox* checkPaid;
    QCheckBox* checkStoreUpdating;
    DateEdit* saleDate;
    DateEdit *paymentDate;

};

#endif // SALEVIEW_H
