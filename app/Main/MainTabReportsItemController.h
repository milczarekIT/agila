#ifndef MAINTABREPORTSITEMCONTROLLER_H
#define MAINTABREPORTSITEMCONTROLLER_H

#include <QWidget>
#include "Other/QtHelpers/Reflection.h"
#include "Main/MainTabReportsItem.h"
#include "Main/MainTabItemController.h"
#include "Report/Inventory/CurrentInventoryDialogController.h"
#include "Report/Inventory/CurrentInventoryGroupsDialogController.h"
#include "Report/Unpaid/UnpaidSaleDocumentDialogController.h"
#include "Report/Unpaid/UnpaidPurchaseDocumentDialogController.h"
#include "Report/Order/UnrealizedOrderDialogController.h"
#include "Report/Goods/MissingGoodsDialogController.h"
#include "Report/Goods/EndingGoodsDialogController.h"
#include "Report/Goods/OrderedGoodsDialogController.h"
#include "Report/Goods/TopGoodsDialogController.h"
#include "Report/Contractor/TopContractorsDialogController.h"
#include "Report/ReportListDialogController.h"
#include "Report/Report.h"
class MainTabReportsItem;

class MainTabReportsItemController : public MainTabItemController
{
    Q_OBJECT

private:
    MainTabReportsItem *view;

public:
    MainTabReportsItemController(QWidget *parent = 0);
    MainTabItem *getView();
    ModuleManager::Module module();
    void initModel();

public slots:
    void menuActionClicked(QAction* action);
    void generateCurrentInventory(); // Remanent bieżący
    void generateCurrentInventoryGroups(); // Remanent bieżący wg grup
    void generateUnpaidSaleDocuments(); // Niezapłacone dokumenty sprzedaży
    void generateUnpaidPurchaseDocuments(); // Niezapłacone dokumenty zakupu
    void generateUnrealizedDocumentsZK(); // Niezrealizowane zamówienia od klientów
    void generateUnrealizedDocumentsZD(); // Niezrealizowane zamówienia do dostawców
    void generateMissingGoods(); // Brakujące towary
    void generateEndingGoods(); // Kończące się towary
    void generateOrderedGoodsZK(); // Towary zamówione przez klientów
    void generateOrderedGoodsZD(); // Towary zamówione u dostawców
    void generateTopGoods(); // Najlepiej sprzedające się towary
    void generateTopContractors(); // Najlepsi klienci

    void showCurrentInventory(); // Remanent bieżący
    void showCurrentInventoryGroups(); // Remanent bieżący wg grup
    void showUnpaidSaleDocuments(); // Niezapłacone dokumenty sprzedaży
    void showUnpaidPurchaseDocuments(); // Niezapłacone dokumenty zakupu
    void showUnrealizedDocumentsZK(); // Niezrealizowane zamówienia od klientów
    void showUnrealizedDocumentsZD(); // Niezrealizowane zamówienia do dostawców
    void showMissingGoods(); // Brakujące towary
    void showEndingGoods(); // Kończące się towary
    void showOrderedGoodsZK(); // Towary zamówione przez klientów
    void showOrderedGoodsZD(); // Towary zamówione u dostawców
    void showTopGoods(); // Najlepiej sprzedające się towary
    void showTopContractors(); // Najlepsi klienci
};

#endif // MAINTABREPORTSITEMCONTROLLER_H
