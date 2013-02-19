#include "MainTabSaleItemController.h"

MainTabSaleItemController::MainTabSaleItemController()
{
    view = new MainTabSaleItem(this);
    invoiceService = new InvoiceService();
    fkService = new DocumentFKService();
    zalService = new DocumentZALService();
    initModel();
    initFilters();
    initSelectingColumnVisibility();

    restoreTableState();
}

MainTabSaleItemController::~MainTabSaleItemController()
{
    saveTableState();
    delete invoiceService;
    delete fkService;
}

void MainTabSaleItemController::addDocument(const int index)
{
    switch(index)
    {
        case 0:{
            dialogInvoiceAdd();break;
        }
        case 1:{
            dialogDocumentFKAdd();break;
        }
        case 2:{
            dialogDocumentFMPAdd();break;
        }
        case 3:{
            dialogDocumentPROAdd();break;
        }
        case 4:{
            dialogDocumentFMAdd();break;
        }
        case 5:{
            dialogDocumentPIAdd();break;
        }
        case 6:{
            dialogDocumentPAAdd();break;
        }
        case 7:{
            dialogDocumentZALAdd();break;
        }
        case 8:{
            dialogDocumentRZLAdd();break;
        }
    }
}

MainTabItem *MainTabSaleItemController::getView()
{
    return view;
}

void MainTabSaleItemController::dialogInvoiceAdd()
{
    InvoiceController dialog(this,"FV",0);
    dialog.exec();
    documentTVModel->getDocuments();
}

void MainTabSaleItemController::dialogDocumentFMPAdd()
{
    InvoiceController dialog(this,"FMP",0);
    dialog.exec();
    documentTVModel->getDocuments();
}

void MainTabSaleItemController::dialogDocumentPROAdd()
{
    InvoiceController dialog(this, "PRO",0);
    dialog.exec();
    documentTVModel->getDocuments();
}

void MainTabSaleItemController::dialogDocumentPIAdd()
{
    InvoiceController dialog(this, "PI",0);
    dialog.exec();
    documentTVModel->getDocuments();
}
void MainTabSaleItemController::dialogDocumentZALAdd()
{
    DocumentZALController dialog(this, "ZAL",0);
    dialog.exec();
    documentTVModel->getDocuments();
}
void MainTabSaleItemController::dialogDocumentRZLAdd()
{
    DocumentZALController dialog(this,"RZL",0);
    dialog.exec();
    documentTVModel->getDocuments();
}
void MainTabSaleItemController::dialogDocumentPAAdd()
{
    DocumentPAController dialog(this,0);
    dialog.exec();
    documentTVModel->getDocuments();
}

void MainTabSaleItemController::dialogDocumentFKAdd()
{
    DocumentFKController dialog(this,0);
    dialog.exec();
    documentTVModel->getDocuments();
}

void MainTabSaleItemController::dialogDocumentFMAdd()
{
    DocumentFMController dialog(this,"FM",0);
    dialog.exec();
    documentTVModel->getDocuments();
}

void MainTabSaleItemController::issuedFK()
{
    DocumentFKController dialog(this,0);
    dialog.setFirst(true);
    dialog.insertInvoiceData(invoiceService->getInvoice(view->getTableView()->getSymbol()));
    dialog.exec();
    documentTVModel->getDocuments();
}
void MainTabSaleItemController::issuedKP()
{
    CashDocumentController dialog("KP",false,this);
    dialog.insertInvoiceData(invoiceService->getInvoice(view->getTableView()->getSymbol()));
    dialog.exec();
    emit issuedCashDoc();
}

void MainTabSaleItemController::issuedKW()
{
    CashDocumentController dialog("KW",false,this);
    dialog.insertInvoiceData(invoiceService->getInvoice(view->getTableView()->getSymbol()));
    dialog.exec();
    emit issuedCashDoc();
}

void MainTabSaleItemController::printDocument()
{
    PrintSaleDocumentController *pc = new PrintSaleDocumentController(view->getTableView()->getSymbol());
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

void  MainTabSaleItemController::changeDisabledMenuActions()
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

float MainTabSaleItemController::checkAmount()
{
    float amount = fkService->getDocumentFK(view->getTableView()->getSymbol()).getTotal()-
                   fkService->getDocumentFK(view->getTableView()->getSymbol()).getInvoice().getTotal();
    return amount;
}

void MainTabSaleItemController::dialogDocumentEdit()
{
    if(view->getTableView()->getSymbol() == "")
    {
        MessageBox *messageBox = new MessageBox();
        messageBox->createInfoBox("Zaznacz dokument do edycji");
        delete messageBox;
    }
    else if (view->getTableView()->getSymbol().contains("PA"))
    {
        DocumentPAController dialog(this,1);
        dialog.exec(view->getTableView()->getSymbol());
        documentTVModel->getDocuments();
    }
    else if (view->getTableView()->getSymbol().contains("FK"))
    {
        DocumentFKController dialog(this,1);
        dialog.exec(view->getTableView()->getSymbol());
        documentTVModel->getDocuments();
    }
    else if (view->getTableView()->getSymbol().section("/",0,0)=="FM")
    {
        DocumentFMController dialog(this,"FM",1);
        dialog.exec(view->getTableView()->getSymbol());
        documentTVModel->getDocuments();
    }

    else if (view->getTableView()->getSymbol().contains("FV")||view->getTableView()->getSymbol().contains("FMP")
             ||view->getTableView()->getSymbol().contains("PRO")||view->getTableView()->getSymbol().contains("PI"))
    {
        DocumentZAL doc;
        doc= zalService->getDocumentZAL(view->getTableView()->getSymbol());
         if(doc.getDocumentType().contains("RZL")||doc.getDocumentType().contains("ZAL"))
        {   DocumentZALController*dialog;

            if(doc.getDocumentType().contains("RZL"))
            dialog = new DocumentZALController(this,"RZL",1);
            else
            dialog = new DocumentZALController(this,"ZAL",1);

            dialog->exec(view->getTableView()->getSymbol());
            documentTVModel->getDocuments();
            delete dialog;
        }
        else
         {
        InvoiceController dialog(this,view->getTableView()->getSymbol().section("/",0,0),1);
        dialog.exec(view->getTableView()->getSymbol());
        documentTVModel->getDocuments();
         }
    }
}

void MainTabSaleItemController::removeDocument()
{
    MessageBox *msgBox = new MessageBox();

    bool storeUpdate = false;

    if(view->getTableView()->getId()==-1)
    {
        msgBox->createInfoBox("Zaznacz dokument do usunięcia");
    }

    if(view->getTableView()->getSymbol().contains("FV")||view->getTableView()->getSymbol().contains("FMP")||view->getTableView()->getSymbol().contains("PRO")
        ||view->getTableView()->getSymbol().contains("PI")||view->getTableView()->getSymbol().contains("PA")||view->getTableView()->getSymbol().section("/",0,0)=="FM")
    {
        if(msgBox->createQuestionBox("Usuwanie dokumentu " +view->getTableView()->getSymbol())== MessageBox::YES)
        {

            if(invoiceService->getInvoice(view->getTableView()->getSymbol()).getStoreResult())
              {
                   if(msgBox->createQuestionBox("Usunięto dokument "+view->getTableView()->getSymbol(),"Cofnąć skutek magazynowy?")==MessageBox::YES)
                    storeUpdate=true;
              }
        invoiceService->removeInvoice(view->getTableView()->getSymbol(),storeUpdate);
        }
    }

    if(view->getTableView()->getSymbol().contains("FK"))
    {
        if( msgBox->createQuestionBox("Usuwanie dokumentu " +view->getTableView()->getSymbol())== MessageBox::YES)
        {

            if(fkService->getDocumentFK(view->getTableView()->getSymbol()).getStoreResult())
            {
                if(msgBox->createQuestionBox("Usunięto dokument "+view->getTableView()->getSymbol(),"Cofnąć skutek magazynowy?")==MessageBox::YES)
                  storeUpdate=true;
            }
        fkService->removeDocumentFK(view->getTableView()->getSymbol(),storeUpdate);
        }
    }

    delete msgBox;
    documentTVModel->getDocuments();
}

void MainTabSaleItemController::initModel()
{
    documentTVModel = new SaleDocumentTVModel();
    documentTVModel->getDocuments();
    view->getTableView()->setSaleDocumentModel(documentTVModel);
}

void MainTabSaleItemController::initFilters()
{
    documentTVModel->setFromDateFilter(view->getFilterWidget()->getFromDate());
    documentTVModel->setToDateFilter(view->getFilterWidget()->getToDate());
    documentTVModel->getDocuments();
}

void MainTabSaleItemController::restoreTableState() {
    QByteArray state = tableStateManager->getState("MAIN_TAB_SALE");
    view->getTableView()->horizontalHeader()->restoreState(state);

    view->getTableView()->hideIdColumn(); // ukrywa id
    view->getTableView()->horizontalHeader()->setSortIndicatorShown(true); // pokazuje sortindicator

    int columnAtTable = view->getTableView()->horizontalHeader()->sortIndicatorSection();
    documentTVModel->sortByColumn(columnAtTable, view->getTableView()->horizontalHeader()->sortIndicatorOrder());
    documentTVModel->getDocuments();
}

void MainTabSaleItemController::saveTableState() {
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("MAIN_TAB_SALE");
    if(state != oldState)
        tableStateManager->saveState("MAIN_TAB_SALE", state);
}

void MainTabSaleItemController::changeColumnVisiblity(QList<int> visibleColumns)
{
    for(int column = 0; column < view->getTableView()->model()->columnCount(); column++) {
        if(visibleColumns.contains(column))
            view->getTableView()->setColumnHidden(column, false);
        else
            view->getTableView()->setColumnHidden(column, true);
    }
}

void MainTabSaleItemController::initSelectingColumnVisibility()
{
    selectColumnsDialog = new SelectVisibleColumns(view->getTableView(), this);
    connect(selectColumnsDialog, SIGNAL(selectedColumnsChanged(QList<int>)), this, SLOT(changeColumnVisiblity(QList<int>)));
}

void MainTabSaleItemController::sortByColumn(int column)
{
    documentTVModel->sortByColumn(column, view->getTableView()->horizontalHeader()->sortIndicatorOrder());
}

ModuleManager::Module MainTabSaleItemController::module()
{
    return ModuleManager::Sale;
}
