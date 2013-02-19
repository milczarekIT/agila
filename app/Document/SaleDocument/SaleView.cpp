#include "SaleView.h"

SaleView::SaleView(QWidget* parent) : DocumentView(parent)
{
}

SaleView::~SaleView(){}

void SaleView::initOptionalConnections()  {
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    connect(buttonOrderOrFactureAdd,SIGNAL(clicked()),controller,SLOT(selectOrderOrFacture()));
    connect(buttonChangeContractor,SIGNAL(clicked()),controller,SLOT(selectContractor()));
    connect(boxWayToPay,SIGNAL(currentIndexChanged(int)),controller,SLOT(updatePaymentDate()));
    connect(paymentDate,SIGNAL(dateChanged(QDate)),controller,SLOT(changedPaid()));
    connect(lineDiscount,SIGNAL(textEdited(QString)),controller,SLOT(discountChanged()));
}



void SaleView::addOptionalComponents() {

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

    int row = 2;
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        mainLayout->addWidget(new QLabel("Skutek magazynowy:"),row,4);
        mainLayout->addWidget(checkStoreUpdating,row,5);
        row++;
    }
    mainLayout->addWidget( new QLabel("Zapłacono:"),row,4);
    mainLayout->addWidget(checkPaid,row,5);
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    {
    mainLayout->addWidget(new QLabel("Zamówienie nr:"),4,7);
    mainLayout->addWidget(lineOrder,4,8);
    }
    mainLayout->addWidget(new QLabel("Sposób płatności:"),4,0);
    mainLayout->addWidget(boxWayToPay,4,1);
    mainLayout->addWidget(new QLabel("Rabat[%]"),1,4);
    mainLayout->addWidget(lineDiscount,1,5);
    mainLayout->addWidget(new QLabel("Brutto po rabacie:"),8,7);
    mainLayout->addWidget(lineGoodsValueDiscount,8,8);
    lineGoodsValueDiscount->setReadOnly(true);
    mainLayout->addWidget(contractorData,0,7,4,2);
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    mainLayout->addWidget(buttonOrderOrFactureAdd,4,9);
    if (controller->getSymbol()!="FM")
    {
        mainLayout->addWidget( new QLabel("Razem netto:"), 8, 0);
        mainLayout->addWidget(lineGoodsValueNet, 8, 1);
        lineGoodsValueNet->setReadOnly(true);
        lineGoodsValueNet->setValidator(validator);
    }
    mainLayout->addWidget(new QLabel("Dokument odebrał:"), 9, 7);
    mainLayout->addWidget(lineReceiveName, 9, 8);
    mainLayout->addWidget(buttonChangeContractor, 1, 9);
    lineDiscount->setValidator(validator);
    lineGoodsValueDiscount->setValidator(validator);
}

void SaleView::initOptionalLineEdits() {

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    lineOrder = new QLineEdit();
    lineDiscount = new QLineEdit();
    contractorData= new QTextEdit("Wprowadź dane kontrahenta");
    if (controller->getSymbol()!="FM")
        lineGoodsValueNet= new QLineEdit();
    lineReceiveName = new QLineEdit();
    lineGoodsValueDiscount = new QLineEdit();
    saleDate = new DateEdit();
    paymentDate = new DateEdit();//data wystawienia dokumentu
    boxWayToPay = new QComboBox();
    checkPaid = new QCheckBox();

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        checkStoreUpdating = new QCheckBox();
}

void SaleView::initOptionalButtons()
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    buttonOrderOrFactureAdd = new Button(ButtonStruct("Wybierz","Wybierz","chooseDoc",QSize(100,28)),QSize(25,25));
    buttonChangeContractor = new Button(ButtonStruct("Zmień","Zmień","chooseContractor",QSize(100,28)),QSize(25,25));
}

void SaleView::initGoodsTable()  {

  goodsTable = new QTableWidget();
  goodsTable->setColumnCount(6);
  goodsTable->setColumnWidth(0,300);
  goodsTable->setColumnWidth(1,230);
  goodsTable->setColumnWidth(2,120);
  goodsTable->setColumnWidth(3,120);
  goodsTable->setColumnWidth(4,110);
  goodsTable->setColumnWidth(5,110);
  goodsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  setHeaders(0,new QTableWidgetItem("Nazwa"));
  setHeaders(1,new QTableWidgetItem("Symbol"));
  setHeaders(2,new QTableWidgetItem("Cena Netto"));
  setHeaders(3,new QTableWidgetItem("Cena Brutto"));
  setHeaders(4,new QTableWidgetItem("Ilość"));
  setHeaders(5,new QTableWidgetItem("Wartość brutto"));
}

DateEdit* SaleView::getPaymentDate(){return this->paymentDate;}
QComboBox *SaleView::getWayToPay(){return this->boxWayToPay;}
QLineEdit *SaleView::getDiscountOrWaybillNo(){return this->lineDiscount;}
QLineEdit *SaleView::getLineOrderSymbol(){
    return this->lineOrder;
}
double SaleView::getLineGoodsValueNet(){return this->lineGoodsValueNet->text().toDouble();}
double SaleView::getLineGoodsValueDiscount(){return this->lineGoodsValueDiscount->text().toDouble();}
QDate SaleView::getSaleOrStoreDate(){return this->saleDate->date();}

bool SaleView::isPaid()
{
    return this->checkPaid->isChecked();
}

bool SaleView::isStoreUpdating()
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        return this->checkStoreUpdating->isChecked();
    else
        return false;
}

void SaleView::setLineGoodsValueNet(double valueNet)
{
      QString str = QVariant(valueNet).toString();
    this->lineGoodsValueNet->setText(str.setNum(valueNet,',',2).replace(QRegExp("[.]"),","));
}

void SaleView::setLineGoodsValueDiscount(double goodsValueWithDiscount)
{
    QString str = QVariant(goodsValueWithDiscount).toString();
    this->lineGoodsValueDiscount->setText(str.setNum(goodsValueWithDiscount,',',2).replace(QRegExp("[.]"),","));
}
void SaleView::setLineDiscount(double discount){

   QString str = QVariant(discount).toString();
  this->lineDiscount->setText(str.setNum(discount,',',2).replace(QRegExp("[.]"),","));
}
void SaleView::setSaleOrStoreDate(QDate saleDate){this->saleDate->setDate(saleDate);}
void SaleView::setPaymentDate(QDate paymentDate){this->paymentDate->setDate(paymentDate);}
void SaleView::setCheckPaid(bool paid){this->checkPaid->setChecked(paid);}

void SaleView::setCheckStoreUpdate(bool update)
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        this->checkStoreUpdating->setChecked(update);
}
