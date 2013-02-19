#ifndef DocumentPAController_H
#define DocumentPAController_H

#include "Document/SaleDocument/DocumentPAView.h"
#include "Document/SaleDocument/SaleController.h"
#include "Document/SaleDocument/DocumentPAManager.h"
#include "Components/MessageBox.h"


class DocumentPAController : public SaleController  {

    Q_OBJECT

public:

   DocumentPAController(QWidget* parent,bool edit);
   ~DocumentPAController();
    void exec();
    void exec(QString symbol);

private:

    InvoiceService *invoiceService;

    bool isChangesOccured();
    void insertOrderData(Order order);
    void restoreTableState();
    void saveTableState();

public slots:
    void getDocumentData();
    void printDoc();
    void selectOrderOrFacture();

    };

#endif // DocumentPAController_H
