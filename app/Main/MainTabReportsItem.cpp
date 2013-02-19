#include "MainTabReportsItem.h"

MainTabReportsItem::MainTabReportsItem(MainTabReportsItemController * controller, QWidget *parent)
{
    this->controller = controller;
    this->parent = parent;
    setInterface();
    setConnections();
    this->setMinimumHeight(600);
}

void MainTabReportsItem::setInterface()
{
    currentInventory = new Button(ButtonStruct("Remanent bieżący"));
    currentInventoryGroups = new Button(ButtonStruct("Remanent bieżący wg grup"));
    unpaidSaleDocument = new Button(ButtonStruct("Niezapłacone dokumenty sprzedaży"));
    unpaidPurchaseDocument = new Button(ButtonStruct("Niezapłacone dokumenty zakupu"));
    unrealizedDocumentsZK = new Button(ButtonStruct("Niezrealizowane zamówienia od klientów"));
    unrealizedDocumentsZD = new Button(ButtonStruct("Niezrealizowane zamówienia do dostawców"));
    missingGoods = new Button(ButtonStruct("Brakujące towary"));
    endingGoods = new Button(ButtonStruct("Kończące się towary"));
    orderedGoodsZK = new Button(ButtonStruct("Towary zamówione przez klientów"));
    orderedGoodsZD = new Button(ButtonStruct("Towary zamówione u dostawców"));
    bestSellerGoods = new Button(ButtonStruct("Najlepiej sprzedające się towary"));
    bestBuyers = new Button(ButtonStruct("Najwięksi klienci"));

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
    buttonList->push_back(unpaidSaleDocument);
    buttonList->push_back(unpaidPurchaseDocument);
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
    buttonList->push_back(bestSellerGoods);
    buttonList->push_back(bestBuyers);
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
        buttons->at(i)->setMinimumHeight(50);
        buttons->at(i)->setMaximumHeight(50);
        buttons->at(i)->setMinimumWidth(parent->width()/2 -50);
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


void MainTabReportsItem::setConnections()
{
    connect(currentInventory,SIGNAL(clicked()),controller,SLOT(dialogCurrentInvetory()));
    connect(currentInventoryGroups,SIGNAL(clicked()),controller,SLOT(dialogCurrentInvetoryGroups()));
    connect(unpaidSaleDocument, SIGNAL(clicked()), controller, SLOT(dialogUnpaidSaleDocuments()));
    connect(unpaidPurchaseDocument, SIGNAL(clicked()), controller, SLOT(dialogUnpaidPurchaseDocuments()));
    connect(unrealizedDocumentsZK, SIGNAL(clicked()), controller, SLOT(dialogUnrealizedDocumentsZK()));
    connect(unrealizedDocumentsZD, SIGNAL(clicked()), controller, SLOT(dialogUnrealizedDocumentsZD()));
    connect(missingGoods, SIGNAL(clicked()), controller, SLOT(dialogMissingGoods()));
    connect(endingGoods, SIGNAL(clicked()), controller, SLOT(dialogEndingGoods()));
    connect(orderedGoodsZK, SIGNAL(clicked()), controller, SLOT(dialogOrderedGoodsZK()));
    connect(orderedGoodsZD, SIGNAL(clicked()), controller, SLOT(dialogOrderedGoodsZD()));
    connect(bestSellerGoods, SIGNAL(clicked()), controller, SLOT(dialogTopGoods()));
    connect(bestBuyers, SIGNAL(clicked()), controller, SLOT(dialogTopContractors()));
}
