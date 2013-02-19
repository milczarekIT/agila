#include "DocumentView.h"

DocumentView::DocumentView(QWidget* parent) : QDialog(parent)
{

}

DocumentView::~DocumentView()
{
    delete mainLayout;
}

void DocumentView::initAlwaysUsedConnections()  {

    connect(buttonBox,SIGNAL(rejected()),controller,SLOT(getDocumentData()));
    connect(buttonBox, SIGNAL(accepted()), controller,SLOT(checkRequiredFields()));
    connect(buttonBox, SIGNAL(rejected()), controller, SLOT(checkChanges()));
    connect(goodsTable,SIGNAL(cellChanged(int,int)),controller,SLOT(editGood(int,int)));
    connect(buttonGoodAdd, SIGNAL(clicked()), controller, SLOT(selectGoods()));
    connect(buttonGoodDel,SIGNAL(clicked()),controller,SLOT(removeGood()));
}

void DocumentView::closeEvent(QCloseEvent *event)
 {
     if (event->type() == QEvent::Close) {
         controller->getDocumentData();
         controller->checkChanges();
         event->accept();
     }
 }

void DocumentView::addAlwaysUsedComponents() {

    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]+([.]|,)[0-9]{2}"),this);
    dateIssue->setDate(QDate::currentDate()); //data wystawienia
    mainLayout->addWidget( new QLabel("Symbol dokumentu:"), 0, 0);
    mainLayout->addWidget(lineDocumentSymbol, 0, 1);
    mainLayout->addWidget(new QLabel("Miejsce wystawienia:"), 0, 4);
    mainLayout->addWidget(lineDocumentPlace, 0, 5);
    mainLayout->addWidget(new QLabel("Data wystawienia:"),1,0);
    mainLayout->addWidget(dateIssue,1,1);
    mainLayout->addWidget(goodsTable, 5, 0, 3, 9);
    mainLayout->addWidget(labelGoodsValue , 8, 4);
    mainLayout->addWidget(lineGoodsValue, 8, 5);
    mainLayout->addWidget(new QLabel("Dokument wystawił:"), 9, 0);
    mainLayout->addWidget(lineIssueName, 9, 1);
    mainLayout->addWidget(buttonGoodAdd, 5, 9);
    mainLayout->addWidget(buttonGoodDel, 6, 9);
    mainLayout->addWidget(buttonBox, 10, 0, 1, 10);
    lineGoodsValue->setValidator(validator);
    lineGoodsValue->setReadOnly(true);

}

void DocumentView::initAlwaysUsedLineEdits()    {

    lineDocumentSymbol = new QLineEdit();
    lineDocumentSymbol->setMaxLength(20);
    lineDocumentPlace = new QLineEdit();
    lineDocumentPlace->setMaxLength(40);
    lineGoodsValue = new QLineEdit();
    lineIssueName = new QLineEdit();
    lineIssueName->setMaxLength(70);
    dateIssue = new DateEdit();
}

void DocumentView::initButtons()   {

    buttonBox = new ButtonBox(this);
    buttonGoodAdd = new Button(ButtonStruct("Zmień","Zmień","chooseGood",QSize(100,28)),QSize(25,25));
    buttonGoodDel = new Button(ButtonStruct("Usuń  ","Usuń  ","del",QSize(100,28)),QSize(20,20));
    labelGoodsValue = new QLabel("Razem brutto:");
}

void DocumentView::setHeaders(int id, QTableWidgetItem* header)
{
    goodsTable->setHorizontalHeaderItem(id,header);
}

void DocumentView::setLineDocumentSymbol(QString documentSymbol){this->lineDocumentSymbol->setText(documentSymbol);}
void DocumentView::setLineDocumentPlace(QString documentPlace){this->lineDocumentPlace->setText(documentPlace);}
void DocumentView::setLineGoodsValue(double goodsValue)
{
    QString str = QVariant(goodsValue).toString();
    this->lineGoodsValue->setText(str.setNum(goodsValue,',',2).replace(QRegExp("[.]"),","));
}
void DocumentView::setLineIssueName(QString issueName){this->lineIssueName->setText(issueName);}
void DocumentView::setLineReceiveName (QString receiveName){this->lineReceiveName->setText(receiveName);}
void DocumentView::setDateIssue(QDate issueDate){this->dateIssue->setDate(issueDate);}
void DocumentView::setRealized(bool realized){}
void DocumentView::setRealizationDate(QDate realizationDate){}
void DocumentView::setCheckPaid(bool paid){}
void DocumentView::setPaymentDate(QDate paymentDate){}
void DocumentView::setLineGoodsValueDiscount(double goodsValueWithDiscount){}
void DocumentView::setAdvance(double advance){}
void DocumentView::setLineDiscount(double discount){}
void DocumentView::setSaleOrStoreDate(QDate date){}

bool DocumentView::isPaid(){return 0;}
QLineEdit *DocumentView::getPurchaseOrFactureSymbol(){return 0;}
QLineEdit *DocumentView::getDiscountOrWaybillNo(){return 0;}
QLineEdit *DocumentView::getLineOrderSymbol(){return 0;}
QComboBox *DocumentView::getComboBox(){return 0;}
QComboBox *DocumentView::getWayToPay(){return 0;}
DateEdit *DocumentView::getPaymentDate(){return 0;}
QDate DocumentView::getSaleOrStoreDate(){}
QLineEdit *DocumentView::getLineDocumentSymbol(){return this->lineDocumentSymbol;}
QLineEdit *DocumentView::getLineDocumentPlace(){return this->lineDocumentPlace;}
double DocumentView::getLineGoodsValue(){return this->lineGoodsValue->text().toDouble();}
double DocumentView::getLineGoodsValueDiscount(){return 0;}
double DocumentView::getLineAdvance(){return 0; }
QString DocumentView::getLineIssueName(){return this->lineIssueName->text();}
QString DocumentView::getLineReceiveName(){return this->lineReceiveName->text();}
QDate DocumentView::getDateIssue(){return this->dateIssue->date();}
QTableWidget *DocumentView::getGoodsTable(){return this->goodsTable;}
QTableWidget *DocumentView::getZALTable(){return 0;}
QTextEdit *DocumentView::getContractorData(){return this->contractorData;}
DocumentController * DocumentView::getController(){return this->controller;}
void DocumentView::setTabOrders(){}
bool DocumentView::isRealized()
{
     return 0;
}

QDate DocumentView::getRealizationDate(){}

void DocumentView::setContractorData(Contractor contractor)
{
    this->contractorData->setText(contractor.getContractorData());
    if(!contractor.getAdditionalId().getValue().isEmpty() && controller->getSymbol()=="RR")
        contractorData->append(contractor.getAdditionalId().getType().getName()+":"+ contractor.getAdditionalId().getValue());
}
