#ifndef PURCHASECONTROLLER_H
#define PURCHASECONTROLLER_H

#include "Document/SaleDocument/SaleController.h"
#include "Document/PurchaseDocument/PurchaseInvoiceService.h"
#include "Tools/Print/PrintPurchaseDocumentController.h"

class PurchaseController : public SaleController
{
    Q_OBJECT

public:
    PurchaseController();
    ~PurchaseController();

protected:

    PurchaseInvoiceModel *purModel;
    PurchaseInvoiceService *purchaseInvoiceService;
    MOPModel * mopModel;
    void fillBox(QComboBox *box,QVector<MethodOfPayment> values);
    bool isChangesOccured();
    void printDoc();

public slots:

    void updatePaymentDate();
    void changedPaid();
};

#endif // PURCHASECONTROLLER_H
