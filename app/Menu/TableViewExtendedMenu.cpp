#include "TableViewExtendedMenu.h"

TableViewExtendedMenu::TableViewExtendedMenu()
{
    this->menuCash = new MenuCash("Dodaj dokument kasowy");
    this->menuOrder = new MenuOrder("Dodaj zamówienie");
    this->menuPurchase = new MenuPurchase("Dodaj dokument zakupu");
    this->menuSale = new MenuSale("Dodaj dokument sprzedaży");
    this->menuStore = new MenuStore("Dodaj dokument magazynowy");
}

TableViewExtendedMenu::~TableViewExtendedMenu()
{
    delete menuCash;
    delete menuOrder;
    delete menuSale;
    delete menuStore;
    delete menuPurchase;
}

void TableViewExtendedMenu::addMenuCash()
{
    menuStandard->addMenu(this->menuCash->getMenuCash());
}

void TableViewExtendedMenu::addMenuOrder()
{
    menuStandard->addMenu(this->menuOrder->getMenuOrder());
    menuSale->setName("Wystaw fakturę sprzedaży");
    menuSale->getActionFKAdd()->setVisible(false);
    menuSale->getActionPAAdd()->setVisible(false);
    menuStandard->addMenu(this->menuSale->getMenuSale());
    menuStandard->addAction(this->menuOrder->getActionIssuedZD());
}

void TableViewExtendedMenu::addMenuPurchase()
{
    menuStandard->addMenu(this->menuPurchase->getMenuPurchase());
    menuStandard->addAction(this->menuPurchase->getActionIssuedFZK());
    menuStandard->addAction(this->menuPurchase->getActionIssuedKW());
}

void TableViewExtendedMenu::addMenuSale()
{
    menuStandard->addMenu(this->menuSale->getMenuSale());
    menuStandard->addAction(this->menuSale->getActionIssuedFK());
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Cash))
    {
    menuStandard->addAction(this->menuSale->getActionIssuedCashDocKP());
    menuStandard->addAction(this->menuSale->getActionIssuedCashDocKW());
    }
}

void TableViewExtendedMenu::addMenuStore()
{
    menuStandard->addMenu(this->menuStore->getMenuStore());
}

MenuSale*TableViewExtendedMenu::getMenuSale(){return this->menuSale;}
MenuOrder*TableViewExtendedMenu::getMenuOrder(){return this->menuOrder;}
MenuCash*TableViewExtendedMenu::getMenuCash(){return this->menuCash;}
MenuPurchase*TableViewExtendedMenu::getMenuPurchase(){return this->menuPurchase;}
MenuStore*TableViewExtendedMenu::getMenuStore(){return this->menuStore;}

