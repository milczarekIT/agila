#include "MainTabPriceItemController.h"

MainTabPriceItemController::MainTabPriceItemController() : MainTabDocumentItemController() {
    view = new MainTabPriceItem(this);
    initModel();
    plService = new PriceListService();

    initFilters();
    initSelectingColumnVisibility();
    restoreTableState();
}

MainTabPriceItemController::~MainTabPriceItemController() {
    saveTableState();
}

void MainTabPriceItemController::printDocument()
{

}

void MainTabPriceItemController::addDocument(const int index) {

    switch(index) {
        case 0: {
            dialogPriceListAdd();
            break;
        }
        case 1: {
            dialogOfferAdd();
            break;
        }
    }
}

void MainTabPriceItemController::dialogPriceListAdd() {
    PriceListController dialog(this);
    dialog.add();
    documentTVModel->getDocuments();
}

void MainTabPriceItemController::dialogOfferAdd() {
    OfferController dialog(this);
    dialog.add();
    documentTVModel->getDocuments();
}

void MainTabPriceItemController::dialogDocumentEdit()
{
    int row = view->getTableView()->currentIndex().row();
    QString symbol = view->getTableView()->model()->index(row,2).data().toString();

    if(view->getTableView()->getSymbol() == "")
    {
        MessageBox *messageBox = new MessageBox();
        messageBox->createInfoBox("Zaznacz dokument do edycji");
        delete messageBox;
    }
    else if (symbol.contains("CN"))
    {
        PriceListController dialog(this);
        dialog.edit(symbol);
        documentTVModel->getDocuments();
    }
    else if (symbol.contains("OF"))
    {
        OfferController dialog(this);
        dialog.edit(symbol);
        documentTVModel->getDocuments();
    }
}

void MainTabPriceItemController::removeDocument()
{
    MessageBox *msgBox = new MessageBox();
    int row = view->getTableView()->currentIndex().row();
    QString symbol = view->getTableView()->model()->index(row,2).data().toString();

    if(view->getTableView()->getId()==-1) {
        msgBox->createInfoBox("Zaznacz dokument do usunięcia");
    }
    else if(msgBox->createQuestionBox("Usuwanie dokumentu " + symbol) == MessageBox::YES) {
        plService->removePriceList(symbol);
    }

    delete msgBox;
    documentTVModel->getDocuments();
}

/*

void MainTabPriceItemController::issuedFK()
{
    DocumentFKController dialog(this,0);
    dialog.setFirst(true);
    dialog.insertInvoiceData(invoiceService->getInvoice(view->getTableView()->getSymbol()));
    dialog.exec();
    documentTVModel->getDocuments();
}
void MainTabPriceItemController::issuedKP()
{
    DocumentKPController dialog("KP",false,this);
    dialog.insertInvoiceData(invoiceService->getInvoice(view->getTableView()->getSymbol()));
    dialog.exec();
    emit issuedCashDoc();
}

void MainTabPriceItemController::issuedKW()
{
    DocumentKPController dialog("KW",false,this);
    dialog.insertInvoiceData(invoiceService->getInvoice(view->getTableView()->getSymbol()));
    dialog.exec();
    emit issuedCashDoc();
}*/

/*void MainTabPriceItemController::printDocument()
{
    PrintDialogController *pc = new PrintDialogController(view->getTableView()->getSymbol());
    if(view->getTableView()->getSymbol() == "")
    {
        MessageBox *messageBox = new MessageBox();
        messageBox->createInfoBox("Zaznacz dokument do druku");
        delete messageBox;
    }
    else if(view->getTableView()->getSymbol().contains("FK"))
    {
        DocumentFK doc = fkService->getDocumentFK(view->getTableView()->getSymbol());
        pc->print(&doc);
    }
    else
    {
         DocumentZAL docZal;
         docZal= zalService->getDocumentZAL(view->getTableView()->getSymbol());
         if(docZal.getDocumentType().contains("RZL")||docZal.getDocumentType().contains("ZAL"))
         {
             pc->print(&docZal);
         }
         else
         {
             Invoice doc = invoiceService->getInvoice(view->getTableView()->getSymbol());
             pc->print(&doc);

         }
    }
    delete pc;
}

void  MainTabPriceItemController::changeDisabledMenuActions()
{

    if(!(view->getTableView()->getSymbol().contains("FV")||view->getTableView()->getSymbol().contains("FMP")||view->getTableView()->getSymbol().contains("PRO")))
        view->getTableView()->getExtendedMenu()->getMenuSale()->getActionIssuedFK()->setDisabled(true);
    else
        view->getTableView()->getExtendedMenu()->getMenuSale()->getActionIssuedFK()->setDisabled(false);
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Cash))
    {
    if(checkAmount()>0 ||view->getTableView()->getSymbol().contains("FV"))
    {
        view->getTableView()->getExtendedMenu()->getMenuSale()->getActionIssuedCashDocKW()->setDisabled(true);
        view->getTableView()->getExtendedMenu()->getMenuSale()->getActionIssuedCashDocKP()->setDisabled(false);
    }
    else if(checkAmount()<0)
    {
        view->getTableView()->getExtendedMenu()->getMenuSale()->getActionIssuedCashDocKW()->setDisabled(false);
        view->getTableView()->getExtendedMenu()->getMenuSale()->getActionIssuedCashDocKP()->setDisabled(true);
    }
    else if(checkAmount()==0)
    {
        view->getTableView()->getExtendedMenu()->getMenuSale()->getActionIssuedCashDocKW()->setDisabled(true);
        view->getTableView()->getExtendedMenu()->getMenuSale()->getActionIssuedCashDocKP()->setDisabled(true);
    }
    }
}

float MainTabPriceItemController::checkAmount()
{
    float amount = fkService->getDocumentFK(view->getTableView()->getSymbol()).getTotal()-
                   fkService->getDocumentFK(view->getTableView()->getSymbol()).getInvoice().getTotal();
    return amount;
}*/

void MainTabPriceItemController::initModel()
{
    documentTVModel = new PriceDocumentTVModel();
    documentTVModel->getDocuments();
    view->getTableView()->setPriceDocumentModel(documentTVModel);
}

void MainTabPriceItemController::initFilters()
{
    documentTVModel->setFromDateFilter(view->getFilterWidget()->getFromDate());
    documentTVModel->setToDateFilter(view->getFilterWidget()->getToDate());
    documentTVModel->getDocuments();
}

void MainTabPriceItemController::restoreTableState() {
    QByteArray state = tableStateManager->getState("MAIN_TAB_PRICE");
    view->getTableView()->horizontalHeader()->restoreState(state);

    view->getTableView()->hideIdColumn(); // ukrywa id
    view->getTableView()->horizontalHeader()->setSortIndicatorShown(true); // pokazuje sortindicator

    int columnAtTable = view->getTableView()->horizontalHeader()->sortIndicatorSection();
    documentTVModel->sortByColumn(columnAtTable, view->getTableView()->horizontalHeader()->sortIndicatorOrder());
    documentTVModel->getDocuments();
}

void MainTabPriceItemController::saveTableState() {
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("MAIN_TAB_PRICE");
    if(state != oldState)
        tableStateManager->saveState("MAIN_TAB_PRICE", state);
}

void MainTabPriceItemController::changeColumnVisiblity(QList<int> visibleColumns)
{
    for(int column = 0; column < view->getTableView()->model()->columnCount(); column++) {
        if(visibleColumns.contains(column))
            view->getTableView()->setColumnHidden(column, false);
        else
            view->getTableView()->setColumnHidden(column, true);
    }
}

void MainTabPriceItemController::initSelectingColumnVisibility()
{
    selectColumnsDialog = new SelectVisibleColumns(view->getTableView(), this);
    connect(selectColumnsDialog, SIGNAL(selectedColumnsChanged(QList<int>)), this, SLOT(changeColumnVisiblity(QList<int>)));
}

void MainTabPriceItemController::sortByColumn(int column)
{
    documentTVModel->sortByColumn(column, view->getTableView()->horizontalHeader()->sortIndicatorOrder());
}

ModuleManager::Module MainTabPriceItemController::module()
{
    return ModuleManager::Price;
}

MainTabItem *MainTabPriceItemController::getView()
{
    return view;
}
