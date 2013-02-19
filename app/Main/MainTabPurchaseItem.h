#ifndef MAINTABPURCHASEITEM_H
#define MAINTABPURCHASEITEM_H

#include "Main/MainTabItem.h"
#include "Components/Button.h"
#include "Components/TableView.h"
#include "Components/ButtonsList.h"
#include "Main/MainTabDocumentItem.h"
#include "Main/MainTabDocumentFilterWidget.h"
#include "Main/MainTabPurchaseItemController.h"
class MainTabPurchaseItemController;

class MainTabPurchaseItem : public MainTabDocumentItem
{
private:
    QComboBox *buttons;
    Button *editPurchase;
    Button *deletePurchase;
    MainTabPurchaseItemController *controller;
    void setInterface();
    void setConnections();
    void setMenuConnections();
    void demoBlocker();
    ButtonsList *createButtonsBox();

public:
    MainTabPurchaseItem(MainTabPurchaseItemController *controller);
    Button *getEditPurchase();
    Button *getDeletePurchase();
};

#endif // MAINTABPURCHASEITEM_H
