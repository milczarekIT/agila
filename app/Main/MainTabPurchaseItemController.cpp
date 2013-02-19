#include "MainTabPurchaseItemController.h"

MainTabPurchaseItemController::MainTabPurchaseItemController()
{
    view = new MainTabPurchaseItem(this);
    purchaseInvoiceService = new PurchaseInvoiceService();
    fzkService = new DocumentFZKService();
    nkService = new DocumentNKService();
    initModel();
    initFilters();

    initSelectingColumnVisibility();
    restoreTableState();
}


MainTabPurchaseItemController::~MainTabPurchaseItemController()
{
    saveTableState();
    delete documentTVModel;
    delete purchaseInvoiceService;
    delete fzkService;
    delete nkService;
}

MainTabItem *MainTabPurchaseItemController::getView()
{
    return view;
}

void MainTabPurchaseItemController::addDocument(const int index)
{
    switch(index)
    {
        case 0:{
            dialogDocumentNKAdd();break;
        }
        case 1:{
            dialogDocumentRRAdd();break;
        }
        case 2:{
            dialogDocumentFZKAdd();break;
        }
        case 3:{
            dialogDocumentFZAdd();break;
        }
    }
}

void MainTabPurchaseItemController::dialogDocumentFZAdd()
{
PurchaseInvoiceController *controller = new PurchaseInvoiceController(this,"FZ",0);
controller->exec();
documentTVModel->getDocuments();
delete controller;
}

void MainTabPurchaseItemController::dialogDocumentRRAdd()
{
    DocumentRRController dialog(this, "RR",0);
    dialog.exec();
    documentTVModel->getDocuments();
}
void MainTabPurchaseItemController::dialogDocumentFZKAdd()
{
    DocumentFZKController dialog(this,0);
    dialog.exec();
    documentTVModel->getDocuments();
}

void MainTabPurchaseItemController::dialogDocumentNKAdd()
{
    DocumentNKController *controller = new DocumentNKController(this);
    controller->exec();
    documentTVModel->getDocuments();
    delete controller;
}

void MainTabPurchaseItemController::removeDocument()
{
    bool storeUpdate;
    MessageBox *msgBox;
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
    {
    msgBox= new MessageBox();
    msgBox->setText("Cofnąć skutek magazynowy?");
    msgBox->addButton("Tak",QMessageBox::AcceptRole);
    msgBox->addButton("Nie",QMessageBox::RejectRole);

    storeUpdate = false;
    }
    if(view->getTableView()->getSymbol().contains("RR")||view->getTableView()->getSymbol().contains("FZ"))
    {
        if(purchaseInvoiceService->getPurchaseInvoice(view->getTableView()->getSymbol()).getStoreResult())
        {
            if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
            {
                if(msgBox->exec()==QMessageBox::AcceptRole)
                   storeUpdate=true;
            }
        }
        purchaseInvoiceService->removePurchaseInvoice(view->getTableView()->getSymbol(),storeUpdate);
        documentTVModel->getDocuments();
     }
    else if(view->getTableView()->getSymbol().contains("FZK"))
    {
        if(fzkService->getDocumentFZK(view->getTableView()->getSymbol()).getStoreResult())
        {
            if(ApplicationManager::getInstance()->containsModule(ModuleManager::Warehouses))
            {
                if(msgBox->exec()==QMessageBox::AcceptRole)
                   storeUpdate=true;
            }
        }
        fzkService->removeDocumentFZK(view->getTableView()->getSymbol(),storeUpdate);
        documentTVModel->getDocuments();
    }
    delete msgBox;
}

void MainTabPurchaseItemController::issuedFZK()
{
    DocumentFZKController dialog(this,0);
    dialog.setFirst(true);
    dialog.insertInvoiceData(purchaseInvoiceService->getPurchaseInvoice(view->getTableView()->getSymbol()));
    dialog.exec();
    documentTVModel->getDocuments();
}

void MainTabPurchaseItemController::issuedKW()
{
    CashDocumentController dialog("KW",false,this);
    dialog.insertInvoiceData(purchaseInvoiceService->getPurchaseInvoice(view->getTableView()->getSymbol()));
    dialog.exec();
    emit issuedDocKW();
}

void  MainTabPurchaseItemController::changeDisabledMenuActions()
{
    if(!(view->getTableView()->getSymbol().section("/",0,0)=="FZ"))
    {
        view->getTableView()->getExtendedMenu()->getMenuPurchase()->getActionIssuedFZK()->setDisabled(true);
        view->getTableView()->getExtendedMenu()->getMenuPurchase()->getActionIssuedKW()->setDisabled(true);
    }
    else
    {
        view->getTableView()->getExtendedMenu()->getMenuPurchase()->getActionIssuedFZK()->setDisabled(false);
        view->getTableView()->getExtendedMenu()->getMenuPurchase()->getActionIssuedKW()->setDisabled(false);
    }
}

void MainTabPurchaseItemController::dialogDocumentEdit()
{
    if(view->getTableView()->getSymbol() == "")
    {
         MessageBox *messageBox = new MessageBox();
         messageBox->createInfoBox("Zaznacz dokument do edycji");
         delete messageBox;
    }
    else if(view->getTableView()->getSymbol().contains("RR"))
    {
         DocumentRRController dialog(this,"RR",1);
         dialog.exec(view->getTableView()->getSymbol());
         documentTVModel->getDocuments();
    }
    else if(view->getTableView()->getSymbol().contains("NK"))
    {
         DocumentNKController dialog(this);
         dialog.exec(view->getTableView()->getSymbol());
         documentTVModel->getDocuments();
    }
    else if(view->getTableView()->getSymbol().section("/",0,0)=="FZ")
    {
         PurchaseInvoiceController dialog(this,"FZ",1);
         dialog.exec(view->getTableView()->getSymbol());
         documentTVModel->getDocuments();
    }
    else if(view->getTableView()->getSymbol().contains("FZK"))
    {
        DocumentFZKController dialog(this,1);
        dialog.exec(view->getTableView()->getSymbol());
        documentTVModel->getDocuments();
    }
}

void MainTabPurchaseItemController::initModel()
{
    documentTVModel = new PurchaseDocumentTVModel();
    documentTVModel->getDocuments();
    view->getTableView()->setPurchaseDocumentModel(documentTVModel);
}

void MainTabPurchaseItemController::initFilters()
{
    documentTVModel->setFromDateFilter(view->getFilterWidget()->getFromDate());
    documentTVModel->setToDateFilter(view->getFilterWidget()->getToDate());
    documentTVModel->getDocuments();
}

void MainTabPurchaseItemController::restoreTableState() {
    QByteArray state = tableStateManager->getState("MAIN_TAB_PURCHASE");
    view->getTableView()->horizontalHeader()->restoreState(state);

    view->getTableView()->hideIdColumn(); // ukrywa id
    view->getTableView()->horizontalHeader()->setSortIndicatorShown(true); // pokazuje sortindicator

    int columnAtTable = view->getTableView()->horizontalHeader()->sortIndicatorSection();
    documentTVModel->sortByColumn(columnAtTable, view->getTableView()->horizontalHeader()->sortIndicatorOrder());
    documentTVModel->getDocuments();
}

void MainTabPurchaseItemController::saveTableState() {
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("MAIN_TAB_PURCHASE");
    if(state != oldState)
        tableStateManager->saveState("MAIN_TAB_PURCHASE", state);
}

void MainTabPurchaseItemController::changeColumnVisiblity(QList<int> visibleColumns)
{
    for(int column = 0; column < view->getTableView()->model()->columnCount(); column++) {
        if(visibleColumns.contains(column))
            view->getTableView()->setColumnHidden(column, false);
        else
            view->getTableView()->setColumnHidden(column, true);
    }
}

void MainTabPurchaseItemController::printDocument()
{
    PrintPurchaseDocumentController *pc = new PrintPurchaseDocumentController(view->getTableView()->getSymbol());

    if(view->getTableView()->getSymbol() == "") {
        MessageBox *messageBox = new MessageBox();
        messageBox->createInfoBox("Zaznacz dokument do druku");
        delete messageBox;
    }
    else if(view->getTableView()->getSymbol().contains("FZK")) {
        DocumentFZK doc = fzkService->getDocumentFZK(view->getTableView()->getSymbol());
        pc->print(&doc);
    }
    else if(view->getTableView()->getSymbol().contains("NK")) {
        DocumentNK doc = nkService->getDocumentNK(view->getTableView()->getSymbol());
        pc->print(&doc);
    }
    else if(view->getTableView()->getSymbol().contains("RR") || view->getTableView()->getSymbol().contains("FZ")) {
        PurchaseInvoice doc = purchaseInvoiceService->getPurchaseInvoice(view->getTableView()->getSymbol());
        pc->print(&doc);
    }
    delete pc;
}

void MainTabPurchaseItemController::initSelectingColumnVisibility()
{
    selectColumnsDialog = new SelectVisibleColumns(view->getTableView(), this);
    connect(selectColumnsDialog, SIGNAL(selectedColumnsChanged(QList<int>)), this, SLOT(changeColumnVisiblity(QList<int>)));
}

void MainTabPurchaseItemController::sortByColumn(int column)
{
    documentTVModel->sortByColumn(column, view->getTableView()->horizontalHeader()->sortIndicatorOrder());
}

ModuleManager::Module MainTabPurchaseItemController::module()
{
    return ModuleManager::Purchase;
}
