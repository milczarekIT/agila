#ifndef InvoiceCONTROLLER_H
#define InvoiceCONTROLLER_H

#include "Document/SaleDocument/InvoiceService.h"
#include "Document/MethodOfPayment.h"
#include "Document/DocumentNumeratorController.h"
#include "Document/SaleDocument/SaleController.h"
#include "Document/OrderDocument/Order.h"
#include "Document/SaleDocument/InvoiceView.h"
#include "Document/SaleDocument/InvoiceManager.h"

class InvoiceController :  public SaleController  {

    Q_OBJECT

public:

    InvoiceController(QWidget* parent, QString symbol, bool edit);
    ~InvoiceController();
    void exec();
    void exec(QString symbol);
    void insertOrderData(Order order);

private:

    InvoiceService *invoiceService;
    MOPModel *mopModel;
    void fillBox(QComboBox *box,QVector<MethodOfPayment> values);
    bool isChangesOccured();
    void restoreTableState();
    void saveTableState();

public slots:
    void getDocumentData();
    void printDoc();
    void updatePaymentDate();
    void selectOrderOrFacture();
    void changedPaid();

};

#endif // InvoiceCONTROLLER_H
