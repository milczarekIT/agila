#include "SelectContractorController.h"


SelectContractorController::SelectContractorController(QWidget* parent) {

    this->view = new SelectContractorView(parent, this);
    conService= new ContractorService();
    contractorTVModel = new ContractorTVModel();
    initContractorsTable();

    selectColumnsDialog = new SelectVisibleColumns(view->getContractorsTable());
    connect(selectColumnsDialog, SIGNAL(selectedColumnsChanged(QList<int>)), this, SLOT(changeColumnVisiblity(QList<int>)));

    restoreTableState();
}
SelectContractorController::~SelectContractorController()
{
    saveTableState();
    delete conService;
    delete contractorTVModel;
}

void SelectContractorController::showDialog()   {
    this->view->exec();
}

int SelectContractorController::getCancel(){
    return this->cancel;
}

SelectContractorView *SelectContractorController::getView(){
    return this->view;
}

void SelectContractorController::initContractorsTable(){


    contractorTVModel->getContractors();
    view->getContractorsTable()->setContractorModel(contractorTVModel);
}

Contractor SelectContractorController::addContractor() {

        Contractor c;
        c=conService->getContractor(view->getContractorsTable()->getId());
        return c;
    }

void SelectContractorController::setCancel ()
{
    cancel=1;
}

void SelectContractorController::setContractorTypeFilter(int contractorType)
{
    contractorTVModel->setConTypeFilter(contractorType);
    contractorTVModel->getContractors();
}

void SelectContractorController::addNewContractor() {

    ContractorDialogController *dialog= new ContractorDialogController(this->view);
    dialog->exec();
        contractorTVModel->getContractors();

    }

void SelectContractorController::dialogContractorEdit(){
    editContractor(view->getContractorsTable()->getId());
}

void SelectContractorController::editContractor(int id)
{
    ContractorDialogController *dialog =new ContractorDialogController(view);
    dialog->exec(id);
        //update widoku
        contractorTVModel->getContractors();
}

void SelectContractorController::dialogSelectColumns() {
    selectColumnsDialog->exec();
}

void SelectContractorController::changeColumnVisiblity(QList<int> visibleColumns)
{
    for(int column = 0; column < view->getContractorsTable()->model()->columnCount(); column++) {
        if(visibleColumns.contains(column))
        {
            view->getContractorsTable()->setColumnHidden(column, false);
        }
        else
        {
            view->getContractorsTable()->setColumnHidden(column, true);
        }
    }
}

void SelectContractorController::restoreTableState() {
    tableStateManager = new TableStateManager();

    QByteArray state = tableStateManager->getState("SELECT_WINDOW_CONTRACTOR");
    view->getContractorsTable()->horizontalHeader()->restoreState(state);
    delete tableStateManager;

    view->getContractorsTable()->hideIdColumn(); // ukrywa id
    view->getContractorsTable()->horizontalHeader()->setSortIndicatorShown(true); // pokazuje sortindicator

    int columnAtTable = view->getContractorsTable()->horizontalHeader()->sortIndicatorSection();
    contractorTVModel->sort(columnAtTable, view->getContractorsTable()->horizontalHeader()->sortIndicatorOrder());
    contractorTVModel->getContractors();
}

void SelectContractorController::saveTableState() {
    tableStateManager = new TableStateManager();

    QByteArray state = view->getContractorsTable()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("SELECT_WINDOW_CONTRACTOR");
    if(state != oldState)
        tableStateManager->saveState("SELECT_WINDOW_CONTRACTOR", state);

    delete tableStateManager;
}

void SelectContractorController::setContractorNameFilter(QString text)
{
    contractorTVModel->setNameFilter(text);
    contractorTVModel->getContractors();
}

void SelectContractorController::setContractorSymbolFilter(QString text)
{
    contractorTVModel->setSymbolFilter(text);
    contractorTVModel->getContractors();
}

void SelectContractorController::setContractorNipFilter(QString text)
{
    contractorTVModel->setNipFilter(text);
    contractorTVModel->getContractors();
}
