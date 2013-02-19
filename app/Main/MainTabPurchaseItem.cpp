#include "MainTabPurchaseItem.h"

MainTabPurchaseItem::MainTabPurchaseItem(MainTabPurchaseItemController * controller)
{
    this->controller = controller;
    tableView = new TableView();
    setInterface();
    setConnections();
    setMenuConnections();
}

void MainTabPurchaseItem::setInterface()
{
    editPurchase = new Button(ButtonStruct("","Edytuj","edit", QSize(50,50)));
    deletePurchase = new Button(ButtonStruct("","Usuń","del", QSize(50,50)));
    filterWidget = new MainTabDocumentFilterWidget("PURCHASE");
    buttons = createButtonsBox();

    this->layout->addWidget(new QLabel("  Dodaj dokument:  "),1,1);
    this->layout->addWidget(buttons,1,2);
    this->layout->addWidget(deletePurchase,1,4);
    this->layout->addWidget(editPurchase,1,5);
    this->layout->addWidget(buttonSelectColumns, 1,7);
    this->layout->addWidget(filterWidget, 3,1,1,7);
    this->layout->addItem(new QSpacerItem(20,0, QSizePolicy::Expanding, QSizePolicy::Minimum),1,7,3,1);
    this->layout->setColumnMinimumWidth(0,20);
    this->layout->setColumnMinimumWidth(1,146);
    this->layout->setColumnMinimumWidth(3,60);
    this->layout->setColumnMinimumWidth(6,40);
    this->layout->setRowMinimumHeight(0,10);
    this->layout->setRowMinimumHeight(4,10);
}

ButtonsList *MainTabPurchaseItem::createButtonsBox()
{
    ButtonsList *buttons = new ButtonsList();

    buttons->addItem("Nota Korygująca","Dodaj notę korygującą", "NK");
    buttons->addItem("Rolnik Ryczaltowy","Dodaj fakturę rolnik ryczałtowy", "RR");
    buttons->addItem("Faktura Korygująca","Dodaj fakturę korygującą zakupu", "FK");
    buttons->addItem("Faktura Zakupu","Dodaj fakturę zakupu", "FZ");

    return buttons;
}

void MainTabPurchaseItem::setConnections()
{
    connect(buttons,SIGNAL(activated(int)),controller,SLOT(addDocument(int)));
    connect(editPurchase,SIGNAL(clicked()),controller,SLOT(dialogDocumentEdit()));
    connect(deletePurchase,SIGNAL(clicked()),controller,SLOT(removeDocument()));
    connect(filterWidget, SIGNAL(documentTypeChanged(QString)), controller, SLOT(setDocTypeFilter(QString)));
    connect(filterWidget, SIGNAL(fromDateChanged(QDate)), controller, SLOT(setFromDateFilter(QDate)));
    connect(filterWidget, SIGNAL(toDateChanged(QDate)), controller, SLOT(setToDateFilter(QDate)));
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),controller,SLOT(dialogDocumentEdit()));
    connect(tableView,SIGNAL(pressed(QModelIndex)),controller,SLOT(changeDisabledMenuActions()));
    connect(buttonSelectColumns, SIGNAL(clicked()), controller, SLOT(dialogSelectColumns())); // wybierz kolumny
    connect(tableView->horizontalHeader(),SIGNAL(sectionClicked(int)), controller, SLOT(sortByColumn(int)));
}

void MainTabPurchaseItem::setMenuConnections()
{
    tableView->getExtendedMenu()->addMenuPurchase();
    connect(tableView->getExtendedMenu()->getActionDel(),SIGNAL(triggered()),controller,SLOT(removeDocument()));
    connect(tableView->getExtendedMenu()->getActionEdit(),SIGNAL(triggered()),controller,SLOT(dialogDocumentEdit()));
    connect(tableView->getExtendedMenu()->getMenuPurchase()->getActionNKAdd(),SIGNAL(triggered()),controller,SLOT(dialogDocumentNKAdd()));
    connect(tableView->getExtendedMenu()->getMenuPurchase()->getActionRRAdd(),SIGNAL(triggered()),controller,SLOT(dialogDocumentRRAdd()));
    connect(tableView->getExtendedMenu()->getMenuPurchase()->getActionPurInvoiceAdd(),SIGNAL(triggered()),controller,SLOT(dialogDocumentFZAdd()));
    connect(tableView->getExtendedMenu()->getMenuPurchase()->getActionFZKAdd(),SIGNAL(triggered()),controller,SLOT(dialogDocumentFZKAdd()));
    connect(tableView->getExtendedMenu()->getMenuPurchase()->getActionIssuedFZK(),SIGNAL(triggered()),controller,SLOT(issuedFZK()));
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Cash))
    {
     connect(tableView->getExtendedMenu()->getMenuSale()->getActionIssuedCashDocKW(),SIGNAL(triggered()),controller,SLOT(issuedKW()));
    }
    connect(tableView->getExtendedMenu()->getActionPrintDoc(),SIGNAL(triggered()),controller,SLOT(printDocument()));
}

Button *MainTabPurchaseItem::getEditPurchase()
{
    return editPurchase;
}

Button *MainTabPurchaseItem::getDeletePurchase()
{
    return deletePurchase;
}

