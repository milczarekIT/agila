#include "DocumentPZView.h"

DocumentPZView::DocumentPZView(QWidget *parent, DocumentPZController* controller) : StoreDocumentView(parent)    {

    this->controller = controller;
    this->mainLayout = new QGridLayout();
    mainLayout->setColumnMinimumWidth(4, 150);
    mainLayout->setColumnMinimumWidth(9, 100);
    this->setLayout(mainLayout);
    this->setMaximumSize(1024,700);
    this->setMinimumSize(1024,700);
 if(controller->getEdition()==true)
    this->setWindowTitle( this->controller->getSymbol().append(" - Edycja dokumentu"));
   else
    this->setWindowTitle( this->controller->getSymbol().append(" - Nowy dokument"));
    initOptionalLineEdits();
    initOptionalButtons();
    initGoodsTable();
    initPZComponents();
    initAlwaysUsedLineEdits();
    initButtons();
    addPZComponents();
    addOptionalComponents();
    addAlwaysUsedComponents();
    initAlwaysUsedConnections();
    initOptionalConnections();
    setTabOrders();

}
void DocumentPZView::setTabOrders()
{
    this->buttonChangeContractor->setFocus();
    setTabOrder(buttonChangeContractor,buttonGoodAdd);
    setTabOrder(this->buttonGoodAdd,this->buttonGoodDel);
    setTabOrder(this->buttonGoodDel,this->buttonBox);
    setTabOrder(buttonBox,this->lineDocumentPlace);
    setTabOrder(lineDocumentPlace,dateIssue);
    setTabOrder(this->dateIssue,checkStoreUpdating);
    setTabOrder(checkStoreUpdating,storeDate);
    setTabOrder(storeDate,comboBoxTransport);
    setTabOrder(comboBoxTransport,lineIssueName);
    setTabOrder(lineIssueName,lineReceiveName);
    setTabOrder(lineReceiveName,buttonChangeContractor);
    lineDocumentSymbol->setFocusPolicy(Qt::NoFocus);
    lineGoodsValueNet->setFocusPolicy(Qt::NoFocus);
}
void DocumentPZView::initOptionalConnections()  {

    connect(buttonChangeContractor,SIGNAL(clicked()),controller,SLOT(selectContractor()));
}

void DocumentPZView::addPZComponents()
{
    contractorData->setReadOnly(true);
    mainLayout->addWidget(new QLabel("Data przyjęcia:"), 2, 0);
    mainLayout->addWidget(storeDate, 2, 1);
    mainLayout->addWidget(new QLabel("Rodzaj transportu:"),3,0);
    mainLayout->addWidget(comboBoxTransport,3,1);
    mainLayout->addWidget(contractorData,0,7,4,2);
    mainLayout->addWidget(buttonChangeContractor, 1, 9);
    mainLayout->addWidget(new QLabel("Dokument odebrał:"), 9, 7);
    mainLayout->addWidget(lineReceiveName, 9, 8);
}

void DocumentPZView::initOptionalButtons()
{
    buttonChangeContractor = new Button(ButtonStruct("Zmień",QSize(100,28)));
}

void DocumentPZView::initPZComponents()
{
    storeDate = new DateEdit();
    comboBoxTransport = new QComboBox();
    storeDate->setDate(QDate::currentDate());
    contractorData= new QTextEdit("Wprowadź dane kontrahenta");
}

DocumentPZView::~DocumentPZView()   {

    delete mainLayout;
}

void DocumentPZView::setSaleOrStoreDate(QDate storeDate){this->storeDate->setDate(storeDate);}
QDate DocumentPZView::getSaleOrStoreDate(){return this->storeDate->date();}
QComboBox *DocumentPZView::getComboBox(){return this->comboBoxTransport;}
