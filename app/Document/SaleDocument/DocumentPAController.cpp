#include "DocumentPAController.h"

DocumentPAController::DocumentPAController(QWidget* parent, bool edit) {
    this->symbol="PA";
    this->edition=edit;
    this->view = new DocumentPAView(parent,this);
    this->invoiceService = new InvoiceService();
    this->validator = new DocumentValidator(view,symbol);
    this->manager = new DocumentPAManager();
    restoreTableState();
}

DocumentPAController::~DocumentPAController()
{
    saveTableState();
    delete invoiceService;
    delete validator;
    delete manager;
}

void DocumentPAController::exec ()
{
    dnc = new DocumentNumeratorController(symbol);
    QString nextSymbol = dnc->getNextSymbol();
    view->getLineDocumentSymbol()->setText(nextSymbol);
    delete dnc;
    dnc = NULL;

    QString documentPlace = smodel->getDefualtDocumentPlace().getName();
    this->view->setLineDocumentPlace(documentPlace);

    this->view->setLineIssueName(ApplicationManager::getInstance()->getLoggedUser().getName()); //TODO dane użytkownika programu!!!!!!!!!!!!!!!!!


    if (view->exec())
    {
        getDocumentData();
        invoiceService->addInvoice(manager->getInvoicePolicy()->getInvoice());
        this->printDoc();
        return;
    }
    return;
}

void DocumentPAController::exec(QString Symbol)
{
    this->edition = true;
    this->totalFromBase=true;
    manager->getInvoicePolicy()->setInvoice(invoiceService->getInvoice(Symbol));
    manager->getInvoicePolicy()->setOldInvoice(manager->getInvoicePolicy()->getInvoice());
    view->setLineDocumentSymbol(manager->getInvoicePolicy()->getInvoice().getSymbol());
    view->setLineDocumentPlace(manager->getInvoicePolicy()->getInvoice().getDocumentPlace());
    view->setDateIssue(manager->getInvoicePolicy()->getInvoice().getDocumentDate());
    view->setSaleOrStoreDate(manager->getInvoicePolicy()->getInvoice().getSaleDate());
    view->setLineDiscount(manager->getInvoicePolicy()->getInvoice().getDiscount());
    view->setLineIssueName(manager->getInvoicePolicy()->getInvoice().getIssueName());
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    view->getLineOrderSymbol()->setText(manager->getInvoicePolicy()->getInvoice().getOrder());
    view->setCheckStoreUpdate(manager->getInvoicePolicy()->getInvoice().getStoreResult());
    manager->setDocumentPositions(manager->getInvoicePolicy()->getInvoice().getDocumentPositions());
    view->getLineDocumentSymbol()->setEnabled(false);
    addGood();
    manager->countGoodsValue(view->getDiscountOrWaybillNo()->text().toDouble());
    setGoodsValue();
    if(totalFromBase==true)
    {
    view->setLineGoodsValueDiscount(manager->getInvoicePolicy()->getInvoice().getTotal());
    totalFromBase=false;
    }
    if (view->exec())
    {
        getDocumentData();
        if(isChangesOccured())
        {
        invoiceService->editInvoice(manager->getInvoicePolicy()->getInvoice());
        this->printDoc();
        }
    }
}

void DocumentPAController::getDocumentData()
{
     Invoice invoice;
     invoice.setDocumentType(symbol);
     invoice.setSymbol(view->getLineDocumentSymbol()->text());
     invoice.setDocumentPlace(view->getLineDocumentPlace()->text());
     invoice.setDocumentDate(view->getDateIssue());
     invoice.setSaleDate(view->getSaleOrStoreDate());
     invoice.setTotal(view->getLineGoodsValueDiscount());
     invoice.setDiscount(view->getDiscountOrWaybillNo()->text().toDouble());
     if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
     invoice.setOrder(view->getLineOrderSymbol()->text());
     invoice.setIssueName(view->getLineIssueName());
     invoice.setStoreResult(view->isStoreUpdating());
     invoice.setDocumentPositions(manager->getDocumentPosition());
     manager->getInvoicePolicy()->setDocumentData(invoice);

}

void DocumentPAController::selectOrderOrFacture()
{
    manager->setTotal(0.0);
    manager->setTotalNet(0.0);
    manager->setTotalWithDiscount(0.0);
    manager->setDiscount(0.0);
    QString docTypeFilter = "ZK";
    SelectOrderController dialog(view,docTypeFilter);
    dialog.showDialog();

    Order order;

    if(dialog.getCancel() !=1)
    {
       order = dialog.addOrder();
       insertOrderData(order); //metoda z controllera
       addGood();
    }
}

void DocumentPAController::insertOrderData(Order order)
{

    view->getLineOrderSymbol()->setText(order.getSymbol());
    view->setLineIssueName(order.getIssueName());
    view->setLineDiscount(order.getDiscount());
    view->setLineDocumentPlace(order.getDocumentPlace());
    manager->setDocumentPositions(order.getDocumentPositions());
    manager->countGoodsValue(view->getDiscountOrWaybillNo()->text().toDouble());
    setGoodsValue();

}

bool DocumentPAController::isChangesOccured() {
    return !(manager->getInvoicePolicy()->getOldInvoice() == manager->getInvoicePolicy()->getInvoice());
}

void DocumentPAController::printDoc()
{
        PrintSaleDocumentController *pc = new PrintSaleDocumentController(view->getLineDocumentSymbol()->text());
        Invoice doc = invoiceService->getInvoice(view->getLineDocumentSymbol()->text());
        pc->print(&doc);
        delete pc;
}

void DocumentPAController::restoreTableState() {
    QByteArray state = tableStateManager->getState("DOCUMENT_PA_TABLE_GOODS");
    view->getGoodsTable()->horizontalHeader()->restoreState(state);
}

void DocumentPAController::saveTableState() {
    QByteArray state = view->getGoodsTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("DOCUMENT_PA_TABLE_GOODS");
    if(state != oldState)
        tableStateManager->saveState("DOCUMENT_PA_TABLE_GOODS", state);
}





