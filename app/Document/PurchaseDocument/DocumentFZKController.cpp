#include "DocumentFZKController.h"

DocumentFZKController::DocumentFZKController(QWidget* parent,bool edit)
{
    this->edition = edit;
    this->symbol = "FZK";
    this->view = new DocumentFZKView(parent,this);
    this->invoiceService = new InvoiceService();
    this->purService = new PurchaseInvoiceService();
    this->fzkService = new DocumentFZKService();
    this->smodel = new SettingsModel();
    this->mopModel = new MOPModel();
    this->validator = new DocumentValidator(view,symbol);
    this->managerFK = new DocumentFZKManager();
    this->tableStateManager = new TableStateManager();
    fillBox(view->getBoxWayToPay(),mopModel->getMethodsOfPayment());
    first=false;
    restoreTableState();

}

DocumentFZKController::~DocumentFZKController()
{
    delete fzkService;
    saveTableState();
}

void DocumentFZKController::exec ()
{

    dnc = new DocumentNumeratorController("FZK");
    QString nextSymbol = dnc->getNextSymbol();
    view->getLineDocumentSymbol()->setText(nextSymbol);
    delete dnc;
    dnc = NULL;

    QString documentPlace = smodel->getDefualtDocumentPlace().getName();
    this->view->setLineDocumentPlace(documentPlace);
    this->view->setLineIssueName(ApplicationManager::getInstance()->getLoggedUser().getName());

    if (view->exec())
    {   getDocumentData();
        fzkService->addDocumentFZK(managerFK->getFZKPolicy()->getFZK());
        this->printDoc();
        return;
    }
    return;
}

void DocumentFZKController::exec(QString symbol)
{
    this->first = true;
    this->totalFromBase=true;

    managerFK->getFZKPolicy()->setFZK(fzkService->getDocumentFZK(symbol));
    managerFK->getFZKPolicy()->setPurchaseInvoice(managerFK->getFZKPolicy()->getFZK().getInvoice());
    managerFK->getFZKPolicy()->setFZKOld(managerFK->getFZKPolicy()->getFZK());
    view->setLineDocumentSymbol(managerFK->getFZKPolicy()->getFZK().getSymbol());
    view->setContractorDataOld(managerFK->getFZKPolicy()->getFZK().getInvoice().getContractor());
    managerFK->getFZKPolicy()->setContractor(managerFK->getFZKPolicy()->getFZK().getContractor());
    view->setContractorDataNew(managerFK->getFZKPolicy()->getContractor());
    view->setDateEditInvoiceDate(managerFK->getFZKPolicy()->getFZK().getInvoice().getDocumentDate());
    view->setRealatedTo(managerFK->getFZKPolicy()->getFZK().getInvoice().getSymbol());
    view->getBoxWayToPay()->setCurrentIndex(view->getBoxWayToPay()->findData(QVariant::fromValue(managerFK->getFZKPolicy()->getFZK().getMethodOfPayment().getId())));
    view->setLineDocumentPlace(managerFK->getFZKPolicy()->getFZK().getDocumentPlace());
    view->setDateIssue(managerFK->getFZKPolicy()->getFZK().getDocumentDate());
    view->setSaleDate(managerFK->getFZKPolicy()->getFZK().getSaleDate());
    view->setPurchaseDocSymbol(managerFK->getFZKPolicy()->getFZK().getInvoice().getPurchaseDocument());
    view->setPaymentDate(managerFK->getFZKPolicy()->getFZK().getPaymentDate());
    view->setLineDiscountNew(managerFK->getFZKPolicy()->getFZK().getDiscount());
    view->setLineDiscount(managerFK->getFZKPolicy()->getFZK().getInvoice().getDiscount());
    view->setLineIssueName(managerFK->getFZKPolicy()->getFZK().getIssueName());
    view->setLineReceiveName(managerFK->getFZKPolicy()->getFZK().getReceiveName());
    view->setCheckPaid(managerFK->getFZKPolicy()->getFZK().isPaid());
    view->setCheckStoreUpdate(managerFK->getFZKPolicy()->getFZK().getStoreResult());
    managerFK->setDocumentPositions(managerFK->getFZKPolicy()->getFZK().getDocumentPositions());
    managerFK->setDocumentPositionsOld(managerFK->getFZKPolicy()->getFZK().getInvoice().getDocumentPositions());
    managerFK->countGoodsValue(view->getLineDiscount()->text().toDouble(),first);
    setGoodsValue();
    addGood();
    if(totalFromBase==true)
    {
        view->setLineToPayAfterCorrection(managerFK->getFZKPolicy()->getFZK().getTotal());
        totalFromBase=false;
    }
    if (view->exec())
    {
        getDocumentData();
        if(isChangesOccured())
        {
            fkService->editDocumentFK(managerFK->getFZKPolicy()->getFZK());
            this->printDoc();
        }
        return;
     }
    return;
}

void DocumentFZKController::getDocumentData()
{
    DocumentFZK fzk;
    fzk.setSymbol(view->getLineDocumentSymbol()->text());

    MethodOfPayment mop;
    mop.setId((view->getBoxWayToPay()->itemData(view->getBoxWayToPay()->currentIndex()).toInt()));
    fzk.setMethodOfPayment(mop);
    fzk.setDocumentPlace(view->getLineDocumentPlace()->text());
    fzk.setDocumentDate(view->getDateIssue());
    fzk.setSaleDate(view->getSaleDate());
    fzk.setPaymentDate(view->getPaymentDate());
    fzk.setTotal(view->getLineToPayAfterCorrection());
    fzk.setDiscount(view->getLineDiscountNew()->text().toDouble());
    fzk.setReceiveName(view->getLineReceiveName());
    fzk.setOrder();
    fzk.setPurchaseDocument(view->getPurchaseDocSymbol()->text());
    fzk.setIssueName(view->getLineIssueName());
    fzk.setPaid(view->isPaid());
    fzk.setStoreResult(view->isStoreUpdating());
    if (managerFK->getDocumentPositionNew().empty()==1)
      fzk.setDocumentPositions(managerFK->getDocumentPositionOld());
     else
      fzk.setDocumentPositions(managerFK->getDocumentPositionNew());
   managerFK->getFZKPolicy()->setFactureData(fzk);
}

void DocumentFZKController::selectInvoice()
{
    setFirst(true);
    SelectInvoiceController dialog(view,"PURCHASE");
    dialog.setDocumentNotTypeFilter("RR");
    dialog.showDialog();

    Document invoice;

    if(dialog.getCancel() !=1)
    {
       invoice = dialog.addInvoice();
       insertInvoiceData(invoice);
    }
}

void DocumentFZKController::insertInvoiceData(Document invoice)
{
    managerFK->getFZKPolicy()->setPurchaseInvoice(purService->getPurchaseInvoice(invoice.getSymbol()));
    view->setRealatedTo(invoice.getSymbol());
    view->setDateEditInvoiceDate(invoice.getDocumentDate());
    view->setContractorDataOld(invoice.getContractor());
    view->setContractorDataNew(invoice.getContractor());
    view->getBoxWayToPay()->setCurrentIndex(view->getBoxWayToPay()->findData(QVariant::fromValue(managerFK->getFZKPolicy()->getPurchaseInvoice().getMethodOfPayment().getId())));
    view->setSaleDate(managerFK->getFZKPolicy()->getPurchaseInvoice().getSaleDate());
    view->setPaymentDate(managerFK->getFZKPolicy()->getPurchaseInvoice().getPaymentDate());
    view->setCheckPaid(managerFK->getFZKPolicy()->getPurchaseInvoice().isPaid());
    view->setCheckStoreUpdate(managerFK->getFZKPolicy()->getPurchaseInvoice().getStoreResult());
    view->setLineIssueName(invoice.getIssueName());
    view->setLineReceiveName(invoice.getReceiveName());
    view->setPurchaseDocSymbol(managerFK->getFZKPolicy()->getFZK().getInvoice().getPurchaseDocument());
    view->setLineDiscount(managerFK->getFZKPolicy()->getPurchaseInvoice().getDiscount());
    view->setLineDiscountNew(managerFK->getFZKPolicy()->getPurchaseInvoice().getDiscount());
    managerFK->getFZKPolicy()->setContractor(invoice.getContractor());
    managerFK->setDocumentPositionsOld(managerFK->getFZKPolicy()->getPurchaseInvoice().getDocumentPositions());
    managerFK->setDocumentPositions(managerFK->getFZKPolicy()->getPurchaseInvoice().getDocumentPositions());
    managerFK->countGoodsValue(view->getLineDiscount()->text().toDouble(),first);
    setGoodsValue();
    addGood();
}

void DocumentFZKController::printDoc() {
    PrintPurchaseDocumentController *pc = new PrintPurchaseDocumentController(view->getLineDocumentSymbol()->text());
    DocumentFZK doc = fzkService->getDocumentFZK(view->getLineDocumentSymbol()->text());
    pc->print(&doc);
    delete pc;
}


void DocumentFZKController::restoreTableState() {
    QByteArray state = tableStateManager->getState("DOCUMENT_FZK_TABLE_GOODS");
    view->getGoodsTableNew()->horizontalHeader()->restoreState(state);
    view->getGoodsTableOld()->horizontalHeader()->restoreState(state);
}

void DocumentFZKController::saveTableState() {
    QByteArray state = view->getGoodsTableNew()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("DOCUMENT_FZK_TABLE_GOODS");
    if(state != oldState)
        tableStateManager->saveState("DOCUMENT_FZK_TABLE_GOODS", state);
}
