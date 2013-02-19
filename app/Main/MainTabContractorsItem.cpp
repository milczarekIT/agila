#include "MainTabContractorsItem.h"

MainTabContractorsItem::MainTabContractorsItem(MainTabContractorsItemController *controller)
{
    this->controller = controller;
    tableView = new TableView();
    setInterface();
    setConnections();
    setMenu();
}

void MainTabContractorsItem::setInterface()
{
    addCon = new Button(ButtonStruct("Dodaj \nkontrahenta","Dodaj","contractor", QSize(144,50)));
    editCon = new Button(ButtonStruct("","Edytuj","edit", QSize(50,50)));
    deleteCon = new Button(ButtonStruct("","Usuń","del", QSize(50,50)));
    this->layout->addWidget(new QLabel("Grupa"),1,5,1,1);
    this->layout->addWidget(new QLabel("Typ"),1,8,1,1);
    this->layout->addWidget(new QLabel("Nazwa"),3,5,1,1);
    this->layout->addWidget(new QLabel("Symbol"),3,8,1,1);
    this->layout->addWidget(new QLabel("NIP"),3,11,1,1);
    this->layout->addWidget(addCon,1,1,1,3);
    this->layout->addWidget(deleteCon,3,1);
    this->layout->addWidget(editCon,3,2);
    this->layout->addWidget(buttonSelectColumns,1,12,1,1,Qt::AlignCenter);
    this->layout->addWidget(consGroup = new QComboBox(),1,6,1,1);
    this->layout->addWidget(contractorType = new QComboBox(),1,9,1,1);
    this->layout->addWidget(conFilterName = new QLineEdit(),3,6,1,1);
    this->layout->addWidget(conFilterSymbol = new QLineEdit(),3,9,1,1);
    this->layout->addWidget(conFilterNIP = new QLineEdit(),3,12,1,1);
    this->layout->addItem(new QSpacerItem(20,0, QSizePolicy::Expanding, QSizePolicy::Minimum),1,13,3,1);
    this->layout->setColumnMinimumWidth(0,20);
    this->layout->setColumnMinimumWidth(4,20);
    this->layout->setColumnMinimumWidth(7,20);
    this->layout->setColumnMinimumWidth(10,20);
    this->layout->setColumnMinimumWidth(9,20);
    this->layout->setRowMinimumHeight(0,10);
    this->layout->setRowMinimumHeight(4,10);
    consGroup->setMaximumWidth(200);
    contractorType->setMaximumWidth(200);
    conFilterName->setMaximumWidth(200);
    conFilterSymbol->setMaximumWidth(200);
    conFilterNIP->setMaximumWidth(200);
}

void MainTabContractorsItem::setConnections()
{
    connect(addCon, SIGNAL(clicked()),controller,SLOT(dialogContractorAdd()));
    connect(editCon, SIGNAL(clicked()),controller,SLOT(dialogContractorEdit()));
    connect(deleteCon, SIGNAL(clicked()),controller,SLOT(removeContractor()));
    connect(conFilterName,SIGNAL(textEdited(QString)),controller,SLOT(setConNameFilter(QString)));
    connect(conFilterNIP,SIGNAL(textEdited(QString)),controller,SLOT(setConNipFilter(QString)));
    connect(conFilterSymbol,SIGNAL(textEdited(QString)),controller,SLOT(setConSymbolFilter(QString)));
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),controller,SLOT(dialogContractorEdit()));
    connect(buttonSelectColumns, SIGNAL(clicked()), controller, SLOT(dialogSelectColumns()));
    connect(tableView->horizontalHeader(),SIGNAL(sectionClicked(int)), tableView, SLOT(sortByColumn(int)));
}

void MainTabContractorsItem::setMenu()
{
    tableView->getExtendedMenu()->removeActions();
    connect(tableView->getExtendedMenu()->getActionAdd(),SIGNAL(triggered()),controller,SLOT(dialogContractorAdd()));
    connect(tableView->getExtendedMenu()->getActionDel(),SIGNAL(triggered()),controller,SLOT(removeContractor()));
    connect(tableView->getExtendedMenu()->getActionEdit(),SIGNAL(triggered()),controller,SLOT(dialogContractorEdit()));
}

Button *MainTabContractorsItem::MainTabContractorsItem::getAddCon()
{
    return addCon;
}

Button *MainTabContractorsItem::MainTabContractorsItem::getEditCon()
{
    return editCon;
}

Button *MainTabContractorsItem::MainTabContractorsItem::getDeleteCon()
{
    return deleteCon;
}

QComboBox *MainTabContractorsItem::getConGroup()
{
    return consGroup;
}

QComboBox *MainTabContractorsItem::getContractorType()
{
    return contractorType;
}

QLineEdit *MainTabContractorsItem::getConFilterSymbol()
{
    return conFilterSymbol;
}

QLineEdit *MainTabContractorsItem::getConFilterName()
{
    return conFilterName;
}

QLineEdit *MainTabContractorsItem::getConFilterNIP()
{
    return conFilterNIP;
}
