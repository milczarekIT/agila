#include "CurrentInventoryGroupsDialogController.h"

CurrentInventoryGroupsDialogController::CurrentInventoryGroupsDialogController(QWidget *parent)
{
    tvModel = new CurrentInventoryGroupsTVModel();
    view = new CurrentInventoryGroupsDialogView(parent,this);

    tvModel->getData();
    view->setTVModel(tvModel);

    view->getLineValue()->setText(tvModel->getValue().toString());

    restoreTableState();
}

CurrentInventoryGroupsDialogController::~CurrentInventoryGroupsDialogController()
{
    saveTableState();
    delete tvModel;
}

void CurrentInventoryGroupsDialogController::exec()
{
    view->exec();
}

void CurrentInventoryGroupsDialogController::showWithZeroQuantity(bool checked)
{
    if(checked)
        tvModel->showWithZeroQuantityFilter();
    else
        tvModel->dontShowWithZeroQuantityFilter();

    tvModel->getData();
}

void CurrentInventoryGroupsDialogController::saveReport()
{
    ReportDataReader *reportDataReader = new ReportDataReader(view->getTableView());
    doSaveReport(reportDataReader, view->windowTitle(), Report::CURRENT_INVENTORY_GROUP);
    view->accept();
}

void CurrentInventoryGroupsDialogController::restoreTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = tableStateManager->getState("REPORT_CURRENT_GROUP_INVENTORY");
    view->getTableView()->horizontalHeader()->restoreState(state);

    delete tableStateManager;
}

void CurrentInventoryGroupsDialogController::saveTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("REPORT_CURRENT_GROUP_INVENTORY");
    if(state != oldState)
        tableStateManager->saveState("REPORT_CURRENT_GROUP_INVENTORY", state);

    delete tableStateManager;
}
