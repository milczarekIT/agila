#ifndef INVOICEVIEW_H
#define INVOICEVIEW_H

#include "Document/SaleDocument/InvoiceController.h"
#include "Document/SaleDocument/SaleView.h"
#include "SelectionWindows/SelectGoodController.h"
#include "Document/DocumentNumeratorController.h"
#include "Contractor/Contractor.h"
#include "Goods/Goods.h"
#include "Goods/GoodsModel.h"
#include "Settings/SettingsModel.h"

class InvoiceController;

class InvoiceView : public SaleView  {

public:

    InvoiceView(QWidget *parent, InvoiceController* controller);
    ~InvoiceView();
    void setTabOrders();


};

#endif // InvoiceView_H
