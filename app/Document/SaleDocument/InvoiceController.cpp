#include "InvoiceController.h"

InvoiceController::InvoiceController(QWidget* parent, QString symbol, bool edit) {

    this->symbol = symbol;
    this->edition = edit;
    this->view = new InvoiceView(parent,this);
    this->invoiceService = new InvoiceService();
    this->mopModel = new MOPModel();
    this->manager= new InvoiceManager();
    this->validator = new DocumentValidator(view,symbol);
    fillBox(view->getWayToPay(),mopModel->getMethodsOfPayment());
    changingContractor=false;
    restoreTableState();
}

InvoiceController::~InvoiceController()
{
    saveTableState();
    delete invoiceService;
    delete validator;
    delete manager;
    delete mopModel;
}

void InvoiceController::exec ()
{
    dnc = new DocumentNumeratorController(symbol);
    QString nextSymbol = dnc->getNextSymbol();
    view->getLineDocumentSymbol()->setText(nextSymbol);
    delete dnc;
    dnc = NULL;

    QString documentPlace = smodel->getDefualtDocumentPlace().getName();
    this->view->setLineDocumentPlace(documentPlace);
    this->view->setLineIssueName(ApplicationManager::getInstance()->getLoggedUser().getName());
    if (view->exec())
    {
        getDocumentData();
        invoiceService->addInvoice(manager->getInvoicePolicy()->getInvoice());
        this->printDoc();
        return;
    }
    return;
}

void InvoiceController::exec(QString symbol)
{
    this->edition = true;
    this->totalFromBase=true;
    manager->getInvoicePolicy()->setInvoice(invoiceService->getInvoice(symbol));
    manager->getInvoicePolicy()->setOldInvoice(manager->getInvoicePolicy()->getInvoice());
    manager->setContractor(manager->getInvoicePolicy()->getInvoice().getContractor());
    view->setLineDocumentSymbol(manager->getInvoicePolicy()->getInvoice().getSymbol());
    view->getWayToPay()->setCurrentIndex(view->getWayToPay()->findData(QVariant::fromValue(manager->getInvoicePolicy()->getInvoice().getMethodOfPayment().getId())));
    view->setLineDocumentPlace(manager->getInvoicePolicy()->getInvoice().getDocumentPlace());
    view->setDateIssue(manager->getInvoicePolicy()->getInvoice().getDocumentDate());
    view->setSaleOrStoreDate(manager->getInvoicePolicy()->getInvoice().getSaleDate());
    view->setPaymentDate(manager->getInvoicePolicy()->getInvoice().getPaymentDate());
    view->setLineDiscount(manager->getInvoicePolicy()->getInvoice().getDiscount());
    view->setLineIssueName(manager->getInvoicePolicy()->getInvoice().getIssueName());
    view->setLineReceiveName(manager->getInvoicePolicy()->getInvoice().getReceiveName());
    view->setCheckPaid(manager->getInvoicePolicy()->getInvoice().isPaid());
    view->setCheckStoreUpdate(manager->getInvoicePolicy()->getInvoice().getStoreResult());
    if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
    view->getLineOrderSymbol()->setText(manager->getInvoicePolicy()->getInvoice().getOrder());
    manager->setDocumentPositions(manager->getInvoicePolicy()->getInvoice().getDocumentPositions());
    view->getLineDocumentSymbol()->setEnabled(false);

    addGood();
    addContractor();
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
        return;
        }
     }
}

void InvoiceController::getDocumentData()
{
     Invoice invoice;
     invoice.setDocumentType(symbol);
     invoice.setSymbol(view->getLineDocumentSymbol()->text());
     MethodOfPayment mop;
     mop.setId((view->getWayToPay()->itemData(view->getWayToPay()->currentIndex()).toInt()));
     invoice.setMethodOfPayment(mop);
     invoice.setDocumentPlace(view->getLineDocumentPlace()->text());
     invoice.setDocumentDate(view->getDateIssue());
     invoice.setSaleDate(view->getSaleOrStoreDate());
     invoice.setPaymentDate(view->getPaymentDate()->date());
     invoice.setTotal(view->getLineGoodsValueDiscount());
     invoice.setDiscount(view->getDiscountOrWaybillNo()->text().toDouble());
     if(ApplicationManager::getInstance()->containsModule(ModuleManager::Order))
     invoice.setOrder(view->getLineOrderSymbol()->text());
     invoice.setIssueName(view->getLineIssueName());
     invoice.setReceiveName(view->getLineReceiveName());
     invoice.setPaid(view->isPaid());
     invoice.setStoreResult(view->isStoreUpdating());
     invoice.setDocumentPositions(manager->getDocumentPosition());
     manager->getInvoicePolicy()->setDocumentData(invoice);
}

void InvoiceController::insertOrderData(Order order)
{
    view->getLineOrderSymbol()->setText(order.getSymbol());
    view->setContractorData(order.getContractor());
    view->setLineIssueName(order.getIssueName());
    view->setLineReceiveName(order.getReceiveName());
    view->setLineDiscount(order.getDiscount());
    view->setLineDocumentPlace(order.getDocumentPlace());
    manager->setContractor(order.getContractor());
    manager->setDocumentPositions(order.getDocumentPositions());
    manager->countGoodsValue(view->getDiscountOrWaybillNo()->text().toDouble());
    setGoodsValue();
    addGood();
}

void InvoiceController::updatePaymentDate()
{   view->getPaymentDate()->setDate(QDate::currentDate().addDays(
    mopModel->getMethodOfPayment(view->getWayToPay()->itemData(view->getWayToPay()->currentIndex()).toInt()).getMaturity()));
}

void  InvoiceController:: fillBox(QComboBox *box,QVector<MethodOfPayment> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void InvoiceController::printDoc()
{
        PrintSaleDocumentController *pc = new PrintSaleDocumentController(view->getLineDocumentSymbol()->text());
        Invoice doc = invoiceService->getInvoice(view->getLineDocumentSymbol()->text());
        pc->print(&doc);
        delete pc;
}
/**
  Demo blocker nr 1.
*/
void InvoiceController::selectOrderOrFacture()
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
    }

}

void InvoiceController::changedPaid()
{
 if(view->getPaymentDate()->date()<=view->getDateIssue())
    view->setCheckPaid(true);
 else
    view->setCheckPaid(false);
}

bool InvoiceController::isChangesOccured() {
    return !(manager->getInvoicePolicy()->getOldInvoice() == manager->getInvoicePolicy()->getInvoice());
}

void InvoiceController::restoreTableState() {
    QByteArray state = tableStateManager->getState("INVOICE_TABLE_GOODS");
    view->getGoodsTable()->horizontalHeader()->restoreState(state);
}

void InvoiceController::saveTableState() {
    QByteArray state = view->getGoodsTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("INVOICE_TABLE_GOODS");
    if(state != oldState)
        tableStateManager->saveState("INVOICE_TABLE_GOODS", state);
}


