#include "MainTabPriceItem.h"

MainTabPriceItem::MainTabPriceItem(MainTabPriceItemController * controller)
{
    this->controller = controller;
    tableView = new TableView;
    setInterface();
    setConnections();
    setMenuConnections();
}

void MainTabPriceItem::setInterface()
{
    edit = new Button(ButtonStruct("","Edytuj","edit", QSize(50,50)));
    del = new Button(ButtonStruct("","Usuń","del", QSize(50,50)));
    filterWidget = new MainTabDocumentFilterWidget("OTHER");
    buttons = createButtonsBox();

    this->layout->addWidget(new QLabel("  Dodaj dokument:  "),1,1);
    this->layout->addWidget(buttons,1,2);
    this->layout->addWidget(del,1,4);
    this->layout->addWidget(edit,1,5);
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

ButtonsList *MainTabPriceItem::createButtonsBox() {
    ButtonsList *buttons = new ButtonsList();
    buttons->addItem("Cennik", "Dodaj cennik", "CN");
    buttons->addItem("Oferty", "Dodaj oferty", "OF");
    return buttons;
}

void MainTabPriceItem::setConnections()
{
    connect(buttons,SIGNAL(activated(int)),controller,SLOT(addDocument(int)));
    connect(del,SIGNAL(clicked()),controller,SLOT(removeDocument()));
    connect(edit,SIGNAL(clicked()),controller,SLOT(dialogDocumentEdit()));
    connect(filterWidget, SIGNAL(documentTypeChanged(QString)), controller, SLOT(setDocTypeFilter(QString)));
    connect(filterWidget, SIGNAL(fromDateChanged(QDate)), controller, SLOT(setFromDateFilter(QDate)));
    connect(filterWidget, SIGNAL(toDateChanged(QDate)), controller, SLOT(setToDateFilter(QDate)));
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),controller,SLOT(dialogDocumentEdit()));
    //connect(tableView,SIGNAL(pressed(QModelIndex)),controller,SLOT(changeDisabledMenuActions()));
    connect(buttonSelectColumns, SIGNAL(clicked()), controller, SLOT(dialogSelectColumns())); // wybierz kolumn
    connect(tableView->horizontalHeader(),SIGNAL(sectionClicked(int)), controller, SLOT(sortByColumn(int)));
}

void MainTabPriceItem::setMenuConnections()
{
    /*tableView->getExtendedMenu()->addMenuSale();
    connect(tableView->getExtendedMenu()->getActionDel(),SIGNAL(triggered()),controller,SLOT(removeDocument()));
    connect(tableView->getExtendedMenu()->getActionEdit(),SIGNAL(triggered()),controller,SLOT(dialogDocumentEdit()));
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionInvoiceAdd(),SIGNAL(triggered()),controller,SLOT(dialogInvoiceAdd()));
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionFKAdd(),SIGNAL(triggered()),controller,SLOT(dialogDocumentFKAdd()));
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionFMPAdd(),SIGNAL(triggered()),controller,SLOT(dialogDocumentFMPAdd()));
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionFMAdd(),SIGNAL(triggered()),controller,SLOT(dialogDocumentFMAdd()));
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionPROAdd(),SIGNAL(triggered()),controller,SLOT(dialogDocumentPROAdd()));
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionPIAdd(),SIGNAL(triggered()),controller,SLOT(dialogDocumentPIAdd()));
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionPAAdd(),SIGNAL(triggered()),controller,SLOT(dialogDocumentPAAdd()));
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionIssuedFK(),SIGNAL(triggered()),controller,SLOT(issuedFK()));
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Cash))
    {
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionIssuedCashDocKP(),SIGNAL(triggered()),controller,SLOT(issuedKP()));
    connect(tableView->getExtendedMenu()->getMenuSale()->getActionIssuedCashDocKW(),SIGNAL(triggered()),controller,SLOT(issuedKW()));
    }
    connect(tableView->getExtendedMenu()->getActionPrintDoc(),SIGNAL(triggered()),controller,SLOT(printDocument()));*/
}

Button *MainTabPriceItem::getEditSale()
{
    return edit;
}

Button *MainTabPriceItem::getDeleteSale()
{
    return del;
}
