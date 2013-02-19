#ifndef MAINTABORDERITEMCONTROLLER_H
#define MAINTABORDERITEMCONTROLLER_H

#include <QWidget>
#include "Main/MainTabOrderItem.h"
#include "Document/OrderDocument/OrderController.h"
#include "Document/OrderDocument/OrderDocumentTVModel.h"
#include "Document/SaleDocument/InvoiceController.h"
#include "Document/PurchaseDocument/PurchaseInvoiceController.h"
#include "Document/OrderDocument/OrderService.h"
#include "Main/MainTabDocumentItemController.h"
class MainTabOrderItem;

class MainTabOrderItemController : public MainTabDocumentItemController
{
    Q_OBJECT

private:
    MainTabOrderItem *view;
    OrderService *orderService;
    void initFilters();
    void initSelectingColumnVisibility();
    void restoreTableState();
    void saveTableState();
public:
    MainTabOrderItemController();
    ~MainTabOrderItemController();
    MainTabItem *getView();

    void initModel();
    ModuleManager::Module module();

public slots:
    void addDocument(const int index);
    void dialogOrderZKAdd();
    void dialogOrderZDAdd();
    void dialogDocumentEdit();
    void removeDocument();
    void changeDisabledMenuActions();
    void issuedFV();
    void issuedFMP();
    void issuedPRO();
    void issuedPI();
    void issuedFM();
    void issuedFZ();
    void sortByColumn(int column);
    void changeColumnVisiblity(QList<int> visibleColumns);
    void printDocument();

signals:
    void issuedInvoice();
    void issuedPurchaseInvoice();
};

#endif // MAINTABORDERITEMCONTROLLER_H
