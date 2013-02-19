#include "MainTabStoreItemController.h"

MainTabStoreItemController::MainTabStoreItemController()
{
    view = new MainTabStoreItem(this);
    storageService = new StorageService();
    wzService = new DocumentWZService();
    pzService = new DocumentPZService();
    initModel();
    initFilters();

    initSelectingColumnVisibility();
    restoreTableState();
}

MainTabItem *MainTabStoreItemController::getView()
{
    return view;
}

MainTabStoreItemController::~MainTabStoreItemController()
{
    saveTableState();
    delete documentTVModel;
}
void MainTabStoreItemController::printDocument()
{
    PrintStoreDocumentController *pc = new PrintStoreDocumentController(view->getTableView()->getSymbol());
    if(view->getTableView()->getSymbol() == "")
    {
        MessageBox *messageBox = new MessageBox();
        messageBox->createInfoBox("Zaznacz dokument do druku");
        delete messageBox;
    }
    else if(view->getTableView()->getSymbol().contains("PW")||view->getTableView()->getSymbol().contains("RW"))
    {
        StoreDocument doc = storageService->getStoreDocument(view->getTableView()->getSymbol());
        pc->print(&doc);
    }
    else if (view->getTableView()->getSymbol().contains("PZ"))
    {
        DocumentPZ doc = pzService->getDocumentPZ(view->getTableView()->getSymbol());
        pc->print(&doc);
    }
    else if (view->getTableView()->getSymbol().contains("WZ"))
    {
        DocumentWZ doc = wzService->getDocumentWZ(view->getTableView()->getSymbol());
        pc->print(&doc);
    }
    delete pc;
}

void MainTabStoreItemController::addDocument(const int index)
{
    switch(index)
    {
        case 0:{
            dialogStorePZAdd();break;
        }
        case 1:{
            dialogStoreWZAdd();break;
        }
        case 2:{
            dialogStoreRWAdd();break;
        }
        case 3:{
            dialogStorePWAdd();break;
        }
        case 4:{
            dialogStoreMMAdd();break;
        }
    }
}

void MainTabStoreItemController::dialogStorePZAdd()
{
    DocumentPZController* controller = new DocumentPZController(this,0);
    controller->exec();
    delete controller;
    refreshTabStore();
}

void MainTabStoreItemController::dialogStoreWZAdd()
{
    DocumentWZController* controller = new DocumentWZController(this,0);
    controller->exec();
    delete controller;
    refreshTabStore();
}

void MainTabStoreItemController::dialogStoreRWAdd()
{
    StorageController* controller = new StorageController(this,0,"RW");
    controller->exec();
    delete controller;
    refreshTabStore();
}

void MainTabStoreItemController::dialogStorePWAdd()
{
    StorageController* controller = new StorageController(this,0,"PW");
    controller->exec();
    delete controller;
    refreshTabStore();
}

void MainTabStoreItemController::dialogStoreMMAdd()
{
    StorageController* controller = new StorageController(this,0,"MM");
    controller->exec();
    delete controller;
    refreshTabStore();

}

void MainTabStoreItemController::refreshTabStore() {
    documentTVModel->getDocuments();
}

void MainTabStoreItemController::initModel()
{
    documentTVModel = new StoreDocumentTVModel();
    documentTVModel->getDocuments();
    view->getTableView()->setStoreDocumentModel(documentTVModel);
}

void MainTabStoreItemController::initFilters()
{
    documentTVModel->setFromDateFilter(view->getFilterWidget()->getFromDate());
    documentTVModel->setToDateFilter(view->getFilterWidget()->getToDate());
    documentTVModel->getDocuments();
}
void MainTabStoreItemController::dialogDeleteStore()
{
    MessageBox *msgBox = new MessageBox();
       msgBox->setText("Cofnąć skutek magazynowy?");
       msgBox->addButton("Tak",QMessageBox::AcceptRole);
       msgBox->addButton("Nie",QMessageBox::RejectRole);

       bool storeUpdate = false;
       QString symbol = view->getTableView()->getSymbol();
       if(symbol.contains("RW")||symbol.contains("PW")||symbol.contains("MM"))
       {
           if(storageService->getStoreDocument(symbol).getStoreResult())
           {
              if(msgBox->exec()==QMessageBox::AcceptRole)
                 storeUpdate=true;
           }
               storageService->removeDocument(symbol,storeUpdate);
       }
       else if(symbol.contains("WZ"))
       {
           if(wzService->getDocumentWZ(symbol).getStoreResult())
           {
              if(msgBox->exec()==QMessageBox::AcceptRole)
                 storeUpdate=true;
           }
           wzService->removeDocument(symbol,storeUpdate);
        }
      else if(symbol.contains("PZ"))
       {
           if(pzService->getDocumentPZ(symbol).getStoreResult())
           {
              if(msgBox->exec()==QMessageBox::AcceptRole)
                 storeUpdate=true;
           }
           pzService->removeDocument(symbol,storeUpdate);
        }
        documentTVModel->getDocuments();
       delete msgBox;
}
void MainTabStoreItemController::dialogEditStore()
{
    QString symbol = view->getTableView()->getSymbol();

    if(symbol.contains("PZ"))
    {
        DocumentPZController* controller = new DocumentPZController(this,1);
        controller->exec(symbol);
        delete controller;
    }
    else if(symbol.contains("WZ"))
    {
        DocumentWZController* controller = new DocumentWZController(this,1);
        controller->exec(symbol);
        delete controller;
    }
    else if(symbol.contains("RW")||symbol.contains("PW")||symbol.contains("MM"))
    {
        StorageController* controller = new StorageController(this,0,"PW");
        controller->exec(symbol);
        delete controller;
    }

    refreshTabStore();
}

void MainTabStoreItemController::restoreTableState() {
    QByteArray state = tableStateManager->getState("MAIN_TAB_STORE");
    view->getTableView()->horizontalHeader()->restoreState(state);

    view->getTableView()->hideIdColumn(); // ukrywa id
    view->getTableView()->horizontalHeader()->setSortIndicatorShown(true); // pokazuje sortindicator

    int columnAtTable = view->getTableView()->horizontalHeader()->sortIndicatorSection();
    documentTVModel->sortByColumn(columnAtTable, view->getTableView()->horizontalHeader()->sortIndicatorOrder());
    documentTVModel->getDocuments();
}

void MainTabStoreItemController::saveTableState() {
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("MAIN_TAB_STORE");
    if(state != oldState)
        tableStateManager->saveState("MAIN_TAB_STORE", state);
}

void MainTabStoreItemController::changeColumnVisiblity(QList<int> visibleColumns)
{
    for(int column = 0; column < view->getTableView()->model()->columnCount(); column++) {
        if(visibleColumns.contains(column))
            view->getTableView()->setColumnHidden(column, false);
        else
            view->getTableView()->setColumnHidden(column, true);
    }
}

void MainTabStoreItemController::initSelectingColumnVisibility()
{
    selectColumnsDialog = new SelectVisibleColumns(view->getTableView(), this);
    connect(selectColumnsDialog, SIGNAL(selectedColumnsChanged(QList<int>)), this, SLOT(changeColumnVisiblity(QList<int>)));
}

void MainTabStoreItemController::sortByColumn(int column)
{
    documentTVModel->sortByColumn(column, view->getTableView()->horizontalHeader()->sortIndicatorOrder());
}

ModuleManager::Module MainTabStoreItemController::module()
{
    return ModuleManager::Warehouses;
}
