#include "CashDocumentView.h"

CashDocumentView::CashDocumentView(CashDocumentController *controller, QWidget *parent)
{
    this->controller = controller;

    QSize parentSize = parent->size();
    this->setMaximumSize(parentSize);
    this->setMinimumSize(720,460);

    if(controller->getSymbol() == "KP")
        this->setWindowTitle(trUtf8("Nowy dokument: Kasa przyjmie"));
    else if(controller->getSymbol() == "KW")
        this->setWindowTitle(trUtf8("Nowy dokument: Kasa wyda"));

    initInterface();
    initConnections();
}

void CashDocumentView::initLayout()
{
    this->setLayout(mainLayout = new QGridLayout);
    mainLayout->setColumnMinimumWidth(4,50);
    mainLayout->setColumnMinimumWidth(6,180);
    mainLayout->setRowMinimumHeight(6,30);
    mainLayout->setRowMinimumHeight(13,30);
    mainLayout->setRowMinimumHeight(15,30);
}

void CashDocumentView::initInterface()
{
    initLayout();

    buttonChangeContractor = new Button(ButtonStruct("Zmień","Zmiana kontrahenta", QSize(146,28)));
    buttonSelectInvoice =  new Button(ButtonStruct("Wybierz fakture","Wybor dokumentu", QSize(150,28)));
    buttonPrint =  new Button(ButtonStruct("Drukuj","Wydrukuj dokument", QSize(90,25)));
    buttonBox = new ButtonBox(this);

    mainLayout->addWidget(new QLabel("Dane kontrahenta:"),1,1,1,1);
    mainLayout->addWidget(new QLabel("Miejsce wystawienia:"),3,5,1,2);
    mainLayout->addWidget(new QLabel("Symbol:"),4,5,1,1);
    mainLayout->addWidget(new QLabel("Data wystawienia"),5,5,1,1);
    mainLayout->addWidget(new QLabel("Wystawiono dla dokumentu:"),7,1,1,2);
    mainLayout->addWidget(new QLabel("Opis:"),8,6,1,1,Qt::AlignRight);
    mainLayout->addWidget(new QLabel("Data płatności:"),9,1,1,1);

    if(controller->getSymbol().contains("KP"))
        mainLayout->addWidget(new QLabel("Wysokość wpłaty:"),10,1,1,1);
    else
        mainLayout->addWidget(new QLabel("Wysokość wypłaty:"),10,1,1,1);

    mainLayout->addWidget(new QLabel("Tytułem:"),11,1,1,1);
    mainLayout->addWidget(new QLabel("Dokument odebrał:"),14,1,1,1);
    mainLayout->addWidget(new QLabel("Dokument wystawił:"),14,5,1,1);

    mainLayout->addWidget(buttonChangeContractor,2,5,1,2,Qt::AlignLeft);
    mainLayout->addWidget(buttonBox,16,5,1,2,Qt::AlignRight);
    mainLayout->addWidget(buttonPrint,16,1,1,1,Qt::AlignLeft);
    mainLayout->addWidget(buttonSelectInvoice,7,5,1,2,Qt::AlignLeft);

    mainLayout->addWidget(dateOfIssue = new DateEdit,5,6,1,1);
    mainLayout->addWidget(dateOfPayment = new DateEdit,9,2,1,2);

    mainLayout->addWidget(contractorData = new QTextEdit,2,1,4,3);
    mainLayout->addWidget(textDescription = new QTextEdit,9,5,3,2);

    mainLayout->addWidget(lineDocumentPlace = new QLineEdit,3,6,1,1);
    mainLayout->addWidget(lineSymbol = new QLineEdit,4,6,1,1);
    mainLayout->addWidget(lineIssuedForDocument = new QLineEdit,7,3,1,1);
    mainLayout->addWidget(lineAmountOfPayment = new QLineEdit,10,2,1,2);
    mainLayout->addWidget(lineTitle = new QLineEdit,11,2,1,2);
    mainLayout->addWidget(lineReceiveName = new QLineEdit,14,2,1,2);
    mainLayout->addWidget(lineIssueName = new QLineEdit,14,6,1,1);

    contractorData->setReadOnly(true);
}

void CashDocumentView::initConnections()
{
    connect(buttonChangeContractor,SIGNAL(clicked()),controller,SLOT(selectContractor()));
    connect(buttonSelectInvoice,SIGNAL(clicked()),controller,SLOT(selectInvoice()));
    connect(buttonBox,SIGNAL(rejected()),controller,SLOT(checkChanges()));
    connect(buttonBox,SIGNAL(accepted()),controller,SLOT(checkRequiredFields()));
    connect(buttonPrint,SIGNAL(clicked()),controller,SLOT(print()));
}

Button *CashDocumentView::getButtonChangeContractor() { return buttonChangeContractor;}
QTextEdit *CashDocumentView::getContractorData() { return contractorData;}
QLineEdit *CashDocumentView::getLineSymbol() { return lineSymbol;}
DateEdit *CashDocumentView::getDateOfIssue() { return dateOfIssue;}
DateEdit *CashDocumentView::getDateOfPayment() { return dateOfPayment;}
QLineEdit *CashDocumentView::getLineAmountOfPayment() { return lineAmountOfPayment;}
QLineEdit *CashDocumentView::getLineTitle() { return lineTitle;}
QTextEdit *CashDocumentView::getTextDescription() { return textDescription;}
QLineEdit *CashDocumentView::getLineIssuedForDocument() { return lineIssuedForDocument;}
QLineEdit *CashDocumentView::getLineReceiveName() { return lineReceiveName;}
QLineEdit *CashDocumentView::getLineIssueName() { return lineIssueName;}
QLineEdit *CashDocumentView::getLineDocumentPlace() { return lineDocumentPlace;}
ButtonBox *CashDocumentView::getButtonBox(){ return buttonBox;}

CashDocumentView::~CashDocumentView()
{
    delete mainLayout;
}
