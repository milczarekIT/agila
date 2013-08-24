#include "EndingGoodsDialogController.h"

EndingGoodsDialogController::EndingGoodsDialogController(QWidget *parent)
{
    view = new EndingGoodsDialogView(parent, this);

    tvModel = new ReportGoodsTVModel();

    tvModel->getData();
    view->setTVModel(tvModel);

    this->quantityChanged(view->getSpinBoxQuantity()->value());

    restoreTableState();
}

EndingGoodsDialogController::~EndingGoodsDialogController()
{
    saveTableState();
    delete tvModel;
}

void EndingGoodsDialogController::exec()
{
    view->exec();
}

void EndingGoodsDialogController::saveReport()
{
    ReportDataReader *reportDataReader = new ReportDataReader(view->getTableView());
    doSaveReport(reportDataReader, view->windowTitle(),  Report::ENDING_GOODS);
    view->accept();
}

void EndingGoodsDialogController::quantityChanged(double value)
{
    tvModel->setQuantityFilter(value);
    tvModel->getData();
}

void EndingGoodsDialogController::restoreTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = tableStateManager->getState("REPORT_ENDING_GOODS");
    view->getTableView()->horizontalHeader()->restoreState(state);

    delete tableStateManager;
}

void EndingGoodsDialogController::saveTableState() {
    tableStateManager = new TableStateManager();
    QByteArray state = view->getTableView()->horizontalHeader()->saveState();
    QByteArray oldState = tableStateManager->getState("REPORT_ENDING_GOODS");
    if(state != oldState)
        tableStateManager->saveState("REPORT_ENDING_GOODS", state);

    delete tableStateManager;
}
