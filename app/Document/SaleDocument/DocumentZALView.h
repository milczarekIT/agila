#ifndef INVOICEVIEW_H
#define INVOICEVIEW_H

#include "Document/SaleDocument/DocumentZALController.h"
#include "Document/SaleDocument/SaleView.h"
#include "SelectionWindows/SelectGoodController.h"
#include "Document/DocumentNumeratorController.h"
#include "Contractor/Contractor.h"
#include "Goods/Goods.h"
#include "Goods/GoodsModel.h"
#include "Settings/SettingsModel.h"

class DocumentZALController;

class DocumentZALView : public SaleView  {

public:

    DocumentZALView(QWidget *parent, DocumentZALController* controller);
    ~DocumentZALView();
    QTableWidget* getZALTable();
    QComboBox* getComboBox();
    void setAdvance(double advance);
    void setTabOrders();
    double getLineAdvance();

private:
   void addTable();
   void initZALComponents();
   void addAlwaysUsedComponents();
   void addOptionalComponents();

   QLineEdit *lineAdvance;
   QTableWidget *zalTable;
   Button* buttonSelectZal;
   Button* buttonRemoveZal;
   QComboBox* boxDocument;
};

#endif // DocumentZALView_H
