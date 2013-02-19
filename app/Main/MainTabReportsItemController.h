#ifndef MAINTABREPORTSITEMCONTROLLER_H
#define MAINTABREPORTSITEMCONTROLLER_H

#include <QWidget>
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
    void dialogCurrentInvetory(); // Remanent bieżący
    void dialogCurrentInvetoryGroups(); // Remanent bieżący wg grup
    void dialogUnpaidSaleDocuments(); // Niezapłacone dokumenty sprzedaży
    void dialogUnpaidPurchaseDocuments(); // Niezapłacone dokumenty zakupu
    void dialogUnrealizedDocumentsZK(); // Niezrealizowane zamówienia od klientów
    void dialogUnrealizedDocumentsZD(); // Niezrealizowane zamówienia do dostawców
    void dialogMissingGoods(); // Brakujące towary
    void dialogEndingGoods(); // Kończące się towary
    void dialogOrderedGoodsZK(); // Towary zamówione przez klientów
    void dialogOrderedGoodsZD(); // Towary zamówione u dostawców
    void dialogTopGoods(); // Najlepiej sprzedające się towary
    void dialogTopContractors(); // Najlepsi klienci


};

#endif // MAINTABREPORTSITEMCONTROLLER_H
