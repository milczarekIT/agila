#include "MainTabGoodsItem.h"

MainTabGoodsItem::MainTabGoodsItem(MainTabGoodsItemController *controller)
{
    this->controller = controller;
    tableView = new TableView();
    setInterface();
    setConnections();
    setMenu();
}

void MainTabGoodsItem::setInterface()
{
    addGood = new Button(ButtonStruct(" Dodaj towar","Dodaj","good", QSize(144,50)));
    editGood = new Button(ButtonStruct("","Edytuj","edit", QSize(50,50)));
    deleteGood = new Button(ButtonStruct("","Usuń","del", QSize(50,50)));
    this->layout->addWidget(new QLabel("Grupa"),1,7);
    this->layout->addWidget(new QLabel("Poziom cen"),1,10);
    this->layout->addWidget(new QLabel("Nazwa"),3,7);
    this->layout->addWidget(new QLabel("Symbol"),3,10);
    this->layout->addWidget(addGood,1,1,1,3);
    this->layout->addWidget(deleteGood,3,1);
    this->layout->addWidget(editGood,3,2);
    this->layout->addWidget(goodsGroup = new QComboBox(),1,8);
    this->layout->addWidget(priceLevel = new QComboBox(),1,11);
    this->layout->addWidget(buttonSelectColumns,1,12,1,1,Qt::AlignLeft);
    this->layout->addWidget(gFilterName = new QLineEdit(""),3,8);
    this->layout->addWidget(gFilterSymbol = new QLineEdit(""),3,11);
    this->layout->addItem(new QSpacerItem(20,0, QSizePolicy::Expanding, QSizePolicy::Minimum),1,12,3,1);
    this->layout->setColumnMinimumWidth(0,20);
    this->layout->setColumnMinimumWidth(6,20);
    this->layout->setColumnMinimumWidth(9,20);
    this->layout->setRowMinimumHeight(0,10);
    this->layout->setRowMinimumHeight(4,10);
    goodsGroup->setMaximumWidth(200);
    priceLevel->setMaximumWidth(200);
    gFilterName->setMaximumWidth(200);
    gFilterSymbol->setMaximumWidth(200);
}

void MainTabGoodsItem::setConnections()
{
    connect(addGood,SIGNAL(clicked()),controller,SLOT(dialogGoodsAdd()));
    connect(deleteGood,SIGNAL(clicked()),controller,SLOT(removeGood()));
    connect(gFilterName, SIGNAL(textEdited(QString)), controller, SLOT(setGoodsNameFilter(QString)));
    connect(gFilterSymbol, SIGNAL(textEdited(QString)), controller, SLOT(setGoodsSymbolFilter(QString)));
    connect(editGood,SIGNAL(clicked()),controller,SLOT(dialogGoodsEdit()));
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),controller,SLOT(dialogGoodsEdit()));
    connect(buttonSelectColumns, SIGNAL(clicked()), controller, SLOT(dialogSelectColumns()));
    connect(tableView->horizontalHeader(),SIGNAL(sectionClicked(int)), tableView, SLOT(sortByColumn(int)));
}

void MainTabGoodsItem::setMenu()
{
    tableView->getExtendedMenu()->removeActions();
    connect(tableView->getExtendedMenu()->getActionAdd(),SIGNAL(triggered()),controller,SLOT(dialogGoodsAdd()));
    connect(tableView->getExtendedMenu()->getActionDel(),SIGNAL(triggered()),controller,SLOT(removeGood()));
    connect(tableView->getExtendedMenu()->getActionEdit(),SIGNAL(triggered()),controller,SLOT(dialogGoodsEdit()));
}

Button *MainTabGoodsItem::MainTabGoodsItem::getAddGood()
{
    return addGood;
}

Button *MainTabGoodsItem::MainTabGoodsItem::getEditGood()
{
    return editGood;
}

Button *MainTabGoodsItem::MainTabGoodsItem::getDeleteGood()
{
    return deleteGood;
}

QComboBox *MainTabGoodsItem::getGoodsGroup()
{
    return goodsGroup;
}

QComboBox *MainTabGoodsItem::getPriceLevel()
{
    return priceLevel;
}

QLineEdit *MainTabGoodsItem::getGFilterSymbol()
{
    return gFilterSymbol;
}

QLineEdit *MainTabGoodsItem::getGFilterName()
{
    return gFilterName;
}


