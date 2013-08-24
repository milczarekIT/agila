#include "DocumentPZController.h"


DocumentPZController::DocumentPZController(QWidget* parent,bool edit) {
    this->symbol = "PZ";
    this->view = new DocumentPZView(parent, this);
    this->transportModel= new TransportModel();
    this->edition = edit;
    this->pzService = new DocumentPZService();
    this->manager= new DocumentPZManager();
    this->validator = new DocumentValidator(view,symbol);
    fillBox(view->getComboBox(), transportModel->getMeansOfTransport());
    changingContractor=false;
    restoreTableState();
}

void DocumentPZController::exec()   {

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
        pzService->addDocumentPZ(manager->getDocumentPZPolicy()->getDocumentPZ());
        this->printDoc();
        return;
    }
    return;

}

void DocumentPZController::exec(QString symbol)
{
    this->edition = true;
    this->totalFromBase=true;
    if(view != NULL)    {
        manager->getDocumentPZPolicy()->setDocumentPZ(pzService->getDocumentPZ(symbol));
        manager->getDocumentPZPolicy()->setOldDocumentPZ(manager->getDocumentPZPolicy()->getDocumentPZ());
        manager->setContractor(manager->getDocumentPZPolicy()->getDocumentPZ().getContractor());
        view->setLineDocumentSymbol(manager->getDocumentPZPolicy()->getDocumentPZ().getSymbol());
        view->getComboBox()->setCurrentIndex(view->getComboBox()->findData(QVariant::fromValue(manager->getDocumentPZPolicy()->getDocumentPZ().getTransport().getId())));
        view->setLineDocumentPlace(manager->getDocumentPZPolicy()->getDocumentPZ().getDocumentPlace());
        view->setDateIssue(manager->getDocumentPZPolicy()->getDocumentPZ().getDocumentDate());
        view->setCheckStoreUpdate(manager->getDocumentPZPolicy()->getDocumentPZ().getStoreResult());
        view->setSaleOrStoreDate(manager->getDocumentPZPolicy()->getDocumentPZ().getStoreDate());
        view->setDateIssue(manager->getDocumentPZPolicy()->getDocumentPZ().getDocumentDate());
        view->setLineIssueName(manager->getDocumentPZPolicy()->getDocumentPZ().getIssueName());
        view->setLineReceiveName(manager->getDocumentPZPolicy()->getDocumentPZ().getReceiveName());
        manager->setDocumentPositions(manager->getDocumentPZPolicy()->getDocumentPZ().getDocumentPositions());

}
    addGood();
    addContractor();
    if(totalFromBase==true)
    {
    view->setLineGoodsValueNet(manager->getDocumentPZPolicy()->getDocumentPZ().getTotal());
    totalFromBase=false;
    }
    if (view->exec())
    {

        getDocumentData();
        if(isChangesOccured())
        {
        pzService->editDocumentPZ(manager->getDocumentPZPolicy()->getDocumentPZ());
        this->printDoc();
        return;
        }
     }
}


void DocumentPZController::getDocumentData()
{

     DocumentPZ document;
     document.setDocumentType(symbol);
     document.setSymbol(view->getLineDocumentSymbol()->text());
     document.setDocumentDate(view->getDateIssue());
     document.setDocumentPlace(view->getLineDocumentPlace()->text());
     document.setStoreDate(view->getSaleOrStoreDate());
     SimpleStructure sStruct;
     sStruct.setId(view->getComboBox()->itemData(view->getComboBox()->currentIndex()).toInt());
     document.setTransport(sStruct);
     document.setIssueName(view->getLineIssueName());
     document.setReceiveName(view->getLineReceiveName());
     document.setStoreResult(view->isStoreUpdating());
     document.setTotal(view->getLineGoodsValueNet());
     document.setDocumentPositions(manager->getDocumentPosition());
     manager->getDocumentPZPolicy()->setDocumentData(document);
}


void DocumentPZController::printDoc()
{
     DocumentPZ doc = pzService->getDocumentPZ(view->getLineDocumentSymbol()->text());
     PrintStoreDocumentController *pc = new PrintStoreDocumentController(view->getLineDocumentSymbol()->text());
     pc->print(&doc);
     delete pc;
}

bool DocumentPZController::isChangesOccured() {
    return !(manager->getDocumentPZPolicy()->getDocumentPZ() == manager->getDocumentPZPolicy()->getOldDocumentPZ());
}


void  DocumentPZController:: fillBox(QComboBox *box,QVector<SimpleStructure> values)
{
    box->addItem("Nie dotyczy", 0);
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}



void DocumentPZController::saveTableState() {
    QByteArray state = view->getGoodsTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("DOCUMENT_PZ_TABLE_GOODS");
    if(state != oldState)
        tableStateManager->saveState("DOCUMENT_PZ_TABLE_GOODS", state);
}

void DocumentPZController::restoreTableState() {
    QByteArray state = tableStateManager->getState("DOCUMENT_PZ_TABLE_GOODS");
    view->getGoodsTable()->horizontalHeader()->restoreState(state);
}



DocumentPZController::~DocumentPZController()
{
    saveTableState();
    delete pzService;
    delete validator;
    delete manager;
    delete transportModel;
}
