#include "SettingsPanelView.h"


SettingsPanelView::SettingsPanelView(SettingsPanelController *controller,QWidget *parent) :
        QWidget(parent)
{
    this->controller = controller;

    setGraphicElements();
    setGraphicSettings();
    setInterfaceController();
    createAction();
}
void SettingsPanelView::setGraphicElements(QWidget *parent)
{
    tabOwner = new SettingsOwnerController(parent);
    tabPrint = new SettingsPrintController();
    tabOutlook = new SettingsOutlookController();
    tabUser = new SettingsUserController();
    tabConGroups = new SettingsContractorGroupsController();

    this->setLayout(mainLayout = new QGridLayout());
    createListWidget();
    this->setGeometry(QRect(10,10,980,600));
    mainLayout->addWidget(list,1,0,1,1);
    mainLayout->setColumnMinimumWidth(0,250);
    mainLayout->setRowMinimumHeight(0,40);

    createGoodsTabs();
    createDocumentsTabs();
    createStoreTabs();

    layout = new QStackedLayout();
    layout->addWidget(goodsTabWidget);
    layout->addWidget(tabConGroups->getView());
    layout->addWidget(documentsTabWidget);
    layout->addWidget(storeTabWidget);
    layout->addWidget(tabOwner->getView());
    layout->addWidget(tabUser->getView());
    //layout->addWidget(tabPrint->getView());
    layout->addWidget(tabOutlook->getView());

    mainLayout->addLayout(layout,1,1,1,1);
}

void SettingsPanelView::setGraphicSettings()
{
    list->setCurrentRow(0);
}

void SettingsPanelView::setInterfaceController()
{
    connect(list, SIGNAL(currentRowChanged(int)),layout, SLOT(setCurrentIndex(int)));
    connect(tabVAT->getView(),SIGNAL(changesWereMade()),tabMassTaxesChange,SLOT(setModel()));
    connect(tabFeatures->getView(),SIGNAL(changesWereMade()),tabGoodGroups,SLOT(chooseGroup()));
    connect(tabGoodGroups->getView(),SIGNAL(changesWereMade()),tabMassTaxesChange,SLOT(setModel()));
}

SettingsPanelView::~SettingsPanelView()
{
    action;
}

void SettingsPanelView::createListWidget()
{
    list = new QListWidget();
    list->addItem(createListWidgetItem("  Towary i usługi"));
    list->addItem(createListWidgetItem("  Kontrahenci"));
    list->addItem(createListWidgetItem("  Dokumenty"));
    list->addItem(createListWidgetItem("  Magazyny"));
    list->addItem(createListWidgetItem("  Dane podmiotu"));
    list->addItem(createListWidgetItem("  Dane użytkownika"));
    //list->addItem(createListWidgetItem("  Drukowanie"));
    list->addItem(createListWidgetItem("  Wygląd"));
    list->setTabKeyNavigation(true);
}

QListWidgetItem *SettingsPanelView::createListWidgetItem(QString value)
{
    QListWidgetItem *item = new QListWidgetItem(value);
    item->setSizeHint(QSize(50,50));
    return item;
}

void SettingsPanelView::swapFocus()
{
    if(list->currentIndex().row()==0)
        goodsTabWidget->setFocus();
    else if(list->currentIndex().row()==1)
        tabConGroups->getView()->getPushNew()->setFocus();
    else if(list->currentIndex().row()==2)
        documentsTabWidget->setFocus();
    else if(list->currentIndex().row()==4)
        tabOwner->getView()->getLineName()->setFocus();
    else if(list->currentIndex().row()==5)
        tabUser->getView()->getLineLogin()->setFocus();
    else if(list->currentIndex().row()==7)
        tabOutlook->getView()->getRadioBlue()->setFocus();
}

void SettingsPanelView::createAction()
{
    action = new QAction("SwapFocusInsideTab",this);
    action->setShortcut(Qt::SHIFT+Qt::Key_Right);
    goodsTabWidget->addAction(action);
    documentsTabWidget->addAction(action);
    tabConGroups->getView()->addAction(action);
    tabOwner->getView()->addAction(action);
    tabUser->getView()->addAction(action);
    tabOutlook->getView()->addAction(action);
    setConnctions();
}

void SettingsPanelView::setConnctions()
{
    connect(action,SIGNAL(triggered()),this,SLOT(swapFocus()));
}

void SettingsPanelView::createGoodsTabs()
{
    goodsTabWidget = new QTabWidget();
    tabVAT = new SettingsTaxesController();
    tabUnits = new SettingsUnitsController();
    tabFeatures = new SettingsFeaturesController();
    tabGoodGroups = new SettingsGoodGroupsController();
    tabMassTaxesChange = new SettingsMassTaxesChangeController();
    tabPrices = new SettingsPricesController();

    goodsTabWidget->addTab(tabVAT->getView(), "Stawki VAT");
    goodsTabWidget->addTab(tabUnits->getView(), "Jednostki miary");
    goodsTabWidget->addTab(tabGoodGroups->getView(), "Grupy");
    goodsTabWidget->addTab(tabFeatures->getView(), "Cechy grup");
    goodsTabWidget->addTab(tabMassTaxesChange->getView(), "Masowa zmiana stawek VAT");
    goodsTabWidget->addTab(tabPrices->getView(),"Narzut/Upust cen");
}

void SettingsPanelView::createDocumentsTabs()
{
    documentsTabWidget = new QTabWidget();  
    tabMOP = new SettingsMOPController();
    tabDocumentText = new SettingsDocumentTextController();
    tabDefDocPlace = new SettingsDefaultDocPlaceController();
    tabDocumentNumbering = new SettingsDocumentNumberingController();
    tabPricesSelection = new SettingsPriceSelectionController();
    documentsTabWidget->addTab(tabDocumentNumbering->getView(), "Numeracja");
    documentsTabWidget->addTab(tabMOP->getView(), "Sposoby płatności");
    documentsTabWidget->addTab(tabDocumentText->getView(), "Tekst pod dokumentem");
    documentsTabWidget->addTab(tabDefDocPlace->getView(), "Miejsce wystawienia");
    documentsTabWidget->addTab(tabPricesSelection->getView(), "Przeliczanie faktur");

}

void SettingsPanelView::createStoreTabs()
{
    storeTabWidget = new QTabWidget();
    tabMagazine = new SettingsMagazineController();
    tabTransport = new SettingsTransportController();

    storeTabWidget->addTab(tabMagazine->getView(),"Magazyny");
    storeTabWidget->addTab(tabTransport->getView(),"Transport");
}

SettingsMagazineController *SettingsPanelView::getTabMagazine() {return tabMagazine;}
SettingsTaxesController *SettingsPanelView::getTabVAT() {return tabVAT;}
SettingsUnitsController *SettingsPanelView::getTabUnits() {return tabUnits;}
SettingsContractorGroupsController *SettingsPanelView::getTabConGroups() {return tabConGroups;}
SettingsGoodGroupsController *SettingsPanelView::getTabGoodGroups() {return tabGoodGroups;}
SettingsFeaturesController *SettingsPanelView::getTabFeatures() {return tabFeatures;}
SettingsOwnerController *SettingsPanelView::getTabOwner() {return tabOwner;}
SettingsMOPController *SettingsPanelView::getTabMOP() {return tabMOP;}
SettingsDocumentTextController *SettingsPanelView::getTabDocumentText() {return tabDocumentText;}
SettingsDocumentNumberingController *SettingsPanelView::getTabDocumentNumbering() {return tabDocumentNumbering;}
SettingsPrintController *SettingsPanelView::getTabPrint() {return tabPrint;}
SettingsDefaultDocPlaceController *SettingsPanelView::getTabDefDocPlace() {return tabDefDocPlace;}
SettingsMassTaxesChangeController *SettingsPanelView::getTabMassTaxesChange() {return tabMassTaxesChange;}
SettingsUserController *SettingsPanelView::getTabUser() {return tabUser;}
SettingsTransportController *SettingsPanelView::geTabTransport() {return tabTransport;}
QTabWidget *SettingsPanelView::getGoodsTabWidget() { return goodsTabWidget;}
QTabWidget *SettingsPanelView::getDocumentsTabWidget() { return documentsTabWidget;}
QTabWidget *SettingsPanelView::getStoreTabWidget() { return storeTabWidget;}
QListWidget *SettingsPanelView::getList() { return list; }
SettingsOutlookController *SettingsPanelView::getTabOutlook() { return tabOutlook; }
