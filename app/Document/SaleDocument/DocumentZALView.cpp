#include "DocumentZALView.h"

DocumentZALView::DocumentZALView(QWidget *parent, DocumentZALController* controller) : SaleView(parent)
{
    this->controller = controller;
    this->mainLayout = new QGridLayout();
    mainLayout->setColumnMinimumWidth(4, 150);
    mainLayout->setColumnMinimumWidth(9, 100);
    this->setLayout(mainLayout);
    this->setMinimumSize(1024,700);

    if(controller->getEdition()==true)
        this->setWindowTitle( controller->getSymbol().append(" - Edycja dokumentu"));
    else
        this->setWindowTitle( controller->getSymbol().append(" - Nowy dokument"));

    initOptionalLineEdits();
    initOptionalButtons();
    initGoodsTable();
    initZALComponents();
    initAlwaysUsedLineEdits();
    initButtons();
    initAlwaysUsedConnections();
    initOptionalConnections();
    addTable();
    addAlwaysUsedComponents();
    addOptionalComponents();
    setTabOrders();
}

void DocumentZALView::setTabOrders()
{
    this->buttonChangeContractor->setFocus();

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    {
    setTabOrder(this->buttonChangeContractor,this->buttonOrderOrFactureAdd);
    setTabOrder(this->buttonOrderOrFactureAdd, this->buttonSelectZal);
    }
    else
    setTabOrder(buttonChangeContractor,buttonSelectZal);

    setTabOrder(this->buttonSelectZal,this->buttonRemoveZal);
    setTabOrder(this->buttonRemoveZal,buttonGoodAdd);
    setTabOrder(buttonGoodAdd,buttonGoodDel);
    setTabOrder(buttonGoodDel,buttonBox);
    setTabOrder(buttonBox,this->lineDocumentPlace);
    setTabOrder(lineDocumentPlace,dateIssue);
    setTabOrder(this->dateIssue,lineDiscount);
    setTabOrder(lineDiscount,saleDate);
    setTabOrder(saleDate,this->boxDocument);
    setTabOrder(boxDocument,paymentDate);
    setTabOrder(paymentDate,checkPaid);
    setTabOrder(checkPaid,boxWayToPay);
    if(controller->getSymbol()!="ZAL" && ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        setTabOrder(boxWayToPay,this->checkStoreUpdating);
        setTabOrder(checkStoreUpdating,lineOrder);
    }
    else if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    {
        setTabOrder(boxWayToPay,lineOrder);
        setTabOrder(lineOrder,lineReceiveName);
    }
    else
        setTabOrder(boxWayToPay,lineReceiveName);
   if(controller->getSymbol()!="ZAL")
        setTabOrder(lineReceiveName,lineIssueName);
        else
    {
    setTabOrder(lineReceiveName,lineAdvance);
    setTabOrder(lineAdvance,lineIssueName);
    }
    setTabOrder(lineIssueName,buttonChangeContractor);
    lineGoodsValueDiscount->setFocusPolicy(Qt::NoFocus);
    lineGoodsValueNet->setFocusPolicy(Qt::NoFocus);
    lineGoodsValue->setFocusPolicy(Qt::NoFocus);
}

DocumentZALView::~DocumentZALView()
{
    delete mainLayout;
    delete controller;
}
void DocumentZALView::initZALComponents()
{
    buttonSelectZal = new Button(ButtonStruct("Wybierz","Zmień","chooseDoc",QSize(100,28)),QSize(25,25));
    buttonRemoveZal = new Button(ButtonStruct("Usuń  ","Usuń  ","del",QSize(100,28)),QSize(20,20));
    zalTable = new QTableWidget();
    lineAdvance = new QLineEdit();
    boxDocument = new QComboBox();
    boxDocument->addItem("FMP");
    boxDocument->addItem("FV");
    connect(buttonSelectZal,SIGNAL(clicked()),controller,SLOT(selectZAL()));
    connect(buttonRemoveZal,SIGNAL(clicked()),controller,SLOT(removeZal()));
    connect(boxDocument,SIGNAL(currentIndexChanged(int)),controller,SLOT(changedRealizedOrSymbol()));
}
void DocumentZALView::addTable()  {

  zalTable->setColumnCount(3);
  zalTable->setColumnWidth(0,150);
  zalTable->setColumnWidth(1,150);
  zalTable->setColumnWidth(2,150);
  zalTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  zalTable->setHorizontalHeaderItem(0,new QTableWidgetItem("Symbol"));
  zalTable->setHorizontalHeaderItem(1,new QTableWidgetItem("Data Wystawienia"));
  zalTable->setHorizontalHeaderItem(2,new QTableWidgetItem("Zaliczka"));
}

void DocumentZALView::addAlwaysUsedComponents() {

    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]+([.]|,)[0-9]{2}"),this);
    dateIssue->setDate(QDate::currentDate()); //data wystawienia
    mainLayout->addWidget( new QLabel("Symbol dokumentu:"), 0, 0);
    mainLayout->addWidget(lineDocumentSymbol, 0, 1);
    mainLayout->addWidget(new QLabel("Miejsce wystawienia:"), 0, 4);
    mainLayout->addWidget(lineDocumentPlace, 0, 5);
    mainLayout->addWidget(new QLabel("Data wystawienia:"),1,0);
    mainLayout->addWidget(dateIssue,1,1);
    mainLayout->addWidget(zalTable, 5, 0, 2, 5);
    mainLayout->addWidget(buttonSelectZal,5,5);
    mainLayout->addWidget(buttonRemoveZal,6,5,Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Towary:"),7,0);
    mainLayout->addWidget(goodsTable, 8, 0, 2, 9);
    mainLayout->addWidget(labelGoodsValue , 10, 4);
    mainLayout->addWidget(lineGoodsValue, 10, 5);
    mainLayout->addWidget(new QLabel("Dokument wystawił:"), 11, 7);
    mainLayout->addWidget(lineIssueName, 11, 8);
    mainLayout->addWidget(buttonGoodAdd, 7, 9);
    mainLayout->addWidget(buttonGoodDel, 8, 9);
    mainLayout->addWidget(buttonBox, 12, 0, 1, 10);
    lineGoodsValue->setValidator(validator);
    lineGoodsValue->setReadOnly(true);
    delete validator;
}

void DocumentZALView::addOptionalComponents() {

    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]+([.]|,)[0-9]{2}"),this);
    checkPaid->setChecked(true);

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        checkStoreUpdating->setChecked(true);

    contractorData->setReadOnly(true);
    paymentDate->setDate(QDate::currentDate());
    saleDate->setDate(QDate::currentDate());
    mainLayout->addWidget(new QLabel("Data płatności:"), 3, 0);
    mainLayout->addWidget(paymentDate, 3, 1);
    if(controller->getSymbol()!="FZ")
    mainLayout->addWidget(new QLabel("Data sprzedaży:"), 2, 0);
    mainLayout->addWidget(saleDate, 2, 1);
    if(controller->getSymbol()!="ZAL" && ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        mainLayout->addWidget(new QLabel("Skutek magazynowy:"),4,4);
        mainLayout->addWidget(checkStoreUpdating,4,5);
    }
    mainLayout->addWidget( new QLabel("Zapłacono:"),3,4);
    mainLayout->addWidget(checkPaid,3,5);
    mainLayout->addWidget(new QLabel("Dla dokumentu:"),2,4);
    mainLayout->addWidget(boxDocument,2,5);
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    {
    mainLayout->addWidget(new QLabel("Zamówienie nr:"),4,7);
    mainLayout->addWidget(lineOrder,4,8);
    }
    mainLayout->addWidget(new QLabel("Sposób płatności:"),4,0);
    mainLayout->addWidget(boxWayToPay,4,1);
    mainLayout->addWidget(new QLabel("Rabat[%]"),1,4);
    mainLayout->addWidget(lineDiscount,1,5);
    mainLayout->addWidget(new QLabel("Brutto po rabacie:"),11,0);
    mainLayout->addWidget(lineGoodsValueDiscount,11,1);
    if(controller->getSymbol()!="ZAL")
    {
    mainLayout->addWidget(new QLabel("Do zapłaty:"),11,4);
    lineAdvance->setReadOnly(true);
    }
    else
    mainLayout->addWidget(new QLabel("Zaliczka:"),11,4);
    mainLayout->addWidget(lineAdvance,11,5);
    lineAdvance->setValidator(validator);
    lineGoodsValueDiscount->setReadOnly(true);
    mainLayout->addWidget(contractorData,0,7,4,2);
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    mainLayout->addWidget(buttonOrderOrFactureAdd,4,9);
    if (controller->getSymbol()!="FM")
    {
        mainLayout->addWidget( new QLabel("Razem netto:"), 10, 0);
        mainLayout->addWidget(lineGoodsValueNet, 10, 1);
        lineGoodsValueNet->setReadOnly(true);
        lineGoodsValueNet->setValidator(validator);
    }
    mainLayout->addWidget(new QLabel("Dokument odebrał:"), 10, 7);
    mainLayout->addWidget(lineReceiveName, 10, 8);
    mainLayout->addWidget(buttonChangeContractor, 1, 9);
    lineDiscount->setValidator(validator);
    lineGoodsValueDiscount->setValidator(validator);
    lineDiscount->setValidator(new QRegExpValidator(QRegExp("[0-9]{2}+([.]|,)[0-9]{2}"),this));
    delete validator;
}

QTableWidget* DocumentZALView::getZALTable()
{
    return this->zalTable;
}
QComboBox* DocumentZALView::getComboBox()
{
    return this->boxDocument;
}

void DocumentZALView::setAdvance(double advance)
{
    QString str = QVariant(advance).toString();
    this->lineAdvance->setText(str.setNum(advance,',',2).replace(QRegExp("[.]"),","));
}

double DocumentZALView::getLineAdvance()
{
    return this->lineAdvance->text().toDouble();
}
