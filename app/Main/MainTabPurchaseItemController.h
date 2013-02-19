#ifndef MAINTABPURCHASEITEMCONTROLLER_H
#define MAINTABPURCHASEITEMCONTROLLER_H

#include <QWidget>
#include "Main/MainTabPurchaseItem.h"
#include "Components/MessageBox.h"
#include "Document/SaleDocument/SaleDocumentTVModel.h"
#include "Document/PurchaseDocument/DocumentRRController.h"
#include "Document/CashDocument/CashDocumentController.h"
#include "Document/PurchaseDocument/PurchaseDocumentTVModel.h"
#include "Document/PurchaseDocument/DocumentNKController.h"
#include "Document/PurchaseDocument/PurchaseInvoiceController.h"
#include "Document/PurchaseDocument/DocumentFZKController.h"
#include "Main/MainTabDocumentItemController.h"
#include "Document/PurchaseDocument/DocumentNKService.h"

class MainTabPurchaseItem;

class MainTabPurchaseItemController : public MainTabDocumentItemController
{
    Q_OBJECT

private:
    MainTabPurchaseItem *view;
    PurchaseInvoiceService *purchaseInvoiceService;
    DocumentFZKService* fzkService;
    DocumentNKService*nkService;
    void initFilters();
    void initSelectingColumnVisibility();
    void restoreTableState();
    void saveTableState();

public:
    MainTabPurchaseItemController();
    ~MainTabPurchaseItemController();
    MainTabItem *getView();
    ModuleManager::Module module();

public slots:
    void addDocument(const int index);
    void dialogDocumentNKAdd();
    void dialogDocumentFZAdd();
    void dialogDocumentEdit();
    void removeDocument();
    void dialogDocumentRRAdd();
    void dialogDocumentFZKAdd();
    void changeDisabledMenuActions();
    void issuedFZK();
    void issuedKW();
    void initModel();
    void sortByColumn(int column);
    void changeColumnVisiblity(QList<int> visibleColumns);
    void printDocument();

signals:
    void issuedDocKW();
};

#endif // MAINTABPURCHASEITEMCONTROLLER_H
