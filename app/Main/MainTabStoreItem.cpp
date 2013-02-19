#include "MainTabStoreItem.h"

MainTabStoreItem::MainTabStoreItem(MainTabStoreItemController * controller)
{
    this->controller = controller;
    tableView = new TableView;
    setInterface();
    setConnections();
    setMenu();
}

void MainTabStoreItem::setInterface()
{
    editStore = new Button(ButtonStruct("","Edytuj","edit", QSize(50,50)));
    deleteStore = new Button(ButtonStruct("","Usuń","del", QSize(50,50)));
    filterWidget = new MainTabDocumentFilterWidget("STORE");
    buttons = createButtonsBox();
    this->layout->addWidget(new QLabel("  Dodaj dokument:  "),1,1);
    this->layout->addWidget(buttons,1,2);
    this->layout->addWidget(editStore,1,5);
    this->layout->addWidget(deleteStore,1,4);
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

ButtonsList *MainTabStoreItem::createButtonsBox()
{
    ButtonsList *buttons = new ButtonsList();

    buttons->addItem("Przyjęcie Zewnętrzne","Dodaj dokument przyjęcie zewnętrzne", "PZ");
    buttons->addItem("Wydanie Zewnętrzne","Dodaje dokument wydanie zewnętrzne", "WZ");
    buttons->addItem("Rozchód Wewnętrzny","Dodaj dokument rozchód wewnętrzny", "RW");
    buttons->addItem("Przychód Wewnętrzny","Dodaj dokument przychód wewnętrzny", "PW");
    //buttons->addItem("Przesunięcie Międzymagazynowe +","Dodaj dokument przesunięcie międzymagazynowe +", "MM+");
    //buttons->addItem("Przesunięcie Międzymagazynowe -","Dodaj dokument przesunięcie międzymagazynowe -", "MM-");

    return buttons;
}

void MainTabStoreItem::setConnections()
{
    connect(buttons,SIGNAL(activated(int)),controller,SLOT(addDocument(int)));
    connect(filterWidget, SIGNAL(documentTypeChanged(QString)), controller, SLOT(setDocTypeFilter(QString)));
    connect(filterWidget, SIGNAL(fromDateChanged(QDate)), controller, SLOT(setFromDateFilter(QDate)));
    connect(filterWidget, SIGNAL(toDateChanged(QDate)), controller, SLOT(setToDateFilter(QDate)));
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),controller,SLOT(dialogEditStore()));
    connect(editStore,SIGNAL(clicked()),controller,SLOT(dialogEditStore()));
    connect(deleteStore,SIGNAL(clicked()),controller,SLOT(dialogDeleteStore()));
    connect(buttonSelectColumns, SIGNAL(clicked()), controller, SLOT(dialogSelectColumns())); // wybierz kolumny
    connect(tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), controller, SLOT(sortByColumn(int)));
}

void MainTabStoreItem::setMenu()
{
    tableView->getExtendedMenu()->addMenuStore();
    //connect(tableView->getExtendedMenu()->getActionDel(),SIGNAL(triggered()),controller,SLOT(removeDocument()));
    connect(tableView->getExtendedMenu()->getActionEdit(),SIGNAL(triggered()),controller,SLOT(dialogEditStore()));
    connect(tableView->getExtendedMenu()->getMenuStore()->getActionPWAdd(),SIGNAL(triggered()),controller,SLOT(dialogStorePWAdd()));
    connect(tableView->getExtendedMenu()->getMenuStore()->getActionPZAdd(),SIGNAL(triggered()),controller,SLOT(dialogStorePZAdd()));
    connect(tableView->getExtendedMenu()->getMenuStore()->getActionRWAdd(),SIGNAL(triggered()),controller,SLOT(dialogStoreRWAdd()));
    connect(tableView->getExtendedMenu()->getMenuStore()->getActionWZAdd(),SIGNAL(triggered()),controller,SLOT(dialogStoreWZAdd()));
    connect(tableView->getExtendedMenu()->getMenuStore()->getActionMMAdd(),SIGNAL(triggered()),controller,SLOT(dialogStoreMMAdd()));
    connect(tableView->getExtendedMenu()->getActionPrintDoc(),SIGNAL(triggered()),controller,SLOT(printDocument()));
}
