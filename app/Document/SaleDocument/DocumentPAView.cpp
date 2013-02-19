#include "DocumentPAView.h"

DocumentPAView::DocumentPAView(QWidget *parent, DocumentPAController* controller) : SaleView(parent) {
    this->controller = controller;
    this->mainLayout = new QGridLayout();
    mainLayout->setColumnMinimumWidth(4, 150);
    mainLayout->setColumnMinimumWidth(9, 100);
    this->setLayout(mainLayout);
    this->setMinimumSize(1024,768);

    if(controller->getEdition()==true)
        this->setWindowTitle("PA - Edycja dokumentu");
    else
        this->setWindowTitle("PA - Nowy dokument");

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
void DocumentPAView::setTabOrders()
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    {
    this->buttonOrderOrFactureAdd->setFocus();
    setTabOrder(this->buttonOrderOrFactureAdd, this->buttonGoodAdd);
    }
    else
    buttonGoodAdd->setFocus();
    setTabOrder(this->buttonGoodAdd,this->buttonGoodDel);
    setTabOrder(this->buttonGoodDel,this->buttonBox);
    setTabOrder(buttonBox,this->lineDocumentPlace);
    setTabOrder(lineDocumentPlace,dateIssue);
    setTabOrder(this->dateIssue,lineDiscount);
    setTabOrder(lineDiscount,saleDate);

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        setTabOrder(saleDate,this->checkStoreUpdating);
        setTabOrder(checkStoreUpdating,paymentDate);
    }
    else
        setTabOrder(saleDate,lineIssueName);
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    setTabOrder(lineIssueName,buttonOrderOrFactureAdd);
    else
        setTabOrder(lineIssueName,buttonGoodAdd);
    lineGoodsValueDiscount->setFocusPolicy(Qt::NoFocus);
    lineGoodsValue->setFocusPolicy(Qt::NoFocus);
    lineGoodsValueDiscount->setReadOnly(true);
    lineGoodsValueNet->setReadOnly(true);
}

DocumentPAView::~DocumentPAView()
{
    delete controller;
}

void DocumentPAView::initOptionalConnections()  {

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    connect(buttonOrderOrFactureAdd,SIGNAL(clicked()),controller,SLOT(selectOrderOrFacture()));
    connect(lineDiscount,SIGNAL(textEdited(QString)),controller,SLOT(discountChanged()));
}

void DocumentPAView::initOptionalButtons()
{
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    buttonOrderOrFactureAdd = new Button(ButtonStruct("Zmień",QSize(100,28)));
}

void DocumentPAView::addOptionalComponents() {

    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]+([.]|,)[0-9]{2}"),this);

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        checkStoreUpdating->setChecked(true);

    saleDate->setDate(QDate::currentDate());
    mainLayout->addWidget(new QLabel("Data sprzedaży:"), 2, 0);
    mainLayout->addWidget(saleDate, 2, 1);
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
        mainLayout->addWidget(new QLabel("Skutek magazynowy:"),2,4);
        mainLayout->addWidget(checkStoreUpdating,2,5);
    }
    mainLayout->addWidget(new QLabel("Razem netto:"), 8, 0);
    mainLayout->addWidget(lineGoodsValueNet, 8, 1);
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    {
    mainLayout->addWidget(new QLabel("Zamówienie nr:"),0,7);
    mainLayout->addWidget(lineOrder,0,8);
    }
    mainLayout->addWidget(new QLabel("Rabat[%]"),1,4);
    mainLayout->addWidget(lineDiscount,1,5);
    mainLayout->addWidget(new QLabel("Brutto po rabacie:"),8,7);
    mainLayout->addWidget(lineGoodsValueDiscount,8,8);
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    mainLayout->addWidget(buttonOrderOrFactureAdd,0,9);
    lineGoodsValueNet->setValidator(validator);
    lineDiscount->setValidator(new QRegExpValidator(QRegExp("[0-9]{2}+([.]|,)[0-9]{2}"),this));
}


void DocumentPAView::initOptionalLineEdits()    {

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    lineOrder = new QLineEdit();
    lineGoodsValueNet= new QLineEdit();
    lineReceiveName = new QLineEdit();
    saleDate = new DateEdit();

    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
        checkStoreUpdating = new QCheckBox();

    lineGoodsValueDiscount = new QLineEdit();
    lineDiscount = new QLineEdit();
}






