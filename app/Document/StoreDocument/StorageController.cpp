#include "StorageController.h"

StorageController::StorageController(QWidget* parent,bool edit,QString symbol) {
    this->symbol = symbol;
    this->view = new StorageView(parent, this);
    this->edition = edit;
    this->stService = new StorageService();
    this->manager= new StorageManager();
    this->validator = new DocumentValidator(view,symbol);
    changingContractor=false;
    restoreTableState();
}

void StorageController::exec()   {

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
        stService->addStoreDocument(manager->getStoragePolicy()->getStoreDocument());
        this->printDoc();
        return;
    }
    return;

}

void StorageController::exec(QString symbol)
{
    this->edition = true;
    this->totalFromBase=true;
    if(view != NULL)    {
        manager->getStoragePolicy()->setStoreDocument(stService->getStoreDocument(symbol));
        manager->getStoragePolicy()->setOldStoreDocument(manager->getStoragePolicy()->getStoreDocument());
        view->setLineDocumentSymbol(manager->getStoragePolicy()->getStoreDocument().getSymbol());
        view->setLineDocumentPlace(manager->getStoragePolicy()->getStoreDocument().getDocumentPlace());
        view->setDateIssue(manager->getStoragePolicy()->getStoreDocument().getDocumentDate());
        view->setCheckStoreUpdate(manager->getStoragePolicy()->getStoreDocument().getStoreResult());
        view->setDateIssue(manager->getStoragePolicy()->getStoreDocument().getDocumentDate());
        view->setLineIssueName(manager->getStoragePolicy()->getStoreDocument().getIssueName());
        manager->setDocumentPositions(manager->getStoragePolicy()->getStoreDocument().getDocumentPositions());
}
    addGood();

    if(totalFromBase==true)
    {
        view->setLineGoodsValueNet(manager->getStoragePolicy()->getStoreDocument().getTotal());
        totalFromBase=false;
    }
    if (view->exec())
    {
        getDocumentData();
        if(isChangesOccured())
        {
        stService->editStoreDocument(manager->getStoragePolicy()->getStoreDocument());
        this->printDoc();
        return;
        }
     }
}


void StorageController::getDocumentData()
{

     StoreDocument document;
     document.setDocumentType(symbol);
     document.setSymbol(view->getLineDocumentSymbol()->text());
     document.setDocumentDate(view->getDateIssue());
     document.setDocumentPlace(view->getLineDocumentPlace()->text());
     document.setIssueName(view->getLineIssueName());
     document.setStoreResult(view->isStoreUpdating());
     document.setTotal(view->getLineGoodsValueNet());
     document.setDocumentPositions(manager->getDocumentPosition());
     manager->getStoragePolicy()->setDocumentData(document);
}


void StorageController::printDoc()
{
      StoreDocument doc = stService->getStoreDocument(view->getLineDocumentSymbol()->text());
      PrintStoreDocumentController *pc = new PrintStoreDocumentController(view->getLineDocumentSymbol()->text());
      pc->print(&doc);
      delete pc;
}

bool StorageController::isChangesOccured() {
    return !(manager->getStoragePolicy()->getStoreDocument() == manager->getStoragePolicy()->getOldStoreDocument());
}


void  StorageController:: fillBox(QComboBox *box,QVector<SimpleStructure> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}
void StorageController::saveTableState() {
    QByteArray state = view->getGoodsTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("STORAGE_DOCUMENT_TABLE_GOODS");
    if(state != oldState)
        tableStateManager->saveState("STORAGE_DOCUMENT_TABLE_GOODS", state);
}

void StorageController::restoreTableState() {
    QByteArray state = tableStateManager->getState("STORAGE_DOCUMENT_TABLE_GOODS");
    view->getGoodsTable()->horizontalHeader()->restoreState(state);
}

StorageController::~StorageController()
{
    saveTableState();
    delete stService;
    delete validator;
    delete manager;

}
