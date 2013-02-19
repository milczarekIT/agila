#ifndef DOCUMENTFMVIEW_H
#define DOCUMENTFMVIEW_H

#include "Document/SaleDocument/DocumentFMController.h"
#include "Document/SaleDocument/SaleView.h"
class DocumentFMController;

class DocumentFMView : public SaleView {
   Q_OBJECT

public:
    DocumentFMView(QWidget *parent, DocumentFMController* controller);
    ~DocumentFMView();
    void setTabOrders();
    void initGoodsTable();

};

#endif // DOCUMENTFMVIEW_H
