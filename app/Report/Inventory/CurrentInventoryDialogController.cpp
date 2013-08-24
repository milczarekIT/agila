#include "CurrentInventoryDialogController.h"

CurrentInventoryDialogController::CurrentInventoryDialogController(QWidget *parent)
{
    tvModel = new CurrentInventoryTVModel();
    view = new CurrentInventoryDialogView(parent,this);

    tvModel->getData();
    view->setTVModel(tvModel);

    view->getLineValue()->setText(tvModel->getValue().toString());

    restoreTableState();
}

CurrentInventoryDialogController::~CurrentInventoryDialogController()
{
    saveTableState();
    delete tvModel;
}


void CurrentInventoryDialogController::exec() {
    view->exec();
}


void CurrentInventoryDialogController::showWithZeroQuantity(bool checked)
{
    if(checked)
        tvModel->showWithZeroQuantityFilter();
    else
        tvModel->dontShowWithZeroQuantityFilter();

    tvModel->getData();
}

void CurrentInventoryDialogController::saveReport()
{
    ReportDataReader *reportDataReader = new ReportDataReader(view->getTableView());
    doSaveReport(reportDataReader, view->windowTitle(),  Report::CURRENT_INVENTORY);
    view->accept();
}

void CurrentInventoryDialogController::restoreTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = tableStateManager->getState("REPORT_CURRENT_INVENTORY");
    view->getTableView()->horizontalHeader()->restoreState(state);

    delete tableStateManager;
}

void CurrentInventoryDialogController::saveTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("REPORT_CURRENT_INVENTORY");
    if(state != oldState)
        tableStateManager->saveState("REPORT_CURRENT_INVENTORY", state);

    delete tableStateManager;
}
