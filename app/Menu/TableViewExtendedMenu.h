#ifndef TABLEVIEWEXTENDEDMENU_H
#define TABLEVIEWEXTENDEDMENU_H

#include "Menu/TableViewStandardMenu.h"
#include "Menu/Menu.h"
#include "Menu/MenuCash.h"
#include "Menu/MenuOrder.h"
#include "Menu/MenuPurchase.h"
#include "Menu/MenuSale.h"
#include "Menu/MenuStore.h"

class TableViewExtendedMenu : public TableViewStandardMenu
{
public:
    TableViewExtendedMenu();
    ~TableViewExtendedMenu();
    void addMenuCash();
    void addMenuOrder();
    void addMenuSale();
    void addMenuPurchase();
    void addMenuStore();
    MenuSale*getMenuSale();
    MenuStore*getMenuStore();
    MenuOrder*getMenuOrder();
    MenuCash*getMenuCash();
    MenuPurchase*getMenuPurchase();


private:
    void createExtendedActions();
    void createExtendedMenu();
    MenuCash* menuCash;
    MenuOrder* menuOrder;
    MenuPurchase* menuPurchase;
    MenuSale* menuSale;
    MenuStore* menuStore;
};

#endif // TABLEVIEWEXTENDEDMENU_H
