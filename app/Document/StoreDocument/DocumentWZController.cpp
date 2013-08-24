#include "DocumentWZController.h"

DocumentWZController::DocumentWZController(QWidget* parent,bool edit) {
    this->symbol = "WZ";
    this->view = new DocumentWZView(parent, this);
    this->transportModel= new TransportModel();
    this->edition = edit;
    this->wzService = new DocumentWZService();
    this->manager= new DocumentWZManager();
    this->validator = new DocumentValidator(view,symbol);
    fillBox(view->getComboBox(), transportModel->getMeansOfTransport());
    changingContractor=false;
    restoreTableState();
}

void DocumentWZController::exec()   {

    dnc = new DocumentNumeratorController(symbol);
    QString nextSymbol = dnc->getNextSymbol();
    view->getLineDocumentSymbol()->setText(nextSymbol);
    delete dnc;
    dnc = NULL;

    QString documentPlace = smodel->getDefualtDocumentPlace().getName();
    this->view->setLineDocumentPlace(documentPlace);

    if(ApplicationManager::getInstance()->getLoggedUser() != NULL)
        this->view->setLineIssueName(ApplicationManager::getInstance()->getLoggedUser()->getName()); //TODO dane użytkownika programu!!!!!!!!!!!!!!!!!

    if (view->exec())
    {
        getDocumentData();
        wzService->addDocumentWZ(manager->getDocumentWZPolicy()->getDocumentWZ()); //metoda z managera
        this->printDoc();
        return;
    }
    return;

}

void DocumentWZController::exec(QString symbol)
{
    this->edition = true;
    this->totalFromBase=true;
    if(view != NULL)    {
        manager->getDocumentWZPolicy()->setDocumentWZ(wzService->getDocumentWZ(symbol));
        manager->getDocumentWZPolicy()->setOldDocumentWZ(manager->getDocumentWZPolicy()->getDocumentWZ());
        manager->setContractor(manager->getDocumentWZPolicy()->getDocumentWZ().getContractor());
        view->setLineDocumentSymbol(manager->getDocumentWZPolicy()->getDocumentWZ().getSymbol());
        view->getComboBox()->setCurrentIndex(view->getComboBox()->findData(QVariant::fromValue(manager->getDocumentWZPolicy()->getDocumentWZ().getTransport().getId())));
        view->setLineDocumentPlace(manager->getDocumentWZPolicy()->getDocumentWZ().getDocumentPlace());
        view->setDateIssue(manager->getDocumentWZPolicy()->getDocumentWZ().getDocumentDate());
        view->setCheckStoreUpdate(manager->getDocumentWZPolicy()->getDocumentWZ().getStoreResult());
        view->setSaleOrStoreDate(manager->getDocumentWZPolicy()->getDocumentWZ().getSendDate());
        view->setDateIssue(manager->getDocumentWZPolicy()->getDocumentWZ().getDocumentDate());
        view->setLineIssueName(manager->getDocumentWZPolicy()->getDocumentWZ().getIssueName());
        view->setLineReceiveName(manager->getDocumentWZPolicy()->getDocumentWZ().getReceiveName());
        view->getDiscountOrWaybillNo()->setText(manager->getDocumentWZPolicy()->getDocumentWZ().getWaybillNumber());
        view->getPurchaseOrFactureSymbol()->setText(manager->getDocumentWZPolicy()->getDocumentWZ().getFactureSymbol());
        view->getWayToPay()->setCurrentIndex(view->getWayToPay()->findData(QVariant::fromValue(manager->getDocumentWZPolicy()->getDocumentWZ().getShipping())));
        manager->setDocumentPositions(manager->getDocumentWZPolicy()->getDocumentWZ().getDocumentPositions());

}
    addGood();
    addContractor();
    if(totalFromBase==true)
    {
    view->setLineGoodsValueNet(manager->getDocumentWZPolicy()->getDocumentWZ().getTotal());
    totalFromBase=false;
    }
    if (view->exec())
    {
        getDocumentData();
        if(isChangesOccured())
        {
        wzService->editDocumentWZ(manager->getDocumentWZPolicy()->getDocumentWZ());
        this->printDoc();
        return;
        }
     }
}


void DocumentWZController::getDocumentData()
{

     DocumentWZ document;
     document.setDocumentType(symbol);
     document.setSymbol(view->getLineDocumentSymbol()->text());
     document.setDocumentDate(view->getDateIssue());
     document.setDocumentPlace(view->getLineDocumentPlace()->text());
     document.setSendDate(view->getSaleOrStoreDate());
     SimpleStructure sStruct;
     sStruct.setId(view->getComboBox()->itemData(view->getComboBox()->currentIndex()).toInt());
     document.setTransport(sStruct);
     document.setIssueName(view->getLineIssueName());
     document.setReceiveName(view->getLineReceiveName());
     document.setShipping(view->getWayToPay()->itemData(view->getWayToPay()->currentIndex()).toInt());
     document.setWaybillNumber(view->getDiscountOrWaybillNo()->text());
     document.setStoreResult(view->isStoreUpdating());
     document.setTotal(view->getLineGoodsValueNet());
     document.setFactureSymbol(view->getPurchaseOrFactureSymbol()->text());
     document.setDocumentPositions(manager->getDocumentPosition());
     manager->getDocumentWZPolicy()->setDocumentData(document);

}

void DocumentWZController::selectOrderOrFacture()
{
    QStringList docTypeFilter;
    docTypeFilter << "FMP" << "FV" << "PRO"; // faktura VAT, VAT-MP, PROFORMA
    SelectInvoiceController dialog(view, docTypeFilter);
    dialog.showDialog();

    Document invoice;

    if(dialog.getCancel() !=1)
    {
       invoice = dialog.addInvoice();
       insertInvoiceData(invoice);
    }
}

void DocumentWZController::insertInvoiceData(Document invoice)
{

    view->getPurchaseOrFactureSymbol()->setText(invoice.getSymbol());
    view->setCheckStoreUpdate(!invoice.getStoreResult());
    view->setLineIssueName(invoice.getIssueName());
    view->setContractorData(invoice.getContractor());
    view->setLineReceiveName(invoice.getReceiveName());
    manager->getDocumentWZPolicy()->setContractor(invoice.getContractor());
    manager->setDocumentPositions(invoice.getDocumentPositions());
    manager->countGoodsValue(0.0);
    setGoodsValue();
    addGood();
}


void DocumentWZController::printDoc()
{
    DocumentWZ doc = wzService->getDocumentWZ(view->getLineDocumentSymbol()->text());
    PrintStoreDocumentController *pc = new PrintStoreDocumentController(view->getLineDocumentSymbol()->text());
    pc->print(&doc);
    delete pc;
}

bool DocumentWZController::isChangesOccured()
{
    return !(manager->getDocumentWZPolicy()->getOldDocumentWZ() == manager->getDocumentWZPolicy()->getDocumentWZ());
}


void  DocumentWZController:: fillBox(QComboBox *box,QVector<SimpleStructure> values)
{
    box->addItem("Nie dotyczy", 0);
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}


DocumentWZController::~DocumentWZController()
{
    saveTableState();

    delete wzService;
    delete validator;
    delete manager;
    delete transportModel;

}


void DocumentWZController::restoreTableState() {
    QByteArray state = tableStateManager->getState("DOCUMENT_WZ_TABLE_GOODS");
    view->getGoodsTable()->horizontalHeader()->restoreState(state);
}

void DocumentWZController::saveTableState() {
    QByteArray state = view->getGoodsTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("DOCUMENT_WZ_TABLE_GOODS");
    if(state != oldState)
        tableStateManager->saveState("DOCUMENT_WZ_TABLE_GOODS", state);
}

