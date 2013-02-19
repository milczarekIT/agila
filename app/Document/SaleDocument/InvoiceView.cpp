#include "InvoiceView.h"

InvoiceView::InvoiceView(QWidget *parent, InvoiceController* controller) : SaleView(parent)
{
    this->controller = controller;
    this->mainLayout = new QGridLayout();
    mainLayout->setColumnMinimumWidth(4, 150);
    mainLayout->setColumnMinimumWidth(9, 100);
    this->setMinimumSize(1024,700);
    this->setLayout(mainLayout);

    if(controller->getEdition()==true)
        this->setWindowTitle(controller->getSymbol().append(" - Edycja dokumentu"));
    else
        this->setWindowTitle(controller->getSymbol().append(" - Nowy dokument"));

    initOptionalLineEdits();
    initOptionalButtons();
    initGoodsTable();
    addOptionalComponents();
    initAlwaysUsedLineEdits();
    initButtons();
    addAlwaysUsedComponents();
    initAlwaysUsedConnections();
    initOptionalConnections();
    setTabOrders();
}
void InvoiceView::setTabOrders()
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
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    {
        setTabOrder(boxWayToPay,lineOrder);
        setTabOrder(lineOrder,lineIssueName);
    }
    else
        setTabOrder(boxWayToPay,lineIssueName);

    setTabOrder(lineIssueName,lineReceiveName);
    setTabOrder(lineReceiveName,buttonChangeContractor);
    lineGoodsValueDiscount->setFocusPolicy(Qt::NoFocus);
    lineGoodsValueNet->setFocusPolicy(Qt::NoFocus);
    lineGoodsValue->setFocusPolicy(Qt::NoFocus);
}
InvoiceView::~InvoiceView()
{
    delete mainLayout;
    delete controller;
}

