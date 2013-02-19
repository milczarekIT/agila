#include "DocumentMenu.h"

DocumentMenu::DocumentMenu()
{
    createMenu();
}
DocumentMenu::~DocumentMenu()
{
    delete menuCash;
    delete menuOrder;
    delete menuSale;
    delete menuStore;
    delete menuPurchase;
}
void DocumentMenu::createMenu()
{
    this->menuCash = new MenuCash("Dodaj dokument kasowy");
    this->menuOrder = new MenuOrder("Dodaj zamówienie");
    this->menuPurchase = new MenuPurchase("Dodaj dokument zakupu");
    this->menuSale = new MenuSale("Dodaj dokument sprzedaży");
    this->menuStore = new MenuStore("Dodaj dokument magazynowy");
    menuDocumentAdd = new QMenu("Dodaj dokument");
    menuDocumentAdd->addMenu(menuCash->getMenuCash());
    menuDocumentAdd->addMenu(menuOrder->getMenuOrder());
    menuDocumentAdd->addMenu(menuPurchase->getMenuPurchase());
    menuDocumentAdd->addMenu(menuSale->getMenuSale());
    menuDocumentAdd->addMenu(menuStore->getMenuStore());
}

void DocumentMenu::createActions(){}

QMenu* DocumentMenu::getMenuDocument()
{
    return menuDocumentAdd;
}

QMenu* DocumentMenu::getMenuCash()
{
   return menuCash->getMenuCash();
}

QMenu* DocumentMenu::getMenuOrder()
{
   return menuOrder->getMenuOrder();
}

QMenu* DocumentMenu::getMenuPurchase()
{
   return menuPurchase->getMenuPurchase();
}

QMenu* DocumentMenu::getMenuSale()
{
   return menuSale->getMenuSale();
}

QMenu* DocumentMenu::getMenuStore()
{
   return menuStore->getMenuStore();
}
