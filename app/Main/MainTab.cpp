#include "MainTab.h"

MainTab::MainTab(QWidget *parent)
{
    this->parent = parent;
    setItems();
    setOptions();
}

MainTab::~MainTab() {
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Goods))
        delete goods;

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Contractors))
        delete contractors;

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Sale))
        delete sale;

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Purchase))
        delete purchase;

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
        delete order;

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        delete store;

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Reports))
        delete reports;

    delete others;

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Settings))
        delete settings;

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Cash))
        delete cash;

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Price))
        delete price;
}

void MainTab::setItems()
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Goods))
    {
        goods = new MainTabGoodsItemController();
        this->addTab(goods->getView(), "Towary i Usługi");
        mainTabItemControllersVector.push_back(goods);
    }
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Contractors))
    {
        contractors = new MainTabContractorsItemController();
        this->addTab(contractors->getView(), "Kontrahenci");
        mainTabItemControllersVector.push_back(contractors);
    }
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Sale))
    {
        sale = new MainTabSaleItemController();
        this->addTab(sale->getView(), "Sprzedaż");
        mainTabItemControllersVector.push_back(sale);
    }
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Purchase))
    {
        purchase = new MainTabPurchaseItemController();
        this->addTab(purchase->getView(), "Zakup");
        mainTabItemControllersVector.push_back(purchase);
    }
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Cash))
    {
        cash = new MainTabCashItemController();
        this->addTab(cash->getView(), "Kasa");
        mainTabItemControllersVector.push_back(cash);
    }
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    {
        order = new MainTabOrderItemController();
        this->addTab(order->getView(), "Zamówienia");
        mainTabItemControllersVector.push_back(order);
    }
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        store = new MainTabStoreItemController();
        this->addTab(store->getView(), "Magazyn");
        mainTabItemControllersVector.push_back(store);
    }
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Price))
    {
        price = new MainTabPriceItemController();
        this->addTab(price->getView(), "Cenniki/Oferty");
        mainTabItemControllersVector.push_back(price);
    }
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Reports))
    {
        reports = new MainTabReportsItemController(parent);
        this->addTab(reports->getView(), "Raporty");
    }

    others = new MainTabOthersItemController();
    this->addTab(others->getView(), "Inne");

    settings = new SettingsPanelController();
    this->addTab(settings->getView(), "Ustawienia");

}

void MainTab::setOptions()
{
    this->setMaximumHeight(170);
    settings->getView()->setMinimumSize(950,620);
    settings->getView()->setMaximumSize(1024,620);

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Contractors))
        connect(contractors,SIGNAL(settingsChangedSignal(QString)),settings->getView()->getTabConGroups(),SLOT(setModel(QString)));

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Goods))
        connect(goods,SIGNAL(settingsChangedSignal(QString)),settings->getView()->getTabVAT(),SLOT(setModel(QString)));
}

void MainTab::setCurrentMainTabItemController(MainTabItemController *mainTabItemController) {
    this->currentMainTabItemController = mainTabItemController;
}

MainTabItemController* MainTab::getCurrentMainTabItemController() {
    return this->currentMainTabItemController;
}

QVector<MainTabItemController*> MainTab::getMainTabItemControllersVector() {
    return this->mainTabItemControllersVector;
}

SettingsPanelController *MainTab::getSettings()
{
    return settings;
}

MainTabCashItemController *MainTab::getCashDocuments()
{
    return cashDocuments;
}

MainTabGoodsItemController *MainTab::getGoods()
{
    return goods;
}

MainTabContractorsItemController *MainTab::getContractors()
{
    return contractors;
}

MainTabPurchaseItemController *MainTab::getPurchase()
{
    return purchase;
}

MainTabOrderItemController *MainTab::getOrder()
{
    return order;
}

MainTabReportsItemController *MainTab::getReports()
{
    return reports;
}

MainTabOthersItemController *MainTab::getOthers()
{
    return others;
}

MainTabStoreItemController *MainTab::getStore()
{
    return store;
}

MainTabSaleItemController *MainTab::getSale()
{
    return sale;
}

MainTabCashItemController *MainTab::getCash()
{
    return cash;
}
