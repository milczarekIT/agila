#include "SelectGoodView.h"


SelectGoodView::SelectGoodView(QWidget *parent, SelectGoodController *controller) :
        QDialog(parent)
{
    this->controller = controller;
    mainLayout = new QGridLayout();
    mainLayout->setColumnMinimumWidth(0,140);
    mainLayout->setColumnStretch(4,250);
    this->setLayout(mainLayout);
    this->setMaximumSize(900,500);
    this->setMinimumSize(900,500);//rozmiar okna dialogowego
    this->setWindowTitle("Wybierz towary");
    initTable();
    initButtons();
    initFilterWidget();
    addAllComponents();
    initConnection();
}

SelectGoodView::~SelectGoodView()   {}

void SelectGoodView::initButtons()    {
    buttonOk = new Button(ButtonStruct("Wybierz","Zmień","chooseGood",QSize(100,28)),QSize(25,25));
    buttonCancel = new Button(ButtonStruct("Anuluj",QSize(100,28)));
    buttonAddNewGood = new Button(ButtonStruct("Dodaj    ","Zmień","chooseGood",QSize(100,28)),QSize(25,25));
    buttonEdit = new Button(ButtonStruct("Edytuj   ","Edytuj","edit",QSize(100,28)),QSize(25,25));
    buttonSelectColumns = new Button(ButtonStruct("Wybierz kolumny",QSize(150,28)));
}

void SelectGoodView::initFilterWidget() {

    filterWidget = new QWidget();
    QGridLayout *filterLayout = new QGridLayout();
    filterWidget->setLayout(filterLayout);

    filterLayout->addWidget(new QLabel("Nazwa:"), 0, 1);
    filterLayout->addWidget(lineNameFilter = new QLineEdit(), 0, 2);
    filterLayout->addWidget(new QLabel("Symbol:"), 0, 3);
    filterLayout->addWidget(lineSymbolFilter = new QLineEdit(), 0, 4);
    filterLayout->addWidget(new QLabel("Grupa dóbr:"), 1, 1);
    filterLayout->addWidget(chooseGoodGroup = new QComboBox(), 1, 2);
    filterLayout->addWidget(buttonSelectColumns, 1, 4, Qt::AlignRight);
}

void SelectGoodView::addAllComponents()   {

    mainLayout->addWidget(buttonOk,3,9);
    mainLayout->addWidget(buttonEdit,4,9);
    mainLayout->addWidget(buttonAddNewGood,5,9);
    mainLayout->addWidget(buttonCancel,6,9);
    mainLayout->addWidget(new QLabel("Filtruj"), 0, 0, 1, 2);
    mainLayout->addWidget(filterWidget, 1, 0, 1, 9);
    mainLayout->addWidget(goodsTable,4,0,30,9);
    mainLayout->addWidget(markAll = new QCheckBox,4,1,1,1);
    mainLayout->setColumnMinimumWidth(0,15);
    markAll->setMinimumWidth(40);
    markAll->hide();
}

void SelectGoodView::initConnection() {

    connect(buttonCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(buttonCancel,SIGNAL(clicked()),controller,SLOT(setCancel()));
    connect(buttonOk,SIGNAL(clicked()), controller,SLOT(selectGoods()));
    connect(buttonOk,SIGNAL(clicked()), this ,SLOT(accept()));
    connect(buttonEdit,SIGNAL(clicked()),controller,SLOT(dialogGoodsEdit()));
    connect(buttonAddNewGood, SIGNAL(clicked()),controller, SLOT(dialogGoodAdd()));
    connect(buttonSelectColumns, SIGNAL(clicked()), controller, SLOT(dialogSelectColumns()));
    connect(lineNameFilter, SIGNAL(textChanged(QString)), controller, SLOT(setGoodsNameFilter(QString)));
    connect(lineSymbolFilter, SIGNAL(textChanged(QString)), controller, SLOT(setGoodsSymbolFilter(QString)));
    connect(chooseGoodGroup, SIGNAL(activated(int)), controller, SLOT(setGoodsGoodGroupFilter(int)));
    connect(goodsTable, SIGNAL(doubleClicked(QModelIndex)), controller, SLOT(selectGoods()));
    connect(markAll,SIGNAL(clicked(bool)),controller,SLOT(markAllItems(bool)));
    connect(controller, SIGNAL(rowCountChanged(int)),controller,SLOT(showingMarkAll(int)));
}

void SelectGoodView::closeEvent(QCloseEvent *event)
 {
     if (event->type() == QEvent::Close) {
         controller->setCancel();
         event->accept();}
 }

void SelectGoodView::initTable() {

    goodsTable = new TableView();
}

TableView* SelectGoodView::getGoodsTable() {
    return this->goodsTable;
}

QComboBox *SelectGoodView::getChooseGoodGroup() {
    return this->chooseGoodGroup;
}

QWidget *SelectGoodView::getFilterWidget() {
    return this->filterWidget;
}

QGridLayout *SelectGoodView::getFilterLayout() {
    return this->filterLayout;
}

QGridLayout* SelectGoodView::getMainLayout() {
    return this->mainLayout;
}

QCheckBox *SelectGoodView::getMarkAll() {
    return this->markAll;
}
