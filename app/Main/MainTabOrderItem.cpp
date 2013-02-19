#include "MainTabOrderItem.h"

MainTabOrderItem::MainTabOrderItem(MainTabOrderItemController * controller)
{
    this->controller = controller;
    tableView = new TableView;
    setInterface();
    setConnections();
    setMenu();
}

void MainTabOrderItem::setInterface()
{

    editOrder = new Button(ButtonStruct("","Edytuj","edit", QSize(50,50)));
    deleteOrder = new Button(ButtonStruct("","Usuń","del", QSize(50,50)));
    filterWidget = new MainTabDocumentFilterWidget("ORDER");
    buttons = createButtonsBox();

    this->layout->addWidget(new QLabel("  Dodaj dokument:  "),1,1);
    this->layout->addWidget(buttons,1,2);
    this->layout->addWidget(deleteOrder,1,4);
    this->layout->addWidget(editOrder,1,5);
    this->layout->addWidget(buttonSelectColumns, 1,7);
    this->layout->addWidget(filterWidget,3,1,1,7);
    this->layout->addItem(new QSpacerItem(20,0, QSizePolicy::Expanding, QSizePolicy::Minimum),1,7,3,1);
    this->layout->setColumnMinimumWidth(0,20);
    this->layout->setColumnMinimumWidth(1,146);
    this->layout->setColumnMinimumWidth(3,60);
    this->layout->setColumnMinimumWidth(6,40);
    this->layout->setRowMinimumHeight(0,10);
    this->layout->setRowMinimumHeight(4,10);
}

ButtonsList *MainTabOrderItem::createButtonsBox()
{
    ButtonsList *buttons = new ButtonsList();

    buttons->addItem("Zamówienie od klienta","Dodaj zamówienie od klienta", "ZK");
    buttons->addItem("Zamówienie do dostawcy","Dodaj zamówienie do dostawcy", "ZD");

    return buttons;
}

void MainTabOrderItem::demoBlocker()
{
    this->setEnabled(false);
    this->setToolTip("Niedostępne w wersji demonstracyjnej!");
    this->tableView->setDisabled(true);
    tableView->setToolTip("Niedostępne w wersji demonstracyjnej!");
}

void MainTabOrderItem::setConnections()
{
    connect(buttons,SIGNAL(activated(int)),controller,SLOT(addDocument(int)));
    connect(editOrder,SIGNAL(clicked()),controller,SLOT(dialogDocumentEdit()));
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),controller,SLOT(dialogDocumentEdit()));
    connect(deleteOrder,SIGNAL(clicked()),controller,SLOT(removeDocument()));
    connect(tableView,SIGNAL(pressed(QModelIndex)),controller,SLOT(changeDisabledMenuActions()));
    connect(filterWidget, SIGNAL(documentTypeChanged(QString)), controller, SLOT(setDocTypeFilter(QString)));
    connect(filterWidget, SIGNAL(fromDateChanged(QDate)), controller, SLOT(setFromDateFilter(QDate)));
    connect(filterWidget, SIGNAL(toDateChanged(QDate)), controller, SLOT(setToDateFilter(QDate)));
    connect(buttonSelectColumns, SIGNAL(clicked()), controller, SLOT(dialogSelectColumns()));
    connect(tableView->horizontalHeader(),SIGNAL(sectionClicked(int)), controller, SLOT(sortByColumn(int)));


}

void MainTabOrderItem::setMenu()
{
    tableView->getExtendedMenu()->addMenuOrder();
    connect(tableView->getExtendedMenu()->getActionDel(),SIGNAL(triggered()),controller,SLOT(removeDocument()));
    connect(tableView->getExtendedMenu()->getActionEdit(),SIGNAL(triggered()),controller,SLOT(dialogDocumentEdit()));
    connect(tableView->getExtendedMenu()->getMenuOrder()->getActionZDAdd(),SIGNAL(triggered()),controller,SLOT(dialogOrderZDAdd()));
    connect(tableView->getExtendedMenu()->getMenuOrder()->getActionZKAdd(),SIGNAL(triggered()),controller,SLOT(dialogOrderZKAdd()));
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionFMAdd(),SIGNAL(triggered()),controller,SLOT(issuedFM()));
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionFMPAdd(),SIGNAL(triggered()),controller,SLOT(issuedFMP()));
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionInvoiceAdd(),SIGNAL(triggered()),controller,SLOT(issuedFV()));
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionPROAdd(),SIGNAL(triggered()),controller,SLOT(issuedPRO()));
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionPIAdd(),SIGNAL(triggered()),controller,SLOT(issuedPI()));
    connect(tableView->getExtendedMenu()->getMenuOrder()->getActionIssuedZD(),SIGNAL(triggered()),controller,SLOT(issuedFZ()));
    connect(tableView->getExtendedMenu()->getActionPrintDoc(),SIGNAL(triggered()),controller,SLOT(printDocument()));
}
