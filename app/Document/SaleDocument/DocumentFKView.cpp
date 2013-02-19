#include "DocumentFKView.h"

DocumentFKView::DocumentFKView(QWidget *parent, DocumentFKController* controller) : QDialog(parent)   {
    this->controller = controller;
    this->mainLayout = new QGridLayout();

    this->setLayout(mainLayout);

    this->setMinimumSize(1024,768);
    if(controller->getEdition()==true)
        this->setWindowTitle("FK - Edycja dokumentu");
    else
       this->setWindowTitle("FK - Nowy dokument");
    initLineEdits();
    initButtons();
    initGoodsTable();
    initConnections();
    initTabs();
    addAllComponents(); //zawsze wywoływana po wszystkich inicjalizacjach!

}

DocumentFKView::DocumentFKView(QWidget *parent) : QDialog(parent) {}

DocumentFKView::~DocumentFKView()
{
    delete mainLayout;
}

void DocumentFKView::initTabs()
{
    mainLayoutAfterCorrection = new QGridLayout();
    mainLayoutBeforeCorrection = new QGridLayout();
    tabWidget = new QTabWidget();
    tabWidget->addTab( tabBeforeCorrection= new QTabWidget(),"Przed korektą");
    tabWidget->addTab(tabAfterCorrection = new QTabWidget(),"Po korekcie");
    tabBeforeCorrection->setLayout(mainLayoutBeforeCorrection);
    tabAfterCorrection->setLayout(mainLayoutAfterCorrection);
    mainLayout->addWidget(tabWidget,0,0);

}

void DocumentFKView::initConnections()  {

    connect(boxWayToPay,SIGNAL(currentIndexChanged(int)),controller,SLOT(updatePaymentDate()));
    connect(paymentDate,SIGNAL(dateChanged(QDate)),this,SLOT(changedDate()));
    connect(buttonBox, SIGNAL(accepted()), controller,SLOT(checkRequredFields()));
    connect(buttonBox,SIGNAL(rejected()),controller,SLOT(checkChanges()));
    connect(buttonChangeContractor,SIGNAL(clicked()),controller,SLOT(selectContractor()));
    connect(lineDiscountNew,SIGNAL(textEdited(QString)),controller,SLOT(discountChanged()));
    connect(goodsTableNew,SIGNAL(cellChanged(int,int)),controller,SLOT(editGood(int,int)));
    connect(buttonChangeGood, SIGNAL(clicked()), controller, SLOT(selectGoods()));
    connect(buttonRemoveGood,SIGNAL(clicked()),controller,SLOT(removeGood()));
    connect(buttonSelectInvoice,SIGNAL(clicked()),controller,SLOT(selectInvoice()));

}

void DocumentFKView::closeEvent(QCloseEvent *event)
 {
     if (event->type() == QEvent::Close) {
         controller->checkChanges();
         event->accept();}
 }

void DocumentFKView::addAllComponents() {

    checkPaid->setChecked(true);

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        checkStoreUpdating->setChecked(true);

    contractorDataNew->setReadOnly(true);
    contractorDataOld->setDisabled(true);

    paymentDate->setDate(QDate::currentDate());
    dateIssue->setDate(QDate::currentDate());
    saleDate->setDate(QDate::currentDate());


    mainLayoutBeforeCorrection->addWidget(new QLabel("Dotyczy faktury nr:"),0,0);
    mainLayoutBeforeCorrection->addWidget(lineRelatedTo,0,1);
    mainLayoutBeforeCorrection->addWidget(new QLabel("Wystawionej dn.:"),0,4);
    mainLayoutBeforeCorrection->addWidget(dateEditInvoiceDate,0,5,1,2);
    mainLayoutBeforeCorrection->addWidget(buttonSelectInvoice,0,9);
    mainLayoutBeforeCorrection->addWidget(new QLabel("Data sprzedaży:"),1,0);
    mainLayoutBeforeCorrection->addWidget(saleDate,1,1);
    mainLayoutBeforeCorrection->addWidget(new QLabel("Sposób płatności:"),1,4);
    mainLayoutBeforeCorrection->addWidget(boxWayToPay,1,5);
    mainLayoutBeforeCorrection->addWidget(new QLabel("Data płatnosci:"), 2,0);
    mainLayoutBeforeCorrection->addWidget(paymentDate, 2, 1);
    mainLayoutBeforeCorrection->addWidget(new QLabel("Rabat[%]:"),2,4);
    mainLayoutBeforeCorrection->addWidget(lineDiscount,2,5);
    mainLayoutBeforeCorrection->addWidget(new QLabel("Zapłacono:"),3,0);
    mainLayoutBeforeCorrection->addWidget(checkPaid,3,1);
    mainLayoutBeforeCorrection->addWidget(contractorDataOld,0,7,4,2);

    mainLayoutBeforeCorrection->addWidget(goodsTableOld, 5, 0, 5, 9);

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses)&& controller->getSymbol().contains("FK"))
    {
        mainLayoutBeforeCorrection->addWidget(new QLabel("Skutek magazynowy:"),3,4,Qt::AlignBottom);
        mainLayoutBeforeCorrection->addWidget(checkStoreUpdating,3,5,Qt::AlignBottom);
    }
    else if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        mainLayoutBeforeCorrection->addWidget(new QLabel("Skutek magazynowy:"),4,0);
        mainLayoutBeforeCorrection->addWidget(checkStoreUpdating,4,1);
    }

    mainLayoutBeforeCorrection->addWidget(new QLabel("Razem netto:"),12,0);
    mainLayoutBeforeCorrection->addWidget(lineGoodsValueNet,12,1);
    mainLayoutBeforeCorrection->addWidget(new QLabel("Razem brutto:"),12,4);
    mainLayoutBeforeCorrection->addWidget(lineGoodsValue,12,5);
    mainLayoutBeforeCorrection->addWidget(new QLabel("Brutto po rabacie:"),12,7);
    mainLayoutBeforeCorrection->addWidget(lineGoodsValueDiscount,12,8);

    //Po korekcie
    mainLayoutAfterCorrection->addWidget(new QLabel("Symbol dokumentu:"), 0, 0);
    mainLayoutAfterCorrection->addWidget(lineDocumentSymbol, 0, 1);
    mainLayoutAfterCorrection->addWidget(buttonChangeContractor, 0,7);
    mainLayoutAfterCorrection->addWidget(new QLabel("Data wystawienia:"),1,0);
    mainLayoutAfterCorrection->addWidget(dateIssue,1,1);
    mainLayoutAfterCorrection->addWidget(new QLabel("Rabat[%]"),2,0);
    mainLayoutAfterCorrection->addWidget(lineDiscountNew,2,1);
    mainLayoutAfterCorrection->addWidget(new QLabel("Miejsce wystawienia:"), 3, 0);
    mainLayoutAfterCorrection->addWidget(lineDocumentPlace, 3, 1);

    mainLayoutAfterCorrection->addWidget(buttonChangeGood, 5,10);
    mainLayoutAfterCorrection->addWidget(buttonRemoveGood,6,10);

    mainLayoutAfterCorrection->addWidget(new QLabel("Dokument wystawił:"),17,4);
    mainLayoutAfterCorrection->addWidget(lineIssueName,17,5);
    mainLayoutAfterCorrection->addWidget(new QLabel("Dokument odebrał:"),17,7);
    mainLayoutAfterCorrection->addWidget(lineReceiveName,17,8);
    mainLayoutAfterCorrection->addWidget(buttonBox, 18, 0, 1, 12);

    mainLayoutAfterCorrection->addWidget(lineGoodsValueNetNew,16,1);
    mainLayoutAfterCorrection->addWidget(new QLabel("Razem netto:"),16,0);
    mainLayoutAfterCorrection->addWidget(new QLabel("Razem brutto:"),16,4);
    mainLayoutAfterCorrection->addWidget(lineGoodsValueNew,16,5);
    mainLayoutAfterCorrection->addWidget(new QLabel("Do zapłaty po korekcie"),16,7);
    mainLayoutAfterCorrection->addWidget(lineToPayAfterCorrection,16,8);
    mainLayoutAfterCorrection->addWidget(new QLabel("Brutto po rabacie:"),17,0);
    mainLayoutAfterCorrection->addWidget(lineGoodsValueDiscountNew,17,1);

    mainLayoutAfterCorrection->addWidget(contractorDataNew,0,4,4,2);
    mainLayoutAfterCorrection->addWidget(goodsTableNew,5,0,5,9);

    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]+([.]|,)[0-9]{2}"),this);
    lineDiscount->setValidator(validator);
    lineGoodsValueDiscount->setValidator(validator);
    lineGoodsValue->setValidator(validator);
    lineGoodsValueNet->setValidator(validator);
    lineGoodsValueDiscountNew->setValidator(validator);
    lineGoodsValueNew->setValidator(validator);
    lineGoodsValueNetNew->setValidator(validator);
    lineGoodsValueNetNew->setReadOnly(true);
    lineGoodsValueNetNew->setFocusPolicy(Qt::NoFocus);
    lineGoodsValueNew->setReadOnly(true);
    lineGoodsValueNew->setFocusPolicy(Qt::NoFocus);
    lineGoodsValueDiscountNew->setReadOnly(true);
    lineGoodsValueDiscountNew->setFocusPolicy(Qt::NoFocus);
    lineToPayAfterCorrection->setReadOnly(true);
    lineToPayAfterCorrection->setFocusPolicy(Qt::NoFocus);
    lineGoodsValue->setDisabled(true);
    lineGoodsValueDiscount->setDisabled(true);
    lineGoodsValueNet->setDisabled(true);
    lineDiscount->setDisabled(true);
    contractorDataNew->setFocusPolicy(Qt::NoFocus);
    lineToPayAfterCorrection->setValidator(validator);

}


void DocumentFKView::initLineEdits()    {

    contractorDataOld = new QTextEdit("Wybierz fakturę aby wprowadzić dane kontrahenta");
    contractorDataNew = new QTextEdit();
    lineDiscount = new QLineEdit();
    lineDiscountNew = new QLineEdit();
    lineToPayAfterCorrection = new QLineEdit();
    lineDocumentSymbol = new QLineEdit();
    lineDocumentSymbol->setMaxLength(20);
    lineDocumentPlace = new QLineEdit();
    lineDocumentPlace->setMaxLength(40);
    lineRelatedTo = new QLineEdit();
    lineGoodsValueNet= new QLineEdit();
    lineGoodsValueNetNew= new QLineEdit();
    lineGoodsValue = new QLineEdit();
    lineGoodsValueDiscount = new QLineEdit();
    lineGoodsValueNew = new QLineEdit();
    lineGoodsValueDiscountNew = new QLineEdit();
    lineIssueName = new QLineEdit();
    lineIssueName->setMaxLength(70);
    lineReceiveName = new QLineEdit();
    lineReceiveName->setMaxLength(70);
    dateEditInvoiceDate = new DateEdit();
    saleDate = new DateEdit();
    dateIssue = new DateEdit();
    paymentDate = new DateEdit();//data wystawienia dokumentu
    boxWayToPay = new QComboBox();
    checkPaid = new QCheckBox();
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        checkStoreUpdating = new QCheckBox();
}

void DocumentFKView::initButtons()   {

    buttonBox = new ButtonBox(this);
    buttonChangeContractor = new Button(ButtonStruct("Zmień","Zmień","chooseContractor",QSize(100,28)),QSize(25,25));
    buttonChangeGood = new Button(ButtonStruct("Zmień","Zmień","chooseGood",QSize(100,28)),QSize(25,25));
    buttonSelectInvoice = new Button(ButtonStruct("Wybierz","Zmień","chooseDoc",QSize(112,28)),QSize(25,25));
    buttonRemoveGood = new Button(ButtonStruct("Usuń  ","Usuń  ","del",QSize(100,28)),QSize(20,20));

}

void DocumentFKView::initGoodsTable()  {

  goodsTableOld = new QTableWidget();
  goodsTableNew = new QTableWidget();
  goodsTableOld->setColumnCount(6);
  goodsTableOld->setColumnWidth(0,300);
  goodsTableOld->setColumnWidth(1,230);
  goodsTableOld->setColumnWidth(2,120);
  goodsTableOld->setColumnWidth(3,120);
  goodsTableOld->setColumnWidth(4,110);
  goodsTableNew->setColumnWidth(5,110);
  goodsTableOld->setSelectionBehavior(QAbstractItemView::SelectRows);
  goodsTableOld->setDisabled(true);
  goodsTableNew->setColumnCount(6);
  goodsTableNew->setColumnWidth(0,300);
  goodsTableNew->setColumnWidth(1,230);
  goodsTableNew->setColumnWidth(2,120);
  goodsTableNew->setColumnWidth(3,120);
  goodsTableNew->setColumnWidth(4,110);
  goodsTableNew->setColumnWidth(5,110);
  goodsTableNew->setSelectionBehavior(QAbstractItemView::SelectRows);

  setHeaders(0,new QTableWidgetItem("Nazwa"));
  setHeaders(1,new QTableWidgetItem("Symbol"));
  setHeaders(2,new QTableWidgetItem("Cena Netto"));
  setHeaders(3,new QTableWidgetItem("Cena Brutto"));
  setHeaders(4,new QTableWidgetItem("Ilość"));
  setHeaders(5,new QTableWidgetItem("Wartość brutto"));
}

void DocumentFKView::setHeaders(int id, QTableWidgetItem* header)
{
    goodsTableOld->setHorizontalHeaderItem(id,header);
    goodsTableNew->setHorizontalHeaderItem(id,header);
}

void DocumentFKView::setContractorDataOld(Contractor receiver)
{
        this->contractorDataOld->setText(receiver.getContractorData());
}

void DocumentFKView::setContractorDataNew(Contractor receiver)
{
    this->contractorDataNew->setText(receiver.getContractorData());  
}

void DocumentFKView::changedDate()
{
 if(getPaymentDate()<=QDate::currentDate())
    setCheckPaid(true);
 else
    setCheckPaid(false);
}

bool DocumentFKView::isPaid() {
    return this->checkPaid->isChecked();
}

bool DocumentFKView::isStoreUpdating() {
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        return this->checkStoreUpdating->isChecked();
    else
        return false;
}

void DocumentFKView::setLineDiscount(double discount){this->lineDiscount->setText(QVariant(discount).toString());}
void DocumentFKView::setLineDocumentSymbol(QString documentSymbol){this->lineDocumentSymbol->setText(documentSymbol);}
void DocumentFKView::setLineDocumentPlace(QString documentPlace){this->lineDocumentPlace->setText(documentPlace);}

void DocumentFKView::setLineGoodsValueNet(double valueNet)
{
    QString str = QVariant(valueNet).toString();
    this->lineGoodsValueNet->setText(str.setNum(valueNet,',',2).replace(QRegExp("[.]"),","));
}

void DocumentFKView::setLineGoodsValue(double goodsValue)
{
    QString str = QVariant(goodsValue).toString();
    this->lineGoodsValue->setText(str.setNum(goodsValue,',',2).replace(QRegExp("[.]"),","));
}

void DocumentFKView::setLineGoodsValueDiscount(double goodsValueWithDiscount)
{
    QString str = QVariant(goodsValueWithDiscount).toString();
    this->lineGoodsValueDiscount->setText(str.setNum(goodsValueWithDiscount,',',2).replace(QRegExp("[.]"),","));
}

void DocumentFKView::setLineIssueName(QString issueName){this->lineIssueName->setText(issueName);}
void DocumentFKView::setLineReceiveName (QString receiveName){this->lineReceiveName->setText(receiveName);}
void DocumentFKView::setSaleDate(QDate saleDate){this->saleDate->setDate(saleDate);}
void DocumentFKView::setDateIssue(QDate issueDate){this->dateIssue->setDate(issueDate);}
void DocumentFKView::setPaymentDate(QDate paymentDate){this->paymentDate->setDate(paymentDate);}//data wystawienia dokumentu
void DocumentFKView::setCheckPaid(bool paid){this->checkPaid->setChecked(paid);}
void DocumentFKView::setCheckStoreUpdate(bool update)
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        this->checkStoreUpdating->setChecked(update);
}
void DocumentFKView::setLineDiscountNew(double discountNew){this->lineDiscountNew->setText(QVariant(discountNew).toString());}
void DocumentFKView::setPurchaseDocSymbol(QString symbol){this->linePurchaseDocSymbol->setText(symbol);}
void DocumentFKView::setLineToPayAfterCorrection(double toPay)
{
    QString str = QVariant(toPay).toString();
    this->lineToPayAfterCorrection->setText(str.setNum(toPay,',',2).replace(QRegExp("[.]"),","));
}
void DocumentFKView::setRealatedTo(QString realtedTo){this->lineRelatedTo->setText(realtedTo);}
void DocumentFKView::setDateEditInvoiceDate(QDate dateEditInvoiceDate){this->dateEditInvoiceDate->setDate(dateEditInvoiceDate);}
void DocumentFKView::setLineGoodsValueNetNew(double valueNetNew)
{
       QString str = QVariant(valueNetNew).toString();
       this->lineGoodsValueNetNew->setText(str.setNum(valueNetNew,',',2).replace(QRegExp("[.]"),","));
}
void DocumentFKView::setLineGoodsValueNew(double goodsValueNew)
{
    QString str = QVariant(goodsValueNew).toString();
    this->lineGoodsValueNew->setText(str.setNum(goodsValueNew,',',2).replace(QRegExp("[.]"),","));
}

void DocumentFKView::setLineGoodsValueDiscountNew(double goodsValueWithDiscountNew)
{
    QString str = QVariant(goodsValueWithDiscountNew).toString();
    this->lineGoodsValueDiscountNew->setText(str.setNum(goodsValueWithDiscountNew,',',2).replace(QRegExp("[.]"),","));
}

QLineEdit *DocumentFKView::getLineDiscountNew(){return this->lineDiscountNew;}
QLineEdit *DocumentFKView::getLineDiscount(){return this->lineDiscount;}
QLineEdit *DocumentFKView::getLineDocumentSymbol(){return this->lineDocumentSymbol;}
QLineEdit *DocumentFKView::getLineRelatedTo(){return this->lineRelatedTo;}
QLineEdit *DocumentFKView::getLineDocumentPlace(){return this->lineDocumentPlace;}
double DocumentFKView::getLineGoodsValue(){return this->lineGoodsValue->text().toDouble();}
double DocumentFKView::getLineGoodsValueNew(){return this->lineGoodsValueNew->text().toDouble();}
double DocumentFKView::getLineToPayAfterCorrection(){return this->lineToPayAfterCorrection->text().toDouble();}
double DocumentFKView::getLineGoodsValueNetNew(){return this->lineGoodsValueNetNew->text().toDouble();}
QString DocumentFKView::getLineIssueName(){return this->lineIssueName->text();}
QString DocumentFKView::getLineReceiveName(){return this->lineReceiveName->text();}
QDate DocumentFKView::getSaleDate(){return this->saleDate->date();}
QDate DocumentFKView::getDateIssue(){return this->dateIssue->date();}
QDate DocumentFKView::getPaymentDate(){return this->paymentDate->date();}
QComboBox *DocumentFKView::getBoxWayToPay(){return this->boxWayToPay;}
QTableWidget *DocumentFKView::getGoodsTableOld(){return this->goodsTableOld;}
QTableWidget *DocumentFKView::getGoodsTableNew(){return this->goodsTableNew;}
QTextEdit *DocumentFKView::getContractorDataOld(){return this->contractorDataOld;}
QTextEdit *DocumentFKView::getContractorDataNew(){return this->contractorDataNew;}
DocumentFKController *DocumentFKView::getController(){return this->controller;}
QLineEdit *DocumentFKView::getPurchaseDocSymbol(){return this->linePurchaseDocSymbol;}

void DocumentFKView::addAdditionalComopnent(){}
