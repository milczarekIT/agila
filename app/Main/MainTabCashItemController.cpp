#include "MainTabCashItemController.h"

MainTabCashItemController::MainTabCashItemController()
{
    view = new MainTabCashItem(this);
    service = new CashDocumentService();
    documentTVModel = new CashDocumentTVModel();
    initModel();
    initFilters();

    initSelectingColumnVisibility();
    restoreTableState();
}

void MainTabCashItemController::addDocument(const int index)
{
    switch(index)
    {
        case 0:{
            dialogDocumentKPAdd();break;
        }
        case 1:{
            dialogDocumentKWAdd();break;
        }
    }
}

MainTabCashItemController::~MainTabCashItemController()
{
    saveTableState();
}

MainTabItem *MainTabCashItemController::getView()
{
    return view;
}

void MainTabCashItemController::initModel()
{
    documentTVModel->getDocuments();
    view->getTableView()->setCashDocumentModel(documentTVModel);
}

void MainTabCashItemController::initFilters()
{
    documentTVModel->setFromDateFilter(view->getFilterWidget()->getFromDate());
    documentTVModel->setToDateFilter(view->getFilterWidget()->getToDate());
    documentTVModel->getDocuments();
}

void MainTabCashItemController::dialogDocumentKPAdd()
{
    CashDocumentController dialog("KP",false,this);
    dialog.exec();
    documentTVModel->getDocuments();

}

void MainTabCashItemController::dialogDocumentKWAdd()
{
    CashDocumentController dialog("KW",false,this);
    dialog.exec();
    documentTVModel->getDocuments();
}

void MainTabCashItemController::printDocument()
{

}

void MainTabCashItemController::dialogDocumentEdit()
{
    if(view->getTableView()->getSymbol() == "")
    {
        MessageBox *messageBox = new MessageBox();
        messageBox->createInfoBox("Zaznacz dokument do edycji");
        delete messageBox;
    }
    else if (view->getTableView()->getSymbol().contains("KP"))
    {
        CashDocumentController dialog("KP",true,this);
        dialog.exec(view->getTableView()->getSymbol());
        documentTVModel->getDocuments();
    }
    else if (view->getTableView()->getSymbol().contains("KW"))
    {
        CashDocumentController dialog("KW",true,this);
        dialog.exec(view->getTableView()->getSymbol());
        documentTVModel->getDocuments();
    }
}

void MainTabCashItemController::documentRemove()
{
    service->removeCashDocument(view->getTableView()->getSymbol());
    documentTVModel->getDocuments();
}

void MainTabCashItemController::restoreTableState() {
    QByteArray state = tableStateManager->getState("MAIN_TAB_CASH");
    view->getTableView()->horizontalHeader()->restoreState(state);

    view->getTableView()->hideIdColumn(); // ukrywa id
    view->getTableView()->horizontalHeader()->setSortIndicatorShown(true); // pokazuje sortindicator

    int columnAtTable = view->getTableView()->horizontalHeader()->sortIndicatorSection();
    documentTVModel->sortByColumn(columnAtTable, view->getTableView()->horizontalHeader()->sortIndicatorOrder());
    documentTVModel->getDocuments();
}

void MainTabCashItemController::saveTableState() {
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("MAIN_TAB_CASH");
    if(state != oldState)
        tableStateManager->saveState("MAIN_TAB_CASH", state);
}

void MainTabCashItemController::changeColumnVisiblity(QList<int> visibleColumns)
{
    for(int column = 0; column < view->getTableView()->model()->columnCount(); column++) {
        if(visibleColumns.contains(column))
            view->getTableView()->setColumnHidden(column, false);
        else
            view->getTableView()->setColumnHidden(column, true);
    }
}

void MainTabCashItemController::initSelectingColumnVisibility()
{
    selectColumnsDialog = new SelectVisibleColumns(view->getTableView(), this);
    connect(selectColumnsDialog, SIGNAL(selectedColumnsChanged(QList<int>)), this, SLOT(changeColumnVisiblity(QList<int>)));
}

void MainTabCashItemController::sortByColumn(int column)
{
    documentTVModel->sortByColumn(column, view->getTableView()->horizontalHeader()->sortIndicatorOrder());
}

ModuleManager::Module MainTabCashItemController::module()
{
    return ModuleManager::Cash;
}
