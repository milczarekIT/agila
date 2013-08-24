#include "TopContractorsDialogController.h"

TopContractorsDialogController::TopContractorsDialogController(QWidget *parent)
{
    view = new TopContractorsDialogView(parent, this);

    tvModel = new TopContractorsTVModel();

    tvModel->getData();
    view->setTVModel(tvModel);

    initModelFromInterfaceData();

    restoreTableState();
}

TopContractorsDialogController::~TopContractorsDialogController()
{
    saveTableState();
}

void TopContractorsDialogController::initModelFromInterfaceData()
{
    this->setListLimitFilter(view->getSpinBoxListLimit()->value());
    this->setDateFromFilter(view->getDateEditFrom()->date());
    this->setDateToFilter(view->getDateEditTo()->date());
}

void TopContractorsDialogController::exec()
{
    view->exec();
}

void TopContractorsDialogController::saveReport()
{
    ReportDataReader *reportDataReader = new ReportDataReader(view->getTableView());
    doSaveReport(reportDataReader, view->windowTitle(), Report::TOP_CONTRACTORS);
    view->accept();
}

void TopContractorsDialogController::setListLimitFilter(int limit)
{
    tvModel->setListLimitFilter(limit);
    tvModel->getData();
}

void TopContractorsDialogController::setDateFromFilter(QDate fromDate)
{
    tvModel->setDateFromFilter(fromDate);
    tvModel->getData();
}

void TopContractorsDialogController::setDateToFilter(QDate toDate)
{
    tvModel->setDateToFilter(toDate);
    tvModel->getData();
}

void TopContractorsDialogController::restoreTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = tableStateManager->getState("REPORT_TOP_CONTRACTORS");
    view->getTableView()->horizontalHeader()->restoreState(state);

    delete tableStateManager;
}

void TopContractorsDialogController::saveTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("REPORT_TOP_CONTRACTORS");
    if(state != oldState)
        tableStateManager->saveState("REPORT_TOP_CONTRACTORS", state);

    delete tableStateManager;
}
