#include "MainTabOtherDocumentsItem.h"

MainTabOtherDocumentsItem::MainTabOtherDocumentsItem(MainTabOtherDocumentsItemController * controller)
{
    this->controller = controller;
    tableView = new TableView;
    setInterface();
    setConnections();
}

void MainTabOtherDocumentsItem::setInterface()
{
    addNK = new Button(ButtonStruct("+ NK","Dodaj notę korygującą", QSize(50,50)));
    this->layout->addWidget(addNK,0,1);
    this->layout->addWidget(new QLabel("Typ dokumentów"),0,3);
    this->layout->addWidget(new QLabel("Od"),0,6);
    this->layout->addWidget(new QLabel("Do"),0,9);
    this->layout->addWidget(otherDocuments = new QComboBox(),0,4);
    this->layout->addWidget(otherDocFrom = new DateEdit(),0,7);
    this->layout->addWidget(otherDocTo = new DateEdit(),0,10);
    this->layout->setColumnMinimumWidth(0,20);
    this->layout->setColumnMinimumWidth(2,50);
    this->layout->setColumnMinimumWidth(5,50);
    this->layout->setColumnMinimumWidth(8,50);
    this->layout->addItem(new QSpacerItem(20,0, QSizePolicy::Expanding, QSizePolicy::Minimum),0,11);
    otherDocuments->setMinimumSize(200,25);
}

void MainTabOtherDocumentsItem::setConnections()
{
    connect(addNK,SIGNAL(clicked()),controller,SLOT(dialogDocumentNKAdd()));
    connect(otherDocFrom, SIGNAL(dateChanged(QDate)),controller,SLOT(setOtherDocFromDateFilter(QDate)));
    connect(otherDocTo, SIGNAL(dateChanged(QDate)),controller,SLOT(setOtherDocToDateFilter(QDate)));
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),controller,SLOT(dialogEditDocument(QModelIndex)));
}

Button *MainTabOtherDocumentsItem::getAddNK()
{
    return addNK;
}

QComboBox *MainTabOtherDocumentsItem::getOtherDocuments()
{
    return otherDocuments;
}

DateEdit *MainTabOtherDocumentsItem::getOtherDocFrom()
{
    return otherDocFrom;
}

DateEdit *MainTabOtherDocumentsItem::getOtherDocTo()
{
    return otherDocTo;
}

TableView *MainTabOtherDocumentsItem::getTableView()
{
    return tableView;
}
