#include "PurchaseInvoiceController.h"

PurchaseInvoiceController::PurchaseInvoiceController(QWidget* parent, QString symbol, bool edit) {

    this->symbol = symbol;
    this->edition = edit;
    this->view = new PurchaseInvoiceView(parent,this);
    this->purchaseInvoiceService = new PurchaseInvoiceService();
    this->manager = new PurchaseManager();
    this->validator = new DocumentValidator(view,symbol);
    this->mopModel = new MOPModel();
    fillBox(view->getWayToPay(),mopModel->getMethodsOfPayment());
    changingContractor=false;
    restoreTableState();
}

PurchaseInvoiceController::~PurchaseInvoiceController()
{
    saveTableState();
    delete purchaseInvoiceService;
    delete validator;
    delete manager;
    delete mopModel;
}

void PurchaseInvoiceController::exec ()
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
        purchaseInvoiceService->addPurchaseInvoice(manager->getPurchasePolicy()->getPurchaseInvoice());
        this->printDoc();
        return;
    }
    return;
}

void PurchaseInvoiceController::exec(QString symbol)
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
    view->getLineOrderSymbol()->setText(manager->getPurchasePolicy()->getPurchaseInvoice().getOrder());
    view->getPurchaseOrFactureSymbol()->setText(manager->getPurchasePolicy()->getPurchaseInvoice().getPurchaseDocument());
    view->setCheckPaid(manager->getPurchasePolicy()->getPurchaseInvoice().isPaid());
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

void PurchaseInvoiceController::getDocumentData()
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
    purchaseInvoice.setPurchaseDocument(view->getPurchaseOrFactureSymbol()->text());
    purchaseInvoice.setPaid(view->isPaid());
    purchaseInvoice.setStoreResult(view->isStoreUpdating());
    purchaseInvoice.setDocumentPositions(manager->getDocumentPosition());
    manager->getPurchasePolicy()->setPurchaseInvoiceData(purchaseInvoice);

}

void PurchaseInvoiceController::selectOrderOrFacture()
{
    manager->setTotal(0.0);
    manager->setTotalNet(0.0);
    manager->setTotalWithDiscount(0.0);
    manager->setDiscount(0.0);
    QString docTypeFilter = "ZD";
    SelectOrderController dialog(view,docTypeFilter);
    dialog.showDialog();

    Order order;

    if(dialog.getCancel() !=1)
    {
       order = dialog.addOrder();
       insertOrderData(order); //metoda z controllera
    }
}

void PurchaseInvoiceController::insertOrderData(Order order)
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

void PurchaseInvoiceController::restoreTableState() {
    QByteArray state = tableStateManager->getState("PURCHASE_INVOICE_TABLE_GOODS");
    view->getGoodsTable()->horizontalHeader()->restoreState(state);
}

void PurchaseInvoiceController::saveTableState() {
    QByteArray state = view->getGoodsTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("PURCHASE_INVOICE_TABLE_GOODS");
    if(state != oldState)
        tableStateManager->saveState("PURCHASE_INVOICE_TABLE_GOODS", state);
}
