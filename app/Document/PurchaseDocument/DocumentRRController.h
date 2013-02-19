#ifndef DocumentRRController_H
#define DocumentRRController_H

#include "Document/PurchaseDocument/DocumentRRView.h"
#include "Document/PurchaseDocument/PurchaseController.h"
#include "Document/PurchaseDocument/PurchaseInvoice.h"
#include "Document/PurchaseDocument/PurchaseInvoiceService.h"
#include "Document/PurchaseDocument/PurchaseManager.h"

class DocumentRRController : public PurchaseController  {
    Q_OBJECT

public:
    DocumentRRController(QWidget* parent, QString symbol, bool edit);
    ~DocumentRRController();

     void exec();
     void exec(QString symbol);

private:
     void restoreTableState();
     void saveTableState();

 protected slots:
     void getDocumentData();
    };

#endif // DocumentRRController_H
