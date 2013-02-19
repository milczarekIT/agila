#include "DocumentFMView.h"

DocumentFMView::DocumentFMView(QWidget *parent, DocumentFMController* controller) : SaleView(parent)
{
    this->controller = controller;
    this->mainLayout = new QGridLayout();
    mainLayout->setColumnMinimumWidth(4, 150);
    mainLayout->setColumnMinimumWidth(9, 100);
    this->setLayout(mainLayout);
    this->setMinimumSize(1024,768);
 if(controller->getEdition()==true)
    this->setWindowTitle("FM - Edycja dokumentu");
   else
    this->setWindowTitle("FM - Nowy dokument");
    initOptionalLineEdits();
    initAlwaysUsedLineEdits();
    initButtons();
    initOptionalButtons();
    initGoodsTable();
    initOptionalConnections();
    initAlwaysUsedConnections();
    addOptionalComponents(); //zawsze wywoływana po wszystkich inicjalizacjach!
    addAlwaysUsedComponents();
    setTabOrders();
}

void DocumentFMView::setTabOrders()
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
    lineGoodsValue->setFocusPolicy(Qt::NoFocus);
}

DocumentFMView::~DocumentFMView()
{
    delete mainLayout;
    delete controller;
}

void DocumentFMView::initGoodsTable()  {

  goodsTable = new QTableWidget();
  goodsTable->setColumnCount(4);
  goodsTable->setColumnWidth(0,500);
  goodsTable->setColumnWidth(1,250);
  goodsTable->setColumnWidth(2,150);
  goodsTable->setColumnWidth(3,150);
  goodsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  setHeaders(0,new QTableWidgetItem("Nazwa"));
  setHeaders(1,new QTableWidgetItem("Ilość"));
  setHeaders(2,new QTableWidgetItem("Cena brutto"));
  setHeaders(3,new QTableWidgetItem("Wartość brutto"));
}



