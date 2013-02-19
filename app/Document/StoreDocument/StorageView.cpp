#include "StorageView.h"

StorageView::StorageView(QWidget *parent, StorageController* controller) : StoreDocumentView(parent)    {

    this->controller = controller;
    this->mainLayout = new QGridLayout();
    mainLayout->setColumnMinimumWidth(7, 140);
    mainLayout->setColumnMinimumWidth(8, 140);
    mainLayout->setColumnMinimumWidth(9, 100);
    this->setLayout(mainLayout);
    this->setMaximumSize(1024,700);
    this->setMinimumSize(1024,700);
 if(controller->getEdition()==true)
    this->setWindowTitle( this->controller->getSymbol().append(" - Edycja dokumentu"));
   else
    this->setWindowTitle( this->controller->getSymbol().append(" - Nowy dokument"));
    initOptionalLineEdits();
    initGoodsTable();
    initAlwaysUsedLineEdits();
    initButtons();
    addOptionalComponents();
    addAlwaysUsedComponents();
    initAlwaysUsedConnections();
    setTabOrders();
}

void StorageView::setTabOrders()
{
    buttonGoodAdd->setFocus();
    setTabOrder(this->buttonGoodAdd,this->buttonGoodDel);
    setTabOrder(this->buttonGoodDel,this->buttonBox);
    setTabOrder(buttonBox,this->lineDocumentPlace);
    setTabOrder(lineDocumentPlace,dateIssue);
    setTabOrder(dateIssue,checkStoreUpdating);
    setTabOrder(checkStoreUpdating,lineIssueName);
    setTabOrder(lineIssueName,buttonGoodAdd);
    lineDocumentSymbol->setFocusPolicy(Qt::NoFocus);
    lineGoodsValueNet->setFocusPolicy(Qt::NoFocus);
}

StorageView::~StorageView()
{
    delete mainLayout;
}

