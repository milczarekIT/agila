#ifndef DocumentPAView_H
#define DocumentPAView_H

#include "Document/SaleDocument/DocumentPAController.h"
#include "Document/SaleDocument/SaleView.h"

class DocumentPAController;

class DocumentPAView : public SaleView  {
   Q_OBJECT

public:
    DocumentPAView(QWidget *parent, DocumentPAController* controller);
    ~DocumentPAView();
    void setTabOrders();
    void initOptionalConnections();
    void initOptionalLineEdits();
    void addOptionalComponents();
    void initOptionalButtons();

};

#endif // DocumentPAView_H
