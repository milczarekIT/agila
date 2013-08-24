#include "DocumentRRController.h"

DocumentRRController::DocumentRRController(QWidget* parent, QString symbol, bool edit) {
    this->symbol = symbol;
    this->edition = edit;
    this->view = new DocumentRRView(parent,this);
    this->purchaseInvoiceService = new PurchaseInvoiceService();
    this->validator = new DocumentValidator(view,symbol);
    this->manager = new PurchaseManager();
    this->mopModel = new MOPModel();
    fillBox(view->getWayToPay(),mopModel->getMethodsOfPayment());
    changingContractor=false;
    restoreTableState();
}

DocumentRRController::~DocumentRRController()
{
    saveTableState();
    delete purchaseInvoiceService;
    delete validator;
    delete manager;
    delete mopModel;
}

void DocumentRRController::exec ()
{
    dnc = new DocumentNumeratorController(symbol);
    QString nextSymbol = dnc->getNextSymbol();
    view->getLineDocumentSymbol()->setText(nextSymbol);
    delete dnc;
    dnc = NULL;

    QString documentPlace = smodel->getDefualtDocumentPlace().getName();
    this->view->setLineDocumentPlace(documentPlace);
    if(ApplicationManager::getInstance()->getLoggedUser() != NULL)
        this->view->setLineIssueName(ApplicationManager::getInstance()->getLoggedUser()->getName());

    if (view->exec())
    {
        getDocumentData();
        purchaseInvoiceService->addPurchaseInvoice(manager->getPurchasePolicy()->getPurchaseInvoice());
        this->printDoc();
        return;
    }
    return;
}

void DocumentRRController::exec(QString symbol)
{
    this->edition = true;
    this->totalFromBase = true;
    manager->getPurchasePolicy()->setPurchaseInvoice(purchaseInvoiceService->getPurchaseInvoice(symbol));
    manager->getPurchasePolicy()->setPurchaseInvoiceOld(manager->getPurchasePolicy()->getPurchaseInvoice());
    manager->setContractor(manager->getPurchasePolicy()->getPurchaseInvoice().getContractor());
    view->setLineDocumentSymbol(manager->getPurchasePolicy()->getPurchaseInvoice().getSymbol());
    view->getWayToPay()->setCurrentIndex(view->getWayToPay()->findData(QVariant::fromValue(manager->getPurchasePolicy()->getPurchaseInvoice().getMethodOfPayment().getId())));
    view->setLineDocumentPlace(manager->getPurchasePolicy()->getPurchaseInvoice().getDocumentPlace());
    view->setDateIssue(manager->getPurchasePolicy()->getPurchaseInvoice().getDocumentDate());
    view->setSaleOrStoreDate(manager->getPurchasePolicy()->getPurchaseInvoice().getSaleDate());
    view->setPaymentDate(manager->getPurchasePolicy()->getPurchaseInvoice().getPaymentDate());
    view->setLineDiscount(manager->getPurchasePolicy()->getPurchaseInvoice().getDiscount());
    view->setLineIssueName(manager->getPurchasePolicy()->getPurchaseInvoice().getIssueName());
    view->setLineReceiveName(manager->getPurchasePolicy()->getPurchaseInvoice().getReceiveName());
    view->setCheckPaid(manager->getPurchasePolicy()->getPurchaseInvoice().isPaid());
    view->getLineOrderSymbol()->setText(manager->getPurchasePolicy()->getPurchaseInvoice().getOrder());
    view->setCheckStoreUpdate(manager->getPurchasePolicy()->getPurchaseInvoice().getStoreResult());
    manager->setDocumentPositions(manager->getPurchasePolicy()->getPurchaseInvoice().getDocumentPositions());
    addGood();
    addContractor();
    if(totalFromBase==true)
    {
        view->setLineGoodsValueDiscount(manager->getPurchasePolicy()->getPurchaseInvoice().getTotal());
        totalFromBase=false;
    }
    if (view->exec())
    {
        getDocumentData();
        if(isChangesOccured())
        {
            purchaseInvoiceService->editPurchaseInvoice(manager->getPurchasePolicy()->getPurchaseInvoice());
            this->printDoc();
        }
    }

}

void DocumentRRController::getDocumentData()
{
    PurchaseInvoice purchaseInvoice;
    purchaseInvoice.setDocumentType(symbol);//ustawiam rodzaj dokumentu PRO FMP documentRR PI
    purchaseInvoice.setSymbol(view->getLineDocumentSymbol()->text());
    MethodOfPayment mop;
    mop.setId((view->getWayToPay()->itemData(view->getWayToPay()->currentIndex()).toInt()));
    purchaseInvoice.setMethodOfPayment(mop);
    purchaseInvoice.setDocumentPlace(view->getLineDocumentPlace()->text());
    purchaseInvoice.setDocumentDate(view->getDateIssue());
    purchaseInvoice.setSaleDate(view->getSaleOrStoreDate());
    purchaseInvoice.setPaymentDate(view->getPaymentDate()->date());
    purchaseInvoice.setTotal(view->getLineGoodsValueDiscount());
    purchaseInvoice.setDiscount(view->getDiscountOrWaybillNo()->text().toDouble());
    purchaseInvoice.setIssueName(view->getLineIssueName());
    purchaseInvoice.setReceiveName(view->getLineReceiveName());
    purchaseInvoice.setOrder(view->getLineOrderSymbol()->text());
    purchaseInvoice.setPurchaseDocument();
    purchaseInvoice.setPaid(view->isPaid());
    purchaseInvoice.setStoreResult(view->isStoreUpdating());
    purchaseInvoice.setDocumentPositions(manager->getDocumentPosition());
    manager->getPurchasePolicy()->setPurchaseInvoiceData(purchaseInvoice);
}

void DocumentRRController::restoreTableState() {
    QByteArray state = tableStateManager->getState("DOCUMENT_RR_TABLE_GOODS");
    view->getGoodsTable()->horizontalHeader()->restoreState(state);
}

void DocumentRRController::saveTableState() {
    QByteArray state = view->getGoodsTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("DOCUMENT_RR_TABLE_GOODS");
    if(state != oldState)
        tableStateManager->saveState("DOCUMENT_RR_TABLE_GOODS", state);
}

