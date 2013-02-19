#ifndef DOCUMENTMENU_H
#define DOCUMENTMENU_H

#include "Menu/Menu.h"
#include "Menu/MenuCash.h"
#include "Menu/MenuOrder.h"
#include "Menu/MenuPurchase.h"
#include "Menu/MenuSale.h"
#include "Menu/MenuStore.h"

class DocumentMenu : public Menu
{

public:
    DocumentMenu();
    ~DocumentMenu();
    void createMenu();
    void createActions();
    QMenu* getMenuDocument();
    QMenu* getMenuCash();
    QMenu* getMenuOrder();
    QMenu* getMenuPurchase();
    QMenu* getMenuSale();
    QMenu* getMenuStore();

private:
    QMenu* menuDocumentAdd;
    MenuCash* menuCash;
    MenuOrder* menuOrder;
    MenuPurchase* menuPurchase;
    MenuSale* menuSale;
    MenuStore* menuStore;
};

#endif // DOCUMENTMENU_H
