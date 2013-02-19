#include "SelectContractorView.h"

SelectContractorView::SelectContractorView(QWidget *parent, SelectContractorController * controller ):
 QDialog(parent)
{

  this->controller = controller;
  mainLayout = new QGridLayout();
  mainLayout->setColumnMinimumWidth(0,140);
  mainLayout->setColumnStretch(4,250);
  this->setLayout(mainLayout);
  this->setMaximumSize(900,500);
  this->setMinimumSize(900,500);//rozmiar okna dialogowego
  this->setWindowTitle("Dodaj nabywce");

  initTable();
  initButtons();
  initFilterWidget();
  initConnections();
  addAllComponents();

}

SelectContractorView::~SelectContractorView(){ }

void SelectContractorView::initButtons()
{
    buttonContractorAdd = new Button(ButtonStruct("Wybierz","Zmień","chooseContractor",QSize(100,28)),QSize(25,25));
    buttonContractorAddNew = new Button(ButtonStruct("Dodaj    ","Zmień","chooseContractor",QSize(100,28)),QSize(25,25));
    buttonAnuluj= new Button(ButtonStruct("Anuluj",QSize(100,28)));
    buttonEdit = new Button(ButtonStruct("Edytuj   ","Edytuj","edit",QSize(100,28)),QSize(25,25));
    buttonSelectColumns = new Button(ButtonStruct("Wybierz kolumny",QSize(150,28)));
}

void SelectContractorView::initFilterWidget() {
    filterWidget = new QWidget();
    QHBoxLayout *filterLayout = new QHBoxLayout();
    filterWidget->setLayout(filterLayout);

    filterLayout->addWidget(new QLabel("Nazwa:"));
    filterLayout->addWidget(lineContractorName = new QLineEdit());
    filterLayout->addWidget(new QLabel("Symbol:"));
    filterLayout->addWidget(lineContractorSymbol = new QLineEdit());
    filterLayout->addWidget(new QLabel("NIP:"));
    filterLayout->addWidget(lineContractorNip = new QLineEdit());
}

void SelectContractorView::addAllComponents()    {

    mainLayout->addWidget(buttonSelectColumns, 0, 8,1,1);
    mainLayout->addWidget(buttonContractorAdd, 2, 9);
    mainLayout->addWidget(buttonEdit,3,9);
    mainLayout->addWidget(buttonContractorAddNew, 4, 9);
    mainLayout->addWidget(buttonAnuluj,5,9);
    mainLayout->addWidget(new QLabel("Filtruj"), 0, 0);
    mainLayout->addWidget(filterWidget, 1, 0, 1, 9);
    mainLayout->addWidget(contractorsTable, 2, 0, 30, 9);
}

void SelectContractorView::initConnections()  {
    connect(buttonEdit,SIGNAL(clicked()),controller,SLOT(dialogContractorEdit()));
    connect(buttonContractorAddNew,SIGNAL(clicked()),controller,SLOT(addNewContractor()));
    connect(buttonContractorAdd,SIGNAL(clicked()),this,SLOT(accept()));
    connect(buttonAnuluj,SIGNAL(clicked()),controller,SLOT(setCancel()));
    connect(buttonAnuluj,SIGNAL(clicked()),this,SLOT(close()));
    connect(contractorsTable, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(accept()));
    connect(buttonSelectColumns, SIGNAL(clicked()), controller, SLOT(dialogSelectColumns()));
    connect(lineContractorName, SIGNAL(textChanged(QString)), controller, SLOT(setContractorNameFilter(QString)));
    connect(lineContractorSymbol, SIGNAL(textChanged(QString)), controller, SLOT(setContractorSymbolFilter(QString)));
    connect(lineContractorNip, SIGNAL(textChanged(QString)), controller, SLOT(setContractorNipFilter(QString)));
}

void SelectContractorView::closeEvent(QCloseEvent *event)
 {
     if (event->type() == QEvent::Close) {
         controller->setCancel();
         event->accept();}
 }

void SelectContractorView::initTable(){

    contractorsTable = new TableView();
}

TableView *SelectContractorView::getContractorsTable()
{
    return this->contractorsTable;
}

QLineEdit *SelectContractorView::getLineContractorName() { return this->lineContractorName; }
QLineEdit *SelectContractorView::getLineContractorSymbol() { return this->lineContractorSymbol; }
QLineEdit *SelectContractorView::getLineContractorNip() { return this->lineContractorNip; }
