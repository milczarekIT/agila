#include "MainTabOrderItemController.h"

MainTabOrderItemController::MainTabOrderItemController()
{
    view = new MainTabOrderItem(this);
    documentTVModel = new OrderDocumentTVModel();
    orderService = new OrderService();
    initModel();
    initFilters();
    initSelectingColumnVisibility();
    restoreTableState();
}

void MainTabOrderItemController::addDocument(const int index)
{
    switch(index)
    {
        case 0:{
            dialogOrderZKAdd();break;
        }
        case 1:{
            dialogOrderZDAdd();break;
        }
    }
}

MainTabItem *MainTabOrderItemController::getView()
{
    return view;
}

void MainTabOrderItemController::dialogOrderZKAdd()
{
    OrderController dialog(this,"ZK",0);
    dialog.exec();
    this->documentTVModel->getDocuments();

}

void MainTabOrderItemController::dialogOrderZDAdd()
{
    OrderController dialog(this,"ZD",0);
    dialog.exec();
    this->documentTVModel->getDocuments();
}

void MainTabOrderItemController::issuedFV()
{
    InvoiceController dialog(this,"FV",0);
    dialog.insertOrderData(orderService->getOrder(view->getTableView()->getSymbol()));
    dialog.exec();
    emit issuedInvoice();
}

void MainTabOrderItemController::issuedFMP()
{
    InvoiceController dialog(this,"FMP",0);
    dialog.insertOrderData(orderService->getOrder(view->getTableView()->getSymbol()));
    dialog.exec();
    emit issuedInvoice();
}

void MainTabOrderItemController::issuedPRO()
{
    InvoiceController dialog(this, "PRO",0);
    dialog.insertOrderData(orderService->getOrder(view->getTableView()->getSymbol()));
    dialog.exec();
    emit issuedInvoice();
}

void MainTabOrderItemController::issuedPI()
{
    InvoiceController dialog(this, "PI",0);
    dialog.insertOrderData(orderService->getOrder(view->getTableView()->getSymbol()));
    dialog.exec();
    emit issuedInvoice();
}

void MainTabOrderItemController::issuedFM()
{
    DocumentFMController dialog(this,"FM",0);
    dialog.insertOrderData(orderService->getOrder(view->getTableView()->getSymbol()));
    dialog.exec();
    emit issuedInvoice();
}
void MainTabOrderItemController::issuedFZ()
{
    PurchaseInvoiceController dialog(this,"FZ",0);
    dialog.insertOrderData(orderService->getOrder(view->getTableView()->getSymbol()));
    dialog.exec();
    emit issuedPurchaseInvoice();
}

MainTabOrderItemController::~MainTabOrderItemController()
{
    saveTableState();
    delete documentTVModel;
}

void MainTabOrderItemController::changeDisabledMenuActions()
{
    if(view->getTableView()->getSymbol().contains("ZK"))
        view->getTableView()->getExtendedMenu()->getMenuSale()->getMenuSale()->setDisabled(false);
    else
        view->getTableView()->getExtendedMenu()->getMenuSale()->getMenuSale()->setDisabled(true);

    if(view->getTableView()->getSymbol().contains("ZD"))
        view->getTableView()->getExtendedMenu()->getMenuOrder()->getActionIssuedZD()->setDisabled(false);
    else
        view->getTableView()->getExtendedMenu()->getMenuOrder()->getActionIssuedZD()->setDisabled(true);
}

void MainTabOrderItemController::initModel()
{
    documentTVModel->getDocuments();
    view->getTableView()->setOrderDocumentModel(documentTVModel);
}

void MainTabOrderItemController::initFilters()
{
    documentTVModel->setFromDateFilter(view->getFilterWidget()->getFromDate());
    documentTVModel->setToDateFilter(view->getFilterWidget()->getToDate());
    documentTVModel->getDocuments();
}

void MainTabOrderItemController::dialogDocumentEdit()
{
    if(view->getTableView()->getSymbol() == "")
    {
         MessageBox *messageBox = new MessageBox();
         messageBox->createInfoBox("Zaznacz dokument do edycji");
         delete messageBox;
    }
    else if(view->getTableView()->getSymbol().contains("ZD")||view->getTableView()->getSymbol().contains("ZK"))
    {
         OrderController dialog(this,view->getTableView()->getSymbol().section("/",0,0),1);
         dialog.exec(view->getTableView()->getSymbol());
         documentTVModel->getDocuments();
    }
}

void MainTabOrderItemController::removeDocument()
{
    orderService->removeOrder(view->getTableView()->getSymbol());
    documentTVModel->getDocuments();
}

void MainTabOrderItemController::restoreTableState() {
    QByteArray state = tableStateManager->getState("MAIN_TAB_ORDER");
    view->getTableView()->horizontalHeader()->restoreState(state);

    view->getTableView()->hideIdColumn(); // ukrywa id
    view->getTableView()->horizontalHeader()->setSortIndicatorShown(true); // pokazuje sortindicator

    int columnAtTable = view->getTableView()->horizontalHeader()->sortIndicatorSection();
    documentTVModel->sortByColumn(columnAtTable, view->getTableView()->horizontalHeader()->sortIndicatorOrder());
    documentTVModel->getDocuments();
}

void MainTabOrderItemController::saveTableState() {
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("MAIN_TAB_ORDER");
    if(state != oldState)
        tableStateManager->saveState("MAIN_TAB_ORDER", state);
}

void MainTabOrderItemController::changeColumnVisiblity(QList<int> visibleColumns)
{
    for(int column = 0; column < view->getTableView()->model()->columnCount(); column++) {
        if(visibleColumns.contains(column))
            view->getTableView()->setColumnHidden(column, false);
        else
            view->getTableView()->setColumnHidden(column, true);
    }
}

void MainTabOrderItemController::printDocument()
{
    PrintOrderDocumentController *pc = new PrintOrderDocumentController(view->getTableView()->getSymbol());
    if(view->getTableView()->getSymbol() == "")
    {
        MessageBox *messageBox = new MessageBox();
        messageBox->createInfoBox("Zaznacz dokument do druku");
        delete messageBox;
    }
    else
    {
        Order doc = orderService->getOrder(view->getTableView()->getSymbol());
        pc->print(&doc);
    }
    delete pc;
}

void MainTabOrderItemController::initSelectingColumnVisibility()
{
    selectColumnsDialog = new SelectVisibleColumns(view->getTableView(), this);
    connect(selectColumnsDialog, SIGNAL(selectedColumnsChanged(QList<int>)), this, SLOT(changeColumnVisiblity(QList<int>)));
}

void MainTabOrderItemController::sortByColumn(int column)
{
    documentTVModel->sortByColumn(column, view->getTableView()->horizontalHeader()->sortIndicatorOrder());
}

ModuleManager::Module MainTabOrderItemController::module()
{
    return ModuleManager::Order;
}
