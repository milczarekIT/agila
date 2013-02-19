#include "MainTabCashItem.h"

MainTabCashItem::MainTabCashItem(MainTabCashItemController *controller)
{
    this->controller = controller;
    tableView = new TableView;
    setInterface();
    setConnections();
    setMenu();
}


void MainTabCashItem::setInterface()
{
    editDocument = new Button(ButtonStruct("","Edytuj dokument","edit", QSize(50,50)));
    deleteDocument = new Button(ButtonStruct("","Usuń dokument","del", QSize(50,50)));
    filterWidget = new MainTabDocumentFilterWidget("CASH");
    buttons = createButtonsBox();

    this->layout->addWidget(new QLabel("  Dodaj dokument:  "),1,1);
    this->layout->addWidget(buttons,1,2);
    this->layout->addWidget(deleteDocument,1,4);
    this->layout->addWidget(editDocument,1,5);
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

ButtonsList *MainTabCashItem::createButtonsBox()
{
    ButtonsList *buttons = new ButtonsList();

    buttons->addItem("Kasa Przyjmie","Dodaj dowód wpłaty", "KP");
    buttons->addItem("Kasa Wyda","Dodaj dowód wypłaty", "KW");

    return buttons;
}

void MainTabCashItem::setConnections()
{
    connect(buttons,SIGNAL(activated(int)),controller,SLOT(addDocument(int)));
    connect(editDocument,SIGNAL(clicked()),controller,SLOT(dialogDocumentEdit()));
    connect(deleteDocument,SIGNAL(clicked()),controller,SLOT(documentRemove()));
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),controller,SLOT(dialogDocumentEdit()));
    connect(filterWidget, SIGNAL(documentTypeChanged(QString)), controller, SLOT(setDocTypeFilter(QString)));
    connect(filterWidget, SIGNAL(fromDateChanged(QDate)), controller, SLOT(setFromDateFilter(QDate)));
    connect(filterWidget, SIGNAL(toDateChanged(QDate)), controller, SLOT(setToDateFilter(QDate)));
    connect(buttonSelectColumns, SIGNAL(clicked()), controller, SLOT(dialogSelectColumns()));
    connect(tableView->horizontalHeader(),SIGNAL(sectionClicked(int)), controller, SLOT(sortByColumn(int)));
}

void MainTabCashItem::setMenu()
{
    tableView->getExtendedMenu()->addMenuCash();
    connect(tableView->getExtendedMenu()->getActionDel(),SIGNAL(triggered()),controller,SLOT(documentRemove()));
    connect(tableView->getExtendedMenu()->getActionEdit(),SIGNAL(triggered()),controller,SLOT(dialogDocumentEdit()));
    connect(tableView->getExtendedMenu()->getMenuCash()->getActionKWAdd(),SIGNAL(triggered()),controller,SLOT(dialogDocumentKWAdd()));
    connect(tableView->getExtendedMenu()->getMenuCash()->getActionKPAdd(),SIGNAL(triggered()),controller,SLOT(dialogDocumentKPAdd()));
}

