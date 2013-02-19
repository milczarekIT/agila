#include "PurchaseInvoiceView.h"

PurchaseInvoiceView::PurchaseInvoiceView(QWidget *parent, PurchaseInvoiceController* controller) : SaleView(parent)   {

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
    initPurchaseComponents();
    setTabOrders();
}

PurchaseInvoiceView::~PurchaseInvoiceView()
{
 delete mainLayout;
 delete controller;
}

void PurchaseInvoiceView::initPurchaseComponents(){

this->purchaseDocSymbol = new QLineEdit();
mainLayout->addWidget(purchaseDocSymbol,4,5);
mainLayout->addWidget( new QLabel("Wystawiono dla dokumentu nr:"),4,4);
mainLayout->addWidget(new QLabel("Data zakupu:"), 2, 0);
}
void PurchaseInvoiceView::setTabOrders()
{
    this->buttonChangeContractor->setFocus();
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    {
        setTabOrder(this->buttonChangeContractor,this->buttonOrderOrFactureAdd);
        setTabOrder(this->buttonOrderOrFactureAdd, this->buttonGoodAdd);
    }
    else
        setTabOrder(buttonChangeContractor,buttonGoodAdd);

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
        setTabOrder(saleDate,paymentDate);

    setTabOrder(paymentDate,checkPaid);
    setTabOrder(checkPaid,boxWayToPay);
    setTabOrder(boxWayToPay,purchaseDocSymbol);
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    {
        setTabOrder(purchaseDocSymbol,lineOrder);
        setTabOrder(lineOrder,lineIssueName);
    }
    else
    setTabOrder(purchaseDocSymbol,lineIssueName);


    setTabOrder(lineIssueName,lineReceiveName);
    setTabOrder(lineReceiveName,buttonChangeContractor);
    lineDocumentSymbol->setFocusPolicy(Qt::NoFocus);
    lineGoodsValueDiscount->setFocusPolicy(Qt::NoFocus);
    lineGoodsValueNet->setFocusPolicy(Qt::NoFocus);
    lineGoodsValue->setFocusPolicy(Qt::NoFocus);
}
QLineEdit* PurchaseInvoiceView::getPurchaseOrFactureSymbol(){return this->purchaseDocSymbol;}

