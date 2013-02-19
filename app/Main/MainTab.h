#ifndef MAINTAB_H
#define MAINTAB_H

#include <QTabWidget>
#include "Main/MainTabCashItemController.h"
#include "Main/MainTabCashItemController.h"
#include "Main/MainTabSaleItemController.h"
#include "Main/MainTabPriceItemController.h"
#include "Main/MainTabOrderItemController.h"
#include "Main/MainTabGoodsItemController.h"
#include "Main/MainTabStoreItemController.h"
#include "Settings/SettingsPanelController.h"
#include "Main/MainTabOthersItemController.h"
#include "Main/MainTabReportsItemController.h"
#include "Main/MainTabPurchaseItemController.h"
#include "Main/MainTabContractorsItemController.h"

class MainTab : public QTabWidget
{
    Q_OBJECT
private:
    QWidget *parent;
    SettingsPanelController *settings;
    MainTabCashItemController *cashDocuments;
    MainTabGoodsItemController *goods;
    MainTabContractorsItemController *contractors;
    MainTabPurchaseItemController *purchase;
    MainTabOrderItemController *order;
    MainTabReportsItemController *reports;
    MainTabOthersItemController *others;
    MainTabStoreItemController *store;
    MainTabSaleItemController *sale;
    MainTabCashItemController *cash;
    MainTabPriceItemController *price;

    /** wektor z MainTabItemController posiadającymi TableView */
    QVector<MainTabItemController*> mainTabItemControllersVector;

    MainTabItemController *currentMainTabItemController;

    void setItems();
    void setOptions();

public:
    explicit MainTab(QWidget *parent = 0);
    ~MainTab();
    SettingsPanelController *getSettings();
    MainTabCashItemController *getCashDocuments();
    MainTabGoodsItemController *getGoods();
    MainTabContractorsItemController *getContractors();
    MainTabPurchaseItemController *getPurchase();
    MainTabOrderItemController *getOrder();
    MainTabReportsItemController *getReports();
    MainTabOthersItemController *getOthers();
    MainTabStoreItemController *getStore();
    MainTabSaleItemController *getSale();
    MainTabCashItemController *getCash();

    void setCurrentMainTabItemController(MainTabItemController *mainTabItemController);
    MainTabItemController* getCurrentMainTabItemController();

    /** zwraca wektor z MainTabItemController posiadającymi TableView */
    QVector<MainTabItemController*> getMainTabItemControllersVector();
};

#endif // MAINTAB_H
