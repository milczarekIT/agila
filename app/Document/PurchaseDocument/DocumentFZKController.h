#ifndef DOCUMENTFZKCONTROLLER_H
#define DOCUMENTFZKCONTROLLER_H

#include "Document/PurchaseDocument/DocumentFZKView.h"
#include "Document/PurchaseDocument/DocumentFZKService.h"
#include "Document/PurchaseDocument/DocumentFZKManager.h"
#include "Document/SaleDocument/DocumentFKController.h"
#include "Tools/Print/PrintPurchaseDocumentController.h"

class DocumentFZKView;

class DocumentFZKController : public DocumentFKController
{
    Q_OBJECT

public:
    DocumentFZKController(QWidget* parent,bool edit);
    ~DocumentFZKController();
    void exec();
    void exec(QString symbol);
    void getDocumentData();
    void insertInvoiceData(Document invoice);
    void restoreTableState();
    void saveTableState();

private:
    DocumentFZKService *fzkService;
    PurchaseInvoiceService *purService;

public slots:
    void selectInvoice();
    void printDoc();
};

#endif // DOCUMENTFZKCONTROLLER_H
