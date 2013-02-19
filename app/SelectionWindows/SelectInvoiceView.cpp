#include "SelectInvoiceView.h"

SelectInvoiceView::SelectInvoiceView(QWidget *parent, SelectInvoiceController * controller) :
        QDialog(parent)
{
    this->controllerInvoice = controller;
    init();
    initInvoiceConnections();
}

SelectInvoiceView::SelectInvoiceView(QWidget *parent, SelectOrderController * controller) :
        QDialog(parent)
{
    this->controllerOrder = controller;
    init();
    initOrderConnections();
}

void SelectInvoiceView::init()
{

    mainLayout = new QGridLayout();
    mainLayout->setColumnMinimumWidth(0,140);
    mainLayout->setColumnStretch(4,250);
    this->setLayout(mainLayout);
    this->setMaximumSize(900,500);
    this->setMinimumSize(900,500);//rozmiar okna dialogowego
    this->setWindowTitle("Wybierz fakturę");

    initTable();
    initButtons();
    initFilterWidget();
    initConnections();
    addAllComponents();

}

SelectInvoiceView::~SelectInvoiceView()
{

}

void SelectInvoiceView::initButtons()  {

    buttonInvoiceSelect = new Button(ButtonStruct("Wybierz","Zmień","chooseDoc",QSize(100,28)),QSize(25,25));
    buttonCancel = new Button(ButtonStruct("Anuluj",QSize(100,28)));
    buttonSelectColumns = new Button(ButtonStruct("Wybierz kolumny",QSize(150,28)));

}

void SelectInvoiceView::initFilterWidget() {
    filterWidget = new QWidget();
    QHBoxLayout *filterLayout = new QHBoxLayout();
    filterWidget->setLayout(filterLayout);

    filterLayout->addWidget(new QLabel("Symbol:"));
    filterLayout->addWidget(lineSymbolFilter = new QLineEdit());
}

void SelectInvoiceView::addAllComponents()    {

    mainLayout->addWidget(buttonSelectColumns, 0, 8,1,1);
    mainLayout->addWidget(buttonInvoiceSelect, 4, 9);
    mainLayout->addWidget(buttonCancel, 5, 9);
    mainLayout->addWidget(new QLabel("Filtruj"), 0, 0);
    mainLayout->addWidget(filterWidget, 1, 0, 1, 9);
    mainLayout->addWidget(invoiceTable, 4, 0, 30, 9);
 }

void SelectInvoiceView::initConnections()
{
    connect(buttonInvoiceSelect,SIGNAL(clicked()),this,SLOT(accept()));
    connect(buttonCancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(invoiceTable, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(accept()));
}

void SelectInvoiceView::initInvoiceConnections()
{
     connect(buttonCancel,SIGNAL(clicked()),controllerInvoice,SLOT(setCancel()));
     connect(buttonSelectColumns, SIGNAL(clicked()), controllerInvoice, SLOT(dialogSelectColumns()));
     connect(lineSymbolFilter, SIGNAL(textChanged(QString)), controllerInvoice, SLOT(setDocumentSymbolFilter(QString)));

}

void SelectInvoiceView::closeEvent(QCloseEvent *event)
 {
     if (event->type() == QEvent::Close) {
         controllerInvoice->setCancel();
         event->accept();
     }
 }

void SelectInvoiceView::initOrderConnections()
{
     connect(buttonCancel,SIGNAL(clicked()),controllerOrder,SLOT(setCancel()));
     connect(buttonSelectColumns, SIGNAL(clicked()), controllerOrder, SLOT(dialogSelectColumns()));
     connect(lineSymbolFilter, SIGNAL(textChanged(QString)), controllerOrder, SLOT(setDocumentSymbolFilter(QString)));
}

void SelectInvoiceView::initTable(){

    invoiceTable = new TableView();

}

TableView* SelectInvoiceView::getInvoiceTable() { return invoiceTable; }
