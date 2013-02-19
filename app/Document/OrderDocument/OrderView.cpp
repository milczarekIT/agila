#include "OrderView.h"

OrderView::OrderView(QWidget *parent, OrderController* controller) : SaleView(parent)   {

    this->controller = controller;
    this->mainLayout = new QGridLayout();
    mainLayout->setColumnMinimumWidth(4, 150);
    mainLayout->setColumnMinimumWidth(9, 100);
    this->setLayout(mainLayout);
    this->setMinimumSize(1024,768);
 if(controller->getEdition()==true)
    this->setWindowTitle( controller->getSymbol().append(" - Edycja dokumentu"));
   else
    this->setWindowTitle( controller->getSymbol().append(" - Nowy dokument"));
    initAlwaysUsedLineEdits();
    initOptionalLineEdits();
    initButtons();
    initOptionalButtons();
    initGoodsTable();
    initAlwaysUsedConnections();
    initOptionalConnections();
    addAlwaysUsedComponents(); //zawsze wywoływana po wszystkich inicjalizacjach!
    addOptionalComponents();
    setTabOrders();
}
void OrderView::setTabOrders()
{
    this->buttonChangeContractor->setFocus();
    setTabOrder(buttonChangeContractor,buttonGoodAdd);
    setTabOrder(this->buttonGoodAdd,this->buttonGoodDel);
    setTabOrder(this->buttonGoodDel,this->buttonBox);
    setTabOrder(buttonBox,this->lineDocumentPlace);
    setTabOrder(lineDocumentPlace,dateIssue);
    setTabOrder(this->dateIssue,lineDiscount);
    setTabOrder(lineDiscount,dateRealization);
    setTabOrder(dateRealization,checkRealization);
    setTabOrder(checkRealization,lineIssueName);
    setTabOrder(lineIssueName,lineReceiveName);
    setTabOrder(lineReceiveName,buttonChangeContractor);
    lineDocumentSymbol->setFocusPolicy(Qt::NoFocus);
    lineGoodsValueDiscount->setFocusPolicy(Qt::NoFocus);
    lineGoodsValueNet->setFocusPolicy(Qt::NoFocus);
    lineGoodsValue->setFocusPolicy(Qt::NoFocus);
}
void OrderView::initOptionalButtons(){

     buttonChangeContractor = new Button(ButtonStruct("Zmień",QSize(100,28)));

}

OrderView::~OrderView()
{
    delete mainLayout;
    delete controller;
}


void OrderView::initOptionalConnections()  {

    connect(buttonChangeContractor,SIGNAL(clicked()),controller,SLOT(selectContractor()));
    connect(this->dateRealization,SIGNAL(dateChanged(QDate)),controller,SLOT(changedRealizedOrSymbol()));
    connect(lineDiscount,SIGNAL(textEdited(QString)),controller,SLOT(discountChanged()));
}

void OrderView::addOptionalComponents() {

    checkRealization->setChecked(true);
    contractorData->setReadOnly(true);
    mainLayout->addWidget(new QLabel("Data realizacji"),2,0);
    mainLayout->addWidget(dateRealization,2,1);
    mainLayout->addWidget(new QLabel("Zrealizowano:"),2,4);
    mainLayout->addWidget(checkRealization,2,5);
    mainLayout->addWidget(contractorData,0,7,3,2);
    mainLayout->addWidget(new QLabel("Razem netto:"), 8, 0);
    mainLayout->addWidget(lineGoodsValueNet, 8, 1);
    mainLayout->addWidget(new QLabel("Dokument odebrał:"), 9, 7);
    mainLayout->addWidget(lineReceiveName, 9, 8);
    mainLayout->addWidget(new QLabel("Rabat[%]"),1,4);
    mainLayout->addWidget(lineDiscount,1,5);
    mainLayout->addWidget(new QLabel("Brutto po rabacie:"),8,7);
    mainLayout->addWidget(lineGoodsValueDiscount,8,8);
    mainLayout->addWidget(buttonChangeContractor, 1, 9);
    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]+([.]|,)[0-9]{2}"),this);
    lineGoodsValueNet->setValidator(validator);
    lineDiscount->setValidator(validator);
    lineGoodsValueDiscount->setReadOnly(true);
    lineGoodsValueNet->setReadOnly(true);
}


void OrderView::initOptionalLineEdits()    {

    contractorData= new QTextEdit("Wprowadź dane kontrahenta");
    lineGoodsValueNet= new QLineEdit();
    lineReceiveName = new QLineEdit();
    dateRealization = new DateEdit();
    checkRealization= new QCheckBox();
    lineDiscount = new QLineEdit();
    lineReceiveName = new QLineEdit();
    lineGoodsValueDiscount = new QLineEdit();
}

bool OrderView::isRealized()
{
     return this->checkRealization->isChecked();
}

QDate OrderView::getRealizationDate(){return this->dateRealization->date();}
void OrderView::setRealized(bool realized){this->checkRealization->setChecked(realized);}
void OrderView::setRealizationDate(QDate realizationDate){this->dateRealization->setDate(realizationDate);}
