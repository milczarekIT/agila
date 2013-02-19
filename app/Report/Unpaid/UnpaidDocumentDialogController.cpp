#include "UnpaidDocumentDialogController.h"

UnpaidDocumentDialogController::UnpaidDocumentDialogController(QWidget *parent)
{
    tvModel = new UnpaidDocumentTVModel();
    this->view = new UnpaidDocumentDialogView(parent, this);

    view->setTVModel(tvModel);
}

void UnpaidDocumentDialogController::exec()
{
    view->exec();
}

void UnpaidDocumentDialogController::initNotPaidOnTimeFilterInModel(bool checked)
{
    if(checked)
        tvModel->notOnTimeFilterOnly();
    else
        tvModel->resetOnTimeFilter();
}

void UnpaidDocumentDialogController::restoreTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = tableStateManager->getState("REPORT_UNPAID_DOCUMENTS");
    view->getTableView()->horizontalHeader()->restoreState(state);

    delete tableStateManager;
}

void UnpaidDocumentDialogController::saveTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("REPORT_UNPAID_DOCUMENTS");
    if(state != oldState)
        tableStateManager->saveState("REPORT_UNPAID_DOCUMENTS", state);

    delete tableStateManager;
}
