#include "MainTabContractorsItemController.h"

MainTabContractorsItemController::MainTabContractorsItemController()
{
    view = new MainTabContractorsItem(this);
    contractorTVModel = new ContractorTVModel();
    contractorService = new ContractorService();
    initModel();
    initComboBox();

    initSelectingColumnVisibility();
    restoreTableState();
}

MainTabContractorsItemController::~MainTabContractorsItemController()
{
    saveTableState();
    delete contractorTVModel;
    delete contractorService;
}

MainTabItem *MainTabContractorsItemController::getView()
{
    return view;
}

void MainTabContractorsItemController::dialogContractorAdd()
{
    ContractorDialogController *dialog = new ContractorDialogController(this);
    connect(dialog->getView(),SIGNAL(settingsChangedSignal(QString)),this,SLOT(settingsChanged(QString)));

    if (dialog->exec())
        contractorTVModel->getContractors();

    delete dialog;
}


void MainTabContractorsItemController::dialogContractorEdit()
{
    if(view->getTableView()->getId() > 0)
    {
        ContractorDialogController dialog(this);
        if (dialog.exec(view->getTableView()->getId()))
            contractorTVModel->getContractors();
    }
    else
    {
        MessageBox *messageBox = new MessageBox();
        messageBox->createInfoBox("Zaznacz kontrahenta do edycji");
        delete messageBox;
    }
}

void MainTabContractorsItemController::removeContractor ()
{ 
    MessageBox * msgBox = new MessageBox();
    if(view->getTableView()->getId()==-1)
        msgBox->createInfoBox("Zaznacz kontrahenta do usunięcia");
    else
    {
        if(msgBox->createQuestionBox("Usuwanie kontrahenta "+view->getTableView()->getSymbol())==MessageBox::YES)
        {
         contractorService->removeContractor(view->getTableView()->getId());
         contractorTVModel->getContractors();
        }
    }
}

void MainTabContractorsItemController::setConNameFilter(QString filter)
{
     contractorTVModel->setNameFilter(filter);
     contractorTVModel->getContractors();
}

void MainTabContractorsItemController::setConNipFilter(QString filter)
{
     contractorTVModel->setNipFilter(filter);
     contractorTVModel->getContractors();
}

void MainTabContractorsItemController::setConSymbolFilter(QString filter)
{
     contractorTVModel->setSymbolFilter(filter);
     contractorTVModel->getContractors();
}

void MainTabContractorsItemController::initComboBox()
{
    ContractorGroupModel *contractorGroupModel = new ContractorGroupModel();
    QVector<ContractorGroup> cgroups = contractorGroupModel->getContractorGroups();
    view->getConGroup()->addItem("Wszyscy", QVariant(-1));
    view->getConGroup()->addItem("BRAK", QVariant(0));
    fillBox(view->getConGroup(), cgroups);
    view->getConGroup()->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    connect(view->getConGroup(), SIGNAL(currentIndexChanged(int)),this, SLOT(setConGroupFilter(int)));
    delete contractorGroupModel;

    view->getContractorType()->addItem("Wszyscy", Contractor::BUYER | Contractor::SUPPLIER);
    view->getContractorType()->addItem("Nabywcy", Contractor::BUYER);
    view->getContractorType()->addItem("Dostawcy", Contractor::SUPPLIER);
    view->getContractorType()->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    connect(view->getContractorType(), SIGNAL(currentIndexChanged(int)), this, SLOT(setConTypeFilter(int)));
}

void  MainTabContractorsItemController::fillBox(QComboBox *box,QVector<ContractorGroup> values)
{
    for(int i = 0; i < values.size(); i++)
        box->addItem(values[i].getName(), QVariant::fromValue(values[i].getId()));
}

void MainTabContractorsItemController::setConGroupFilter(int index)
{
    int conGroupId = view->getConGroup()->itemData(index).toInt();

    contractorTVModel->setConGroupFilter(conGroupId);
    contractorTVModel->getContractors();
}

void MainTabContractorsItemController::setConTypeFilter(int index)
{
    int type = view->getContractorType()->itemData(index).toInt();

    contractorTVModel->setConTypeFilter(type);
    contractorTVModel->getContractors();
}

void MainTabContractorsItemController::initModel()
{
    contractorTVModel->getContractors();
    view->getTableView()->setContractorModel(contractorTVModel);
}

void MainTabContractorsItemController::restoreTableState() {
    tableStateManager = new TableStateManager();

    QByteArray state = tableStateManager->getState("MAIN_TAB_CONTRACTOR");
    view->getTableView()->horizontalHeader()->restoreState(state);

    view->getTableView()->hideIdColumn(); // ukrywa id
    view->getTableView()->horizontalHeader()->setSortIndicatorShown(true); // pokazuje sortindicator

    int columnAtTable = view->getTableView()->horizontalHeader()->sortIndicatorSection();
    contractorTVModel->sort(columnAtTable, view->getTableView()->horizontalHeader()->sortIndicatorOrder());
    contractorTVModel->getContractors();

    delete tableStateManager;
}

void MainTabContractorsItemController::saveTableState() {
    tableStateManager = new TableStateManager();

    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("MAIN_TAB_CONTRACTOR");
    if(state != oldState)
        tableStateManager->saveState("MAIN_TAB_CONTRACTOR", state);

    delete tableStateManager;
}

void MainTabContractorsItemController::refreshTable()
{
    contractorTVModel->getContractors();
}

void MainTabContractorsItemController::dialogSelectColumns() {
    selectColumnsDialog->exec();
}

void MainTabContractorsItemController::initSelectingColumnVisibility()
{
    selectColumnsDialog = new SelectVisibleColumns(view->getTableView(), this);
    connect(selectColumnsDialog, SIGNAL(selectedColumnsChanged(QList<int>)), this, SLOT(changeColumnVisiblity(QList<int>)));
}

void MainTabContractorsItemController::changeColumnVisiblity(QList<int> visibleColumns)
{
    for(int column = 0; column < view->getTableView()->model()->columnCount(); column++) {
        if(visibleColumns.contains(column))
            view->getTableView()->setColumnHidden(column, false);
        else
            view->getTableView()->setColumnHidden(column, true);
    }
}

void MainTabContractorsItemController::settingsChanged(const QString element)
{
    emit this->settingsChangedSignal(element);
}

ModuleManager::Module MainTabContractorsItemController::module()
{
    return ModuleManager::Contractors;
}
