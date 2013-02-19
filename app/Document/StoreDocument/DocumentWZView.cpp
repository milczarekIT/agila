#include "DocumentWZView.h"

DocumentWZView::DocumentWZView(QWidget *parent, DocumentWZController* controller) : StoreDocumentView(parent)    {

    this->controller = controller;
    this->mainLayout = new QGridLayout();
    mainLayout->setColumnMinimumWidth(4, 150);
    mainLayout->setColumnMinimumWidth(9, 100);
    this->setLayout(mainLayout);
    this->setMaximumSize(1024,700);
    this->setMinimumSize(1024,700);
 if(controller->getEdition()==true)
    this->setWindowTitle( controller->getSymbol().append(" - Edycja dokumentu"));
   else
    this->setWindowTitle( controller->getSymbol().append(" - Nowy dokument"));
    initOptionalLineEdits();
    initOptionalButtons();
    initGoodsTable();
    initAlwaysUsedLineEdits();
    initButtons();
    initWZComponents();
    addAlwaysUsedComponents();
    addWZComponents();
    initAlwaysUsedConnections();
    initOptionalConnections();
    setTabOrders();
}

DocumentWZView::~DocumentWZView()
{
    delete mainLayout;
}

void DocumentWZView::setTabOrders()
{
    this->buttonChangeContractor->setFocus();
    setTabOrder(buttonChangeContractor,buttonGoodAdd);
    setTabOrder(this->buttonGoodAdd,this->buttonGoodDel);
    setTabOrder(this->buttonGoodDel,this->buttonBox);
    setTabOrder(buttonBox,this->lineDocumentPlace);
    setTabOrder(lineDocumentPlace,dateIssue);
    setTabOrder(this->dateIssue,lineNoCarraigeNote);
    setTabOrder(lineNoCarraigeNote,dateDelivery);
    setTabOrder(dateDelivery,checkStoreUpdating);
    setTabOrder(checkStoreUpdating,comboBoxTransport);
    setTabOrder(comboBoxTransport,comboPayForDelivery);
    setTabOrder(comboPayForDelivery,lineNoFactureVat);
    setTabOrder(lineNoFactureVat,lineIssueName);
    setTabOrder(lineIssueName,lineReceiveName);
    setTabOrder(lineReceiveName,buttonChangeContractor);
    lineDocumentSymbol->setFocusPolicy(Qt::NoFocus);
    lineGoodsValueNet->setFocusPolicy(Qt::NoFocus);
}

void DocumentWZView::addWZComponents()
{
        QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]+([.]|,)[0-9]{2}"),this);
        checkStoreUpdating->setChecked(true);
        contractorData->setReadOnly(true);
        dateDelivery->setDate(QDate::currentDate());
        mainLayout->addWidget(new QLabel("Data wydania:"), 2, 0);
        mainLayout->addWidget(dateDelivery, 2, 1);
        mainLayout->addWidget(new QLabel("Skutek magazynowy:"),2,4);
        mainLayout->addWidget(checkStoreUpdating,2,5);
        mainLayout->addWidget(new QLabel("Rodzaj transportu:"),3,0);
        mainLayout->addWidget(comboBoxTransport,3,1);
        mainLayout->addWidget(new QLabel("Wysyłka na koszt:"),4,0);
        mainLayout->addWidget(comboPayForDelivery,4,1);
        mainLayout->addWidget(new QLabel("Nr listu przewozowego:"),1,4);
        mainLayout->addWidget(lineNoCarraigeNote,1,5);
        mainLayout->addWidget(new QLabel("Dla faktury nr:"),4,4);
        mainLayout->addWidget(lineNoFactureVat,4,5);
        mainLayout->addWidget(buttonOrderOrFactureAdd,4,7);
        mainLayout->addWidget(contractorData,0,7,4,2);
        mainLayout->addWidget( new QLabel("Razem netto:"), 8, 0);
        mainLayout->addWidget(lineGoodsValueNet, 8, 1);
        lineGoodsValueNet->setValidator(validator);
        mainLayout->addWidget(new QLabel("Dokument odebrał:"), 9, 7);
        mainLayout->addWidget(lineReceiveName, 9, 8);
        mainLayout->addWidget(buttonChangeContractor, 1, 9);
        lineGoodsValueNet->setReadOnly(true);
        lineGoodsValue->setVisible(false);
        labelGoodsValue->setVisible(false);

}

void DocumentWZView::initOptionalButtons()
{
    buttonChangeContractor = new Button(ButtonStruct("Zmień",QSize(100,28)));
}

void DocumentWZView::initOptionalConnections()  {

    connect(buttonChangeContractor,SIGNAL(clicked()),controller,SLOT(selectContractor()));
}
void DocumentWZView::initWZComponents()
{
    comboPayForDelivery = new QComboBox();
    contractorData= new QTextEdit("Wprowadź dane kontrahenta");
    comboPayForDelivery->addItem("BRAK", QVariant(DocumentWZ::SHIPPING_NOT_APLICABLE));
    comboPayForDelivery->addItem("Magazyn", QVariant(DocumentWZ::SHIPPING_STORE));
    comboPayForDelivery->addItem("Odbiorca", QVariant(DocumentWZ::SHIPPING_RECEIPMENT));
    dateDelivery = new DateEdit();
    comboBoxTransport = new QComboBox();
    lineNoCarraigeNote = new QLineEdit();
    lineNoFactureVat = new QLineEdit();
    buttonOrderOrFactureAdd = new Button(ButtonStruct("Zmień",QSize(100,28)));
    buttonOrderOrFactureAdd->setMinimumWidth(60);
    connect(buttonOrderOrFactureAdd,SIGNAL(clicked()),controller,SLOT(selectOrderOrFacture()));
}
QLineEdit *DocumentWZView::getDiscountOrWaybillNo(){return this->lineNoCarraigeNote;}
QLineEdit *DocumentWZView::getPurchaseOrFactureSymbol(){return this->lineNoFactureVat;}
QDate DocumentWZView::getSaleOrStoreDate(){return this->dateDelivery->date();}
QComboBox *DocumentWZView::getWayToPay()
{
    return this->comboPayForDelivery;
}


void DocumentWZView::setSaleOrStoreDate(QDate storeDate){this->dateDelivery->setDate(storeDate);}
QComboBox *DocumentWZView::getComboBox(){return this->comboBoxTransport;}


