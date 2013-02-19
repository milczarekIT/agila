#ifndef MAINTABSALEITEMCONTROLLER_H
#define MAINTABSALEITEMCONTROLLER_H

#include <QWidget>
#include "Main/MainTabSaleItem.h"
#include "Document/DocumentInfo.h"
#include "Document/DocumentInfoModel.h"
#include "Document/SaleDocument/InvoiceService.h"
#include "Document/SaleDocument/InvoiceController.h"
#include "Document/SaleDocument/SaleDocumentTVModel.h"
#include "Document/SaleDocument/DocumentFKController.h"
#include "Document/SaleDocument/DocumentPAController.h"
#include "Document/SaleDocument/DocumentFMController.h"
#include "Document/CashDocument/CashDocumentController.h"
#include "Document/SaleDocument/DocumentZALController.h"
#include "Main/MainTabDocumentItemController.h"

class MainTabSaleItem;

class MainTabSaleItemController : public MainTabDocumentItemController
{
    Q_OBJECT
private:
    MainTabSaleItem *view;
    InvoiceService *invoiceService;
    DocumentFKService *fkService;
    DocumentZALService* zalService;
    void initFilters();
    float checkAmount();

    void initSelectingColumnVisibility();
    void restoreTableState();
    void saveTableState();

public:
    MainTabSaleItemController();
    ~MainTabSaleItemController();
    MainTabItem *getView();
    ModuleManager::Module module();

public slots:
    void addDocument(const int index);
    void initModel();
    void dialogInvoiceAdd();
    void dialogDocumentFMPAdd();
    void dialogDocumentPROAdd();
    void dialogDocumentPIAdd();
    void dialogDocumentZALAdd();
    void dialogDocumentRZLAdd();
    void dialogDocumentPAAdd();
    void dialogDocumentFKAdd();
    void dialogDocumentFMAdd();
    void dialogDocumentEdit();
    void removeDocument();
    void changeDisabledMenuActions();
    void issuedFK();
    void issuedKW();
    void issuedKP();
    void sortByColumn(int column);
    void changeColumnVisiblity(QList<int> visibleColumns);
    void printDocument();

signals:
    void issuedCashDoc();
};

#endif // MAINTABSALEITEMCONTROLLER_H
