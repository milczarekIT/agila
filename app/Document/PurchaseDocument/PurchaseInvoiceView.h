#ifndef PURCHASEINVOICEVIEW_H
#define PURCHASEINVOICEVIEW_H

#include "Document/PurchaseDocument/PurchaseInvoiceController.h"
#include "Document/SaleDocument/SaleView.h"

class PurchaseInvoiceController;

class PurchaseInvoiceView : public SaleView  {
   Q_OBJECT
public:
    PurchaseInvoiceView(QWidget *parent, PurchaseInvoiceController* controller);
    ~PurchaseInvoiceView();

    void initPurchaseComponents();
    QLineEdit* getPurchaseOrFactureSymbol();
    QLineEdit* purchaseDocSymbol;
    void setTabOrders();
};

#endif // PurchaseInvoiceView_H
