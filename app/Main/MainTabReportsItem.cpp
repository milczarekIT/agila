#include "MainTabReportsItem.h"

MainTabReportsItem::MainTabReportsItem(MainTabReportsItemController * controller, QWidget *parent)
{
    this->controller = controller;
    this->parent = parent;
    setInterface();
    setConnections();
    this->setMinimumHeight(600);
}

QString MainTabReportsItem::ACTION_MENU_SHOW = "SHOW";
QString MainTabReportsItem::ACTION_MENU_GENERATE = "GENERATE";

void MainTabReportsItem::setInterface()
{
    currentInventory = new Button(ButtonStruct("Remanent bieżący"));
    currentInventory->setProperty("buttonName", "currentInventory");
    currentInventoryGroups = new Button(ButtonStruct("Remanent bieżący wg grup"));
    currentInventoryGroups->setProperty("buttonName", "currentInventoryGroups");
    unpaidSaleDocuments = new Button(ButtonStruct("Niezapłacone dokumenty sprzedaży"));
    unpaidSaleDocuments->setProperty("buttonName", "unpaidSaleDocuments");
    unpaidPurchaseDocuments = new Button(ButtonStruct("Niezapłacone dokumenty zakupu"));
    unpaidPurchaseDocuments->setProperty("buttonName", "unpaidPurchaseDocuments");
    unrealizedDocumentsZK = new Button(ButtonStruct("Niezrealizowane zamówienia od klientów"));
    unrealizedDocumentsZK->setProperty("buttonName", "unrealizedDocumentsZK");
    unrealizedDocumentsZD = new Button(ButtonStruct("Niezrealizowane zamówienia do dostawców"));
    unrealizedDocumentsZD->setProperty("buttonName", "unrealizedDocumentsZD");
    missingGoods = new Button(ButtonStruct("Brakujące towary"));
    missingGoods->setProperty("buttonName", "missingGoods");
    endingGoods = new Button(ButtonStruct("Kończące się towary"));
    endingGoods->setProperty("buttonName", "endingGoods");
    orderedGoodsZK = new Button(ButtonStruct("Towary zamówione przez klientów"));
    orderedGoodsZK->setProperty("buttonName", "orderedGoodsZK");
    orderedGoodsZD = new Button(ButtonStruct("Towary zamówione u dostawców"));
    orderedGoodsZD->setProperty("buttonName", "orderedGoodsZD");
    topGoods = new Button(ButtonStruct("Najlepiej sprzedające się towary"));
    topGoods->setProperty("buttonName", "topGoods");
    topContractors = new Button(ButtonStruct("Najwięksi klienci"));
    topContractors->setProperty("buttonName", "topContractors");

    QString title;
    QList<QPushButton*> *buttonList;

    scrollArea = new QScrollArea;
    reportsList = new QWidget();
    reportsLayout = new QVBoxLayout();
    reportsList->setLayout(reportsLayout);

    title = "Remanent";
    buttonList  = new QList<QPushButton*>();
    buttonList->push_back(currentInventory);
    buttonList->push_back(currentInventoryGroups);
    addReportGroup(title, buttonList);

    title = "Niezapłacone dokumenty";
    buttonList  = new QList<QPushButton*>();
    buttonList->push_back(unpaidSaleDocuments);
    buttonList->push_back(unpaidPurchaseDocuments);
    addReportGroup(title, buttonList);


    title = "Niezrealizowane zamówienia";
    buttonList  = new QList<QPushButton*>();
    buttonList->push_back(unrealizedDocumentsZK);
    buttonList->push_back(unrealizedDocumentsZD);
    addReportGroup(title, buttonList);

    title = "Zapasy towaru";
    buttonList  = new QList<QPushButton*>();
    buttonList->push_back(missingGoods);
    buttonList->push_back(endingGoods);
    addReportGroup(title, buttonList);

    title = "Zamówione towary";
    buttonList  = new QList<QPushButton*>();
    buttonList->push_back(orderedGoodsZK);
    buttonList->push_back(orderedGoodsZD);
    addReportGroup(title, buttonList);

    title = "Rankingi";
    buttonList  = new QList<QPushButton*>();
    buttonList->push_back(topGoods);
    buttonList->push_back(topContractors);
    addReportGroup(title, buttonList);


    scrollArea->setWidget(reportsList);
    scrollArea->setMinimumWidth(parent->width() - 50);
    scrollArea->setMinimumHeight(parent->size().height() - 200);
    scrollArea->setProperty("raportsWidget",true);
    reportsList->setProperty("raportsWidget",true);
    this->layout->addWidget(scrollArea, 0, 0, Qt::AlignCenter);
}

void MainTabReportsItem::addReportGroup(QString title, QList<QPushButton*> *buttons) {
    QGridLayout *itemLayout = new QGridLayout();
    QLabel *groupTitleLabel = new QLabel(title);
    itemLayout->setSpacing(10);
    groupTitleLabel->setMaximumHeight(20);
    itemLayout->addWidget(groupTitleLabel, 0, 0);

    int row = 1, col = 0;
    for(int i = 0; i < buttons->size(); i++)
    {
        QPushButton* button = buttons->at(i);
        button->setMinimumHeight(50);
        button->setMaximumHeight(50);
        button->setMinimumWidth(parent->width()/2 -50);
        button->setMenu(stdButtonMenu());
        button->menu()->setFixedWidth(parent->width()/2 -50);
        QList<QAction*> menuActions = button->menu()->actions();
        foreach(QAction* action, menuActions)
            action->setProperty("buttonName", button->property("buttonName").toString());

        connect(button->menu(), SIGNAL(triggered(QAction*)), controller, SLOT(menuActionClicked(QAction*)));

        if(i % 2 == 0) {
            row ++;
            col = 0;
        } else {
            col++;
        }

        itemLayout->addWidget(buttons->at(i), row, col, Qt::AlignLeft);
    }

    reportsLayout->addLayout(itemLayout);
}

QMenu* MainTabReportsItem::stdButtonMenu() {
    QMenu *menu = new QMenu();
    QAction *actionShow = new QAction(this);
    actionShow->setText("Pokaż listę stworzonych raportów");
    actionShow->setToolTip("Pokaż listę stworzonych raportów");
    actionShow->setProperty("actionName", MainTabReportsItem::ACTION_MENU_SHOW);
    menu->addAction(actionShow);

    QAction *actionGenerate = new QAction(this);
    actionGenerate->setText("Generuj nowy raport");
    actionGenerate->setToolTip("Generuj nowy raport");
    actionGenerate->setProperty("actionName", MainTabReportsItem::ACTION_MENU_GENERATE);
    menu->addAction(actionGenerate);
    return menu;
}


void MainTabReportsItem::setConnections()
{
    connect(currentInventory,SIGNAL(clicked()),controller,SLOT(generateCurrentInventory()));
    connect(currentInventoryGroups,SIGNAL(clicked()),controller,SLOT(generateCurrentInventoryGroups()));
    connect(unpaidSaleDocuments, SIGNAL(clicked()), controller, SLOT(generateUnpaidSaleDocuments()));
    connect(unpaidPurchaseDocuments, SIGNAL(clicked()), controller, SLOT(generateUnpaidPurchaseDocuments()));
    connect(unrealizedDocumentsZK, SIGNAL(clicked()), controller, SLOT(generateUnrealizedDocumentsZK()));
    connect(unrealizedDocumentsZD, SIGNAL(clicked()), controller, SLOT(generateUnrealizedDocumentsZD()));
    connect(missingGoods, SIGNAL(clicked()), controller, SLOT(generateMissingGoods()));
    connect(endingGoods, SIGNAL(clicked()), controller, SLOT(generateEndingGoods()));
    connect(orderedGoodsZK, SIGNAL(clicked()), controller, SLOT(generateOrderedGoodsZK()));
    connect(orderedGoodsZD, SIGNAL(clicked()), controller, SLOT(generateOrderedGoodsZD()));
    connect(topGoods, SIGNAL(clicked()), controller, SLOT(generateTopGoods()));
    connect(topContractors, SIGNAL(clicked()), controller, SLOT(generateTopContractors()));
}
