#ifndef DocumentRRView_H
#define DocumentRRView_H


#include "Document/PurchaseDocument/DocumentRRController.h"
#include "Document/SaleDocument/SaleView.h"
#include "Tools/Print/PrintPurchaseDocumentController.h"

class DocumentRRController;

class DocumentRRView : public SaleView  {

    Q_OBJECT

public:
    DocumentRRView(QWidget *parent, DocumentRRController* controller);
    ~DocumentRRView();
    void addOptionalComponents();
    void initOptionalConnections();
    void printDoc();
};

#endif // DocumentRRView_H
