#ifndef PURCHASEINVOICECONTROLLER_H
#define PURCHASEINVOICECONTROLLER_H

#include "Document/PurchaseDocument/PurchaseInvoiceView.h"
#include "Document/PurchaseDocument/PurchaseInvoice.h"
#include "Document/PurchaseDocument/PurchaseController.h"
#include "Document/PurchaseDocument/PurchaseManager.h"

class PurchaseInvoiceController : public PurchaseController  {

    Q_OBJECT

public:
    PurchaseInvoiceController(QWidget* parent, QString symbol, bool edit);
    ~PurchaseInvoiceController();

    void exec();
    void exec(QString symbol);
    void insertOrderData(Order order);
    void restoreTableState();
    void saveTableState();


public slots:
    void getDocumentData();
    void selectOrderOrFacture();

    };

#endif // PurchaseInvoiceController_H
