#include "DocumentRRView.h"

DocumentRRView::DocumentRRView(QWidget *parent, DocumentRRController* controller) : SaleView(parent)  {
    this->controller = controller;
    this->mainLayout = new QGridLayout();
    mainLayout->setColumnMinimumWidth(0,140);
    mainLayout->setColumnStretch(4,250);
    this->setLayout(mainLayout);
    this->setMinimumSize(1024,768);
 if(controller->getEdition()==true)
    this->setWindowTitle( controller->getSymbol().append(" - Edycja dokumentu"));
   else
    this->setWindowTitle( controller->getSymbol().append(" - Nowy dokument"));
    initOptionalLineEdits();
    initAlwaysUsedLineEdits();
    initButtons();
    initOptionalButtons();
    initGoodsTable();
    initOptionalConnections();
    initAlwaysUsedConnections();
    addOptionalComponents(); //zawsze wywoływana po wszystkich inicjalizacjach!
    addAlwaysUsedComponents();
}

DocumentRRView::~DocumentRRView()
{
    delete mainLayout;
    delete controller;
}

void DocumentRRView::addOptionalComponents() {

    checkPaid->setChecked(true);
    checkStoreUpdating->setChecked(true);
    contractorData->setReadOnly(true);
    paymentDate->setDate(QDate::currentDate());
    saleDate->setDate(QDate::currentDate());
    mainLayout->addWidget(new QLabel("Data płatności:"), 3, 0);
    mainLayout->addWidget(paymentDate, 3, 1);
    if(controller->getSymbol()!="FZ")
    mainLayout->addWidget(new QLabel("Data sprzedaży:"), 2, 0);
    mainLayout->addWidget(saleDate, 2, 1);
    mainLayout->addWidget(new QLabel("Skutek magazynowy:"),2,4);
    mainLayout->addWidget(checkStoreUpdating,2,5);
    mainLayout->addWidget( new QLabel("Zapłacono:"),3,4);
    mainLayout->addWidget(checkPaid,3,5);
    mainLayout->addWidget(new QLabel("Sposób płatności:"),4,0);
    mainLayout->addWidget(boxWayToPay,4,1);
    mainLayout->addWidget(new QLabel("Rabat[%]"),1,4);
    mainLayout->addWidget(lineDiscount,1,5);
    mainLayout->addWidget(new QLabel("Brutto po rabacie:"),8,7);
    mainLayout->addWidget(lineGoodsValueDiscount,8,8);
    mainLayout->addWidget(contractorData,0,7,4,2);
  if (controller->getSymbol()!="FM")
    {
    mainLayout->addWidget( new QLabel("Razem netto:"), 8, 0);
    mainLayout->addWidget(lineGoodsValueNet, 8, 1);
    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]+([.]|,)[0-9]{2}"),this);
    lineGoodsValueNet->setValidator(validator);
    }
    mainLayout->addWidget(new QLabel("Dokument odebrał:"), 9, 7);
    mainLayout->addWidget(lineReceiveName, 9, 8);
    mainLayout->addWidget(buttonChangeContractor, 1, 9);
    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]+([.]|,)[0-9]{2}"),this);
    lineDiscount->setValidator(validator);
    lineGoodsValueDiscount->setValidator(validator);
    lineGoodsValueDiscount->setReadOnly(true);
    lineGoodsValueNet->setReadOnly(true);
}

void DocumentRRView::initOptionalConnections()  {

    connect(buttonChangeContractor,SIGNAL(clicked()),controller,SLOT(selectContractor()));
    connect(boxWayToPay,SIGNAL(currentIndexChanged(int)),controller,SLOT(updatePaymentDate()));
    connect(paymentDate,SIGNAL(dateChanged(QDate)),controller,SLOT(changedPaid()));
    connect(buttonChangeContractor,SIGNAL(toggled(bool)),controller,SLOT(selectContractor()));
    connect(lineDiscount,SIGNAL(textEdited(QString)),controller,SLOT(discountChanged()));
}

